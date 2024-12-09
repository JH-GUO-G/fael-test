
#include <plan_manage/planner_manager.h>
#include <exploration_manager/fast_exploration_manager.h>
#include <traj_utils/planning_visualization.h>

#include <exploration_manager/fast_exploration_fsm.h>
#include <exploration_manager/expl_data.h>
#include <plan_env/edt_environment.h>
#include <plan_env/sdf_map.h>

#include <bspline/TrajectoryInfo.h>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

using Eigen::Vector4d;

namespace fast_planner {
void FastExplorationFSM::init(ros::NodeHandle& nh) 
{
  fp_.reset(new FSMParam);
  fd_.reset(new FSMData);

  /*  Fsm param  */
  nh.param("fsm/thresh_replan1", fp_->replan_thresh1_, -1.0);
  nh.param("fsm/thresh_replan2", fp_->replan_thresh2_, -1.0);
  nh.param("fsm/thresh_replan3", fp_->replan_thresh3_, -1.0);
  nh.param("fsm/replan_time", fp_->replan_time_, -1.0);

  /* Initialize main modules */
  expl_manager_.reset(new FastExplorationManager);
  expl_manager_->initialize(nh);

  // planner_manager_.reset(new FastPlannerManager);
  // planner_manager_->initPlanModules(nh);

  visualization_.reset(new PlanningVisualization(nh));

  planner_manager_ = expl_manager_->planner_manager_;
  edt_environment_ = planner_manager_->edt_environment_;
  sdf_map_ = edt_environment_->sdf_map_;

  state_ = EXPL_STATE::INIT;
  fd_->have_odom_ = false;
  fd_->state_str_ = { "INIT", "WAIT_TRIGGER", "PLAN_TRAJ", "PUB_TRAJ", "EXEC_TRAJ", "FINISH" };
  fd_->static_state_ = true;
  fd_->trigger_ = false;

  fd_->current_wp_=0;
    
  fd_->expl_= false;
  /* Ros sub, pub and timer */
  exec_timer_ = nh.createTimer(ros::Duration(0.01), &FastExplorationFSM::FSMCallback, this);
  // safety_timer_ = nh.createTimer(ros::Duration(0.05), &FastExplorationFSM::safetyCallback, this);
  frontier_timer_ = nh.createTimer(ros::Duration(0.5), &FastExplorationFSM::frontierCallback, this);

  trigger_sub_ =
      nh.subscribe("/waypoint_generator/waypoints", 1, &FastExplorationFSM::triggerCallback, this);
  odom_sub_ = nh.subscribe("/odom_world", 1, &FastExplorationFSM::odometryCallback, this);

  pos_sub = nh.subscribe("/fast/position",1, &FastExplorationFSM::positionCallback, this);

  traj_sub=nh.subscribe("/fast_planner_node/trajectory_info",1, &FastExplorationFSM::trajCallback, this);
  // replaninfo_sub=nh.subscribe("/fast_planner_node/replan_info",1, &FastExplorationFSM::replanCallback, this);

  replan_pub_ = nh.advertise<std_msgs::Empty>("/planning/replan", 10);
  new_pub_ = nh.advertise<std_msgs::Empty>("/planning/new", 10);
  bspline_pub_ = nh.advertise<bspline::Bspline>("/planning/bspline", 10);

  waypoints_pub_=nh.advertise<nav_msgs::Path>("waypoints", 50);
  waypoint_pub_ = nh.advertise<geometry_msgs::PoseStamped>("waypoint", 50);

}

void FastExplorationFSM::trajCallback(const bspline::TrajectoryInfo::ConstPtr& msg){
  
  fd_->info.duration = msg->duration;
  fd_->info.start_time = msg->start_time;
  fd_->info.pos_end = msg->pos_end;
  fd_->info.pos = msg->pos;
  fd_->info.vel = msg->vel;
  fd_->info.acc = msg->acc;
  fd_->info.start_yaw_= msg->start_yaw_;
  }

  
// {
//     ROS_INFO("Received trajectory info in trajCallback");

// }

void FastExplorationFSM::positionCallback(const geometry_msgs::Point::ConstPtr& msg) {
  ROS_INFO("Received position: x = %f, y = %f, z = %f", msg->x, msg->y, msg->z);
  
  double x_received = msg->x;
  double y_received = msg->y;
  double z_received = msg->z;
  
  Eigen::Vector3d pos(x_received,y_received,z_received);
  // 获取目标点的位置信息
  double x_target = fd_->way_pose_.pose.position.x;
  double y_target = fd_->way_pose_.pose.position.y;
  double z_target = fd_->way_pose_.pose.position.z;

  double distance = sqrt(pow(x_target - x_received, 2) +
                         pow(y_target - y_received, 2) +
                         pow(z_target - z_received, 2));
  //  if (state_ == EXPL_STATE::WAIT_TRIGGER && distance<0.5)
   if (state_ == EXPL_STATE::WAIT_TRIGGER )
  {
    fd_->expl_ =true;
    ROS_WARN_STREAM("changed to expl  ");

    Eigen::Vector3d expl_star_pos(x_received,y_received,z_received );
    // sdf_map_->resetBuffertwo(pos);
  }

}

void FastExplorationFSM::FSMCallback(const ros::TimerEvent& e) {
  ROS_INFO_STREAM_THROTTLE(1.0, "[FSM]: state: " << fd_->state_str_[int(state_)]);

  switch (state_) {
    case INIT: {

      // Wait for odometry ready
      if (!fd_->have_odom_) {
        ROS_WARN_THROTTLE(1.0, "no odom.");
        return;
      }
      // Go to wait trigger when odom is ok
      transitState(WAIT_TRIGGER, "FSM");
      break;
    }

    case WAIT_TRIGGER: {
      // Do nothing but wait for trigger
      // if (fd_->expl_ ==false){
      //   fd_->expl_ =true;
      // }

      ROS_WARN_THROTTLE(1.0, "wait for trigger.");
      break;
    }

    case FINISH: {
      ROS_INFO_THROTTLE(1.0, "finish exploration.");
      break;
    }

    case PLAN_TRAJ: {

      int res;
      if (fd_->expl_ ==false){
        fd_->start_pt_ = fd_->odom_pos_;
        fd_->start_vel_ = fd_->odom_vel_;
        fd_->start_acc_.setZero();

        fd_->start_yaw_(0) = fd_->odom_yaw_;
        fd_->start_yaw_(1) = fd_->start_yaw_(2) = 0.0;
        res = callNextpos();
      } 
      else{  
        if (!fd_->static_state_)
        {    

          fd_->start_pt_ = Eigen::Vector3d(fd_->info.pos.x, fd_->info.pos.y, fd_->info.pos.z);
          fd_->start_vel_ = Eigen::Vector3d(fd_->info.vel.x, fd_->info.vel.y, fd_->info.vel.z);
          fd_->start_acc_ = Eigen::Vector3d(fd_->info.acc.x, fd_->info.acc.y, fd_->info.acc.z);

          // 将 start_yaw_ 的 x, y, z 分量赋值给 Eigen::Vector3d 类型的 fd_->start_yaw_
          fd_->start_yaw_(0) = fd_->info.start_yaw_.x;
          fd_->start_yaw_(1) = fd_->info.start_yaw_.y;
          fd_->start_yaw_(2) = fd_->info.start_yaw_.z;
        // ROS_WARN_STREAM("replanpos     "<< fd_->start_pt_.transpose());
        
        }
         else{
        fd_->start_pt_ = fd_->odom_pos_;
        fd_->start_vel_ = fd_->odom_vel_;
        fd_->start_acc_.setZero();

        fd_->start_yaw_(0) = fd_->odom_yaw_;
        fd_->start_yaw_(1) = fd_->start_yaw_(2) = 0.0;
        }

        res = callNextpos();
        

      }
      if (res == SUCCEED) {
        std::cout << "SUCCEEDSUCCEEDSUCCEEDSUCCEED" << endl;
        // ROS_WARN_STREAM("SUCCEEDSUCCEEDSUCCEEDSUCCEED     ");
        transitState(PUB_TRAJ, "FSM");
      } else if (res == NO_FRONTIER) {
        std::cout << "NO_FRONTIERNO_FRONTIERNO_FRONTIER" << endl;
        transitState(FINISH, "FSM");
        fd_->static_state_ = true;
        clearVisMarker();
      } else if (res == FAIL) {
       std::cout << "FAILFAIL" << endl;

        // Still in PLAN_TRAJ state, keep replanning
        ROS_WARN("plan fail");
        fd_->static_state_ = true;
      }
      break;
    }

    case PUB_TRAJ: {
      if (fd_->expl_ ==false){
        waypoint_pub_.publish(waypoint);
        transitState(WAIT_TRIGGER, "FSM");
      }
      
      if (fd_->expl_ ==true){
        // double dt = (ros::Time::now() - fd_->newest_traj_.start_time).toSec();
        // if (dt > 0) {
        // bspline_pub_.publish(fd_->newest_traj_);
        fd_->static_state_ = false;
        waypoint_pub_.publish(waypoint);
        ROS_WARN_STREAM("waypoint sended  ");

        transitState(EXEC_TRAJ, "FSM");
        thread vis_thread(&FastExplorationFSM::visualize, this);
        vis_thread.detach();
      }
      
      break;
    }

    case EXEC_TRAJ: {
      // bspline::TrajectoryInfo* info = &planner_manager_->local_data_;
      double t_cur = (ros::Time::now() - fd_->info.start_time).toSec();

      double time_to_end = fd_->info.duration - t_cur;
      
      Eigen::Vector3d p_cur(fd_->info.pos.x, fd_->info.pos.y, fd_->info.pos.z);
      Eigen::Vector3d p_end(fd_->info.pos_end.x, fd_->info.pos_end.y, fd_->info.pos_end.z);


    // 计算两个向量之间的距离
      double distance = (p_cur - p_end).norm();

      // ROS_WARN_STREAM("t_cur:"<<t_cur);
      // ROS_WARN_STREAM("time_to_end:"<<time_to_end);

      // if (distance < 0.1) {
      //   // transitState(PLAN_TRAJ, "FSM");
      //   transitState(WAIT_TRIGGER, "FSM");
      //   fd_->static_state_ = true;
      //   fd_->trigger_ = false;

      //   ROS_WARN("get=================================");
      //   return;
      // }

      // Replan if traj is almost fully executed
      if (time_to_end < fp_->replan_thresh1_ ) {//0.5
        transitState(PLAN_TRAJ, "FSM"); 
        // transitState(WAIT_TRIGGER, "FSM");
        // fd_->static_state_ = true;
        // fd_->trigger_ = false;

        ROS_WARN("Replan: traj fully executed=================================");
        return;
      }
      // Replan if next frontier to be visited is covered
      if ( t_cur > fp_->replan_thresh2_ && expl_manager_->frontier_finder_->isFrontierCovered()) {//0.5
        transitState(PLAN_TRAJ, "FSM");
        ROS_WARN("Replan: cluster covered=====================================");
        return;
      }
      // Replan after some time
      if (t_cur > fp_->replan_thresh3_ && !classic_) {//1.5
        transitState(PLAN_TRAJ, "FSM");
        ROS_WARN("Replan: periodic call=======================================");
      }

      break;

    }
    // case EXEC_TRAJ: {
    //   // Replan if next frontier to be visited is covered
    //   if ( expl_manager_->frontier_finder_->isFrontierCovered()) {
    //     transitState(PLAN_TRAJ, "FSM");
    //     ROS_WARN("Replan: cluster covered=====================================");
    //     return;
    //   }
    //   break;
    // }
  }
}

int FastExplorationFSM::callNextpos() {
  ros::Time time_r = ros::Time::now() + ros::Duration(fp_->replan_time_);

  
  int res = expl_manager_->planExploreMotiontwo(fd_->start_pt_, fd_->start_vel_, fd_->start_acc_,
                                             fd_->start_yaw_,fd_->expl_,fd_->way_pose_);//waypose 特指导航的目标点
  
  // int res = planner_manager_->kinodynamicReplan(fd_->start_pt_, fd_->start_vel_, fd_->start_acc_, fd_->end_pt_, fd_->end_vel_);//不断调用，一直是同个终点，但是搜索只在一定范围边界内完成
  
  std::cout << "nextpos  return"<< expl_manager_->ed_->next_pos << endl;
  // 创建 PoseStamped 消息，用于存储 next_pos 的位置
    geometry_msgs::PoseStamped pose_stamped;

    // 将 Eigen::Vector3d (next_pos) 转换为 geometry_msgs::PoseStamped
    pose_stamped.pose.position.x = expl_manager_->ed_->next_pos.x();
    pose_stamped.pose.position.y = expl_manager_->ed_->next_pos.y();
    pose_stamped.pose.position.z = expl_manager_->ed_->next_pos.z();

    // 可以根据需要设置 Orientation（此处设置为单位四元数）
    pose_stamped.pose.orientation.x = 0.0;
    pose_stamped.pose.orientation.y = 0.0;
    pose_stamped.pose.orientation.z = 0.0;
    pose_stamped.pose.orientation.w = 1.0;
    
    tf2::Quaternion tf_quat;
    tf_quat.setRPY(0, 0, expl_manager_->ed_->next_yaw);  // Roll = 0, Pitch = 0, Yaw = next_yaw

  // 将 tf2::Quaternion 转换为 geometry_msgs::Quaternion
    pose_stamped.pose.orientation = tf2::toMsg(tf_quat);
    
    // 将 pose_stamped 添加到 Path 中的 poses 数组
    // waypoints.poses.push_back(pose_stamped);

    // 设置路径的参考坐标系
    pose_stamped.header.frame_id = "world";
    pose_stamped.header.stamp = ros::Time::now();
    waypoint=pose_stamped;
  
    classic_ = false;

  return res;
}

int FastExplorationFSM::callExplorationPlanner() {
  ros::Time time_r = ros::Time::now() + ros::Duration(fp_->replan_time_);

  
  int res = expl_manager_->planExploreMotion(fd_->start_pt_, fd_->start_vel_, fd_->start_acc_,
                                             fd_->start_yaw_,fd_->expl_,fd_->way_pose_);
  
  // int res = planner_manager_->kinodynamicReplan(fd_->start_pt_, fd_->start_vel_, fd_->start_acc_, fd_->end_pt_, fd_->end_vel_);//不断调用，一直是同个终点，但是搜索只在一定范围边界内完成
  
  std::cout << "resturn"<< res << endl;

  classic_ = false;

  // int res = expl_manager_->classicFrontier(fd_->start_pt_, fd_->start_yaw_[0]);
  // classic_ = true;

  // int res = expl_manager_->rapidFrontier(fd_->start_pt_, fd_->start_vel_, fd_->start_yaw_[0],
  // classic_);

  if (res == SUCCEED) {
    auto info = &planner_manager_->local_data_;
    info->start_time_ = (ros::Time::now() - time_r).toSec() > 0 ? ros::Time::now() : time_r;

    bspline::Bspline bspline;
    bspline.order = planner_manager_->pp_.bspline_degree_;
    bspline.start_time = info->start_time_;
    bspline.traj_id = info->traj_id_;
    Eigen::MatrixXd pos_pts = info->position_traj_.getControlPoint();
    for (int i = 0; i < pos_pts.rows(); ++i) {
      geometry_msgs::Point pt;
      pt.x = pos_pts(i, 0);
      pt.y = pos_pts(i, 1);
      pt.z = pos_pts(i, 2);
      bspline.pos_pts.push_back(pt);
    }
    Eigen::VectorXd knots = info->position_traj_.getKnot();
    for (int i = 0; i < knots.rows(); ++i) {
      bspline.knots.push_back(knots(i));
    }
    Eigen::MatrixXd yaw_pts = info->yaw_traj_.getControlPoint();
    for (int i = 0; i < yaw_pts.rows(); ++i) {
      double yaw = yaw_pts(i, 0);
      bspline.yaw_pts.push_back(yaw);
    }
    bspline.yaw_dt = info->yaw_traj_.getKnotSpan();
    fd_->newest_traj_ = bspline;
  }
  // return res+1;
  return res;
}

void FastExplorationFSM::visualize() {
  // auto info = &planner_manager_->local_data_;
  // auto plan_data = &planner_manager_->plan_data_;
  auto ed_ptr = expl_manager_->ed_;

  // Draw updated box
  // Vector3d bmin, bmax;
  // planner_manager_->edt_environment_->sdf_map_->getUpdatedBox(bmin, bmax);
  // visualization_->drawBox((bmin + bmax) / 2.0, bmax - bmin, Vector4d(0, 1, 0, 0.3), "updated_box", 0,
  // 4);

  // Draw frontier
  static int last_ftr_num = 0;
  for (int i = 0; i < ed_ptr->frontiers_.size(); ++i) {
    visualization_->drawCubes(ed_ptr->frontiers_[i], 0.1,
                              visualization_->getColor(double(i) / ed_ptr->frontiers_.size(), 0.4),
                              "frontier", i, 4);
    // visualization_->drawBox(ed_ptr->frontier_boxes_[i].first, ed_ptr->frontier_boxes_[i].second,
    //                         Vector4d(0.5, 0, 1, 0.3), "frontier_boxes", i, 4);
  }
  for (int i = ed_ptr->frontiers_.size(); i < last_ftr_num; ++i) {
    visualization_->drawCubes({}, 0.1, Vector4d(0, 0, 0, 1), "frontier", i, 4);
    // visualization_->drawBox(Vector3d(0, 0, 0), Vector3d(0, 0, 0), Vector4d(1, 0, 0, 0.3),
    // "frontier_boxes", i, 4);
  }
  last_ftr_num = ed_ptr->frontiers_.size();
  // for (int i = 0; i < ed_ptr->dead_frontiers_.size(); ++i)
  //   visualization_->drawCubes(ed_ptr->dead_frontiers_[i], 0.1, Vector4d(0, 0, 0, 0.5), "dead_frontier",
  //                             i, 4);
  // for (int i = ed_ptr->dead_frontiers_.size(); i < 5; ++i)
  //   visualization_->drawCubes({}, 0.1, Vector4d(0, 0, 0, 0.5), "dead_frontier", i, 4);

  // Draw global top viewpoints info
  visualization_->drawSpheres(ed_ptr->points_, 0.4, Vector4d(0, 0.5, 0, 1), "points", 0, 6);
  visualization_->drawLines(ed_ptr->global_tour_, 0.2, Vector4d(0, 0.5, 0, 1), "global_tour", 0, 6);
  // visualization_->drawLines(ed_ptr->points_, ed_ptr->views_, 0.05, Vector4d(0, 1, 0.5, 1), "view", 0, 6);
  // visualization_->drawLines(ed_ptr->points_, ed_ptr->averages_, 0.03, Vector4d(1, 0, 0, 1),
  // "point-average", 0, 6);

  // Draw local refined viewpoints info
  // visualization_->drawSpheres(ed_ptr->refined_points_, 0.2, Vector4d(0, 0, 1, 1), "refined_pts", 0, 6);
  // visualization_->drawLines(ed_ptr->refined_points_, ed_ptr->refined_views_, 0.05,
  //                           Vector4d(0.5, 0, 1, 1), "refined_view", 0, 6);
  // visualization_->drawLines(ed_ptr->refined_tour_, 0.07, Vector4d(0, 0, 1, 1), "refined_tour", 0, 6);
  // visualization_->drawLines(ed_ptr->refined_views1_, ed_ptr->refined_views2_, 0.04, Vector4d(0, 0, 0,
  // 1),
  //                           "refined_view", 0, 6);
  // visualization_->drawLines(ed_ptr->refined_points_, ed_ptr->unrefined_points_, 0.05, Vector4d(1, 1,
  // 0, 1),
  //                           "refine_pair", 0, 6);
  // for (int i = 0; i < ed_ptr->n_points_.size(); ++i)
  //   visualization_->drawSpheres(ed_ptr->n_points_[i], 0.1,
  //                               visualization_->getColor(double(ed_ptr->refined_ids_[i]) /
  //                               ed_ptr->frontiers_.size()),
  //                               "n_points", i, 6);
  // for (int i = ed_ptr->n_points_.size(); i < 15; ++i)
  //   visualization_->drawSpheres({}, 0.1, Vector4d(0, 0, 0, 1), "n_points", i, 6);

  // Draw trajectory
  // visualization_->drawSpheres({ ed_ptr->next_goal_ }, 0.3, Vector4d(0, 1, 1, 1), "next_goal", 0, 6);


  // visualization_->drawBspline(info->position_traj_, 0.1, Vector4d(1.0, 0.0, 0.0, 1), false, 0.15,
  //                             Vector4d(1, 1, 0, 1));

  // visualization_->drawSpheres(plan_data->kino_path_, 0.1, Vector4d(1, 0, 1, 1), "kino_path", 0, 0);
  // visualization_->drawLines(ed_ptr->path_next_goal_, 0.05, Vector4d(0, 1, 1, 1), "next_goal", 1, 6);
}

void FastExplorationFSM::clearVisMarker() {
  // visualization_->drawSpheres({}, 0.2, Vector4d(0, 0.5, 0, 1), "points", 0, 6);
  // visualization_->drawLines({}, 0.07, Vector4d(0, 0.5, 0, 1), "global_tour", 0, 6);
  // visualization_->drawSpheres({}, 0.2, Vector4d(0, 0, 1, 1), "refined_pts", 0, 6);
  // visualization_->drawLines({}, {}, 0.05, Vector4d(0.5, 0, 1, 1), "refined_view", 0, 6);
  // visualization_->drawLines({}, 0.07, Vector4d(0, 0, 1, 1), "refined_tour", 0, 6);
  // visualization_->drawSpheres({}, 0.1, Vector4d(0, 0, 1, 1), "B-Spline", 0, 0);

  // visualization_->drawLines({}, {}, 0.03, Vector4d(1, 0, 0, 1), "current_pose", 0, 6);
}

void FastExplorationFSM::frontierCallback(const ros::TimerEvent& e) {
  static int delay = 0;
  if (++delay < 5) return;

  if (state_ == WAIT_TRIGGER || state_ == FINISH) {
    auto ft = expl_manager_->frontier_finder_;
    auto ed = expl_manager_->ed_;
    ft->searchFrontiers();
    ft->computeFrontiersToVisit();
    ft->updateFrontierCostMatrix();

    ft->getFrontiers(ed->frontiers_);
    ft->getFrontierBoxes(ed->frontier_boxes_);

    // Draw frontier and bounding box
    for (int i = 0; i < ed->frontiers_.size(); ++i) {
      visualization_->drawCubes(ed->frontiers_[i], 0.1,
                                visualization_->getColor(double(i) / ed->frontiers_.size(), 0.4),
                                "frontier", i, 4);
      // visualization_->drawBox(ed->frontier_boxes_[i].first, ed->frontier_boxes_[i].second,
      // Vector4d(0.5, 0, 1, 0.3),
      //                         "frontier_boxes", i, 4);
    }
    for (int i = ed->frontiers_.size(); i < 50; ++i) {
      visualization_->drawCubes({}, 0.1, Vector4d(0, 0, 0, 1), "frontier", i, 4);
      // visualization_->drawBox(Vector3d(0, 0, 0), Vector3d(0, 0, 0), Vector4d(1, 0, 0, 0.3),
      // "frontier_boxes", i, 4);
    }
  }

  // if (!fd_->static_state_)
  // {
  //   static double astar_time = 0.0;
  //   static int astar_num = 0;
  //   auto t1 = ros::Time::now();

  //   planner_manager_->path_finder_->reset();
  //   planner_manager_->path_finder_->setResolution(0.4);
  //   if (planner_manager_->path_finder_->search(fd_->odom_pos_, Vector3d(-5, 0, 1)))
  //   {
  //     auto path = planner_manager_->path_finder_->getPath();
  //     visualization_->drawLines(path, 0.05, Vector4d(1, 0, 0, 1), "astar", 0, 6);
  //     auto visit = planner_manager_->path_finder_->getVisited();
  //     visualization_->drawCubes(visit, 0.3, Vector4d(0, 0, 1, 0.4), "astar-visit", 0, 6);
  //   }
  //   astar_num += 1;
  //   astar_time = (ros::Time::now() - t1).toSec();
  //   ROS_WARN("Average astar time: %lf", astar_time);
  // }
}

void FastExplorationFSM::triggerCallback(const nav_msgs::PathConstPtr& msg) {
  if (msg->poses[0].pose.position.z < -0.1) return;
  if (state_ != WAIT_TRIGGER) return;

  if(fd_->expl_== false)
  {
  // fd_->expl_= true;
  // fd_->way_pose_.pose.position.x=msg->poses[fd_->current_wp_].pose.position.x;
  // fd_->way_pose_.pose.position.y=msg->poses[fd_->current_wp_].pose.position.y;
  // fd_->way_pose_.pose.position.z=4;
  fd_->way_pose_.pose.position.x=38;
  fd_->way_pose_.pose.position.y=6;
  fd_->way_pose_.pose.position.z=3;
  cout<<"----------------------------------------"<<endl;
  cout<<fd_->way_pose_.pose.position.x<<fd_->way_pose_.pose.position.y<<fd_->way_pose_.pose.position.z<<endl;
  // fd_->way_pose_=msg->poses[fd_->current_wp_];
  // fd_->current_wp_=fd_->current_wp_+1;
  // Eigen::Vector3d point(fd_->way_pose_.pose.position.x,
  //                       fd_->way_pose_.pose.position.y,
  //                       fd_->way_pose_.pose.position.z);
  
  // Eigen::Vector3d point (3,3,1);
  // Eigen::Vector3d v (0,0,0);
  // fd_->end_pt_  = point ;
  // fd_->end_vel_ = v;        
  }
 
  fd_->trigger_ = true;
  cout << "Triggered!" << endl;
  transitState(PLAN_TRAJ, "triggerCallback");
}

void FastExplorationFSM::safetyCallback(const ros::TimerEvent& e) {
  if (state_ == EXPL_STATE::EXEC_TRAJ) {
    // Check safety and trigger replan if necessary
    double dist;
    bool safe = planner_manager_->checkTrajCollision(dist);
    if (!safe) {
      ROS_WARN("Replan: collision detected==================================");
      transitState(PLAN_TRAJ, "safetyCallback");
    }
  }
}

void FastExplorationFSM::odometryCallback(const nav_msgs::OdometryConstPtr& msg) {

  fd_->odom_pos_(0) = msg->pose.pose.position.x;
  fd_->odom_pos_(1) = msg->pose.pose.position.y;
  fd_->odom_pos_(2) = msg->pose.pose.position.z;

  fd_->odom_vel_(0) = msg->twist.twist.linear.x;
  fd_->odom_vel_(1) = msg->twist.twist.linear.y;
  fd_->odom_vel_(2) = msg->twist.twist.linear.z;

  fd_->odom_orient_.w() = msg->pose.pose.orientation.w;
  fd_->odom_orient_.x() = msg->pose.pose.orientation.x;
  fd_->odom_orient_.y() = msg->pose.pose.orientation.y;
  fd_->odom_orient_.z() = msg->pose.pose.orientation.z;

  Eigen::Vector3d rot_x = fd_->odom_orient_.toRotationMatrix().block<3, 1>(0, 0);
  fd_->odom_yaw_ = atan2(rot_x(1), rot_x(0));

  fd_->have_odom_ = true;
}

void FastExplorationFSM::transitState(EXPL_STATE new_state, string pos_call) {
  int pre_s = int(state_);
  state_ = new_state;
  cout << "[" + pos_call + "]: from " + fd_->state_str_[pre_s] + " to " + fd_->state_str_[int(new_state)]
       << endl;
}


}  // namespace fast_planner
