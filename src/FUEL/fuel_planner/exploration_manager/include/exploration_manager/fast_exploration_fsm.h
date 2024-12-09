#ifndef _FAST_EXPLORATION_FSM_H_
#define _FAST_EXPLORATION_FSM_H_

#include <Eigen/Eigen>

#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <std_msgs/Empty.h>
#include <nav_msgs/Odometry.h>
#include <visualization_msgs/Marker.h>


#include <bspline/TrajectoryInfo.h>
#include <bspline/replaninfo.h>

// #include <plan_manage/TrajectoryInfo.h>  // 包含自定义消息的头文件

#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>

using Eigen::Vector3d;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::string;

namespace fast_planner {

class EDTEnvironment;
class SDFMap;

class FastPlannerManager;
class FastExplorationManager;
class PlanningVisualization;
struct FSMParam;
struct FSMData;

enum EXPL_STATE { INIT, WAIT_TRIGGER, PLAN_TRAJ, PUB_TRAJ, EXEC_TRAJ, FINISH };

class FastExplorationFSM {
private:
  /* planning utils */
  shared_ptr<FastPlannerManager> planner_manager_;
  shared_ptr<FastExplorationManager> expl_manager_;
  shared_ptr<PlanningVisualization> visualization_;

  shared_ptr<EDTEnvironment> edt_environment_;
  shared_ptr<SDFMap> sdf_map_;

  shared_ptr<FSMParam> fp_;
  shared_ptr<FSMData> fd_;
  EXPL_STATE state_;

  bool classic_;
  
  nav_msgs::Path waypoints;
  geometry_msgs::PoseStamped waypoint;

  /* ROS utils */
  ros::NodeHandle node_;
  ros::Timer exec_timer_, safety_timer_, vis_timer_, frontier_timer_;
  ros::Subscriber trigger_sub_, odom_sub_,pos_sub,traj_sub,replaninfo_sub;
  ros::Publisher replan_pub_, new_pub_, bspline_pub_,waypoints_pub_,waypoint_pub_;

  /* helper functions */
  int callExplorationPlanner();
  
  int callNextpos();

  void transitState(EXPL_STATE new_state, string pos_call);

  /* ROS functions */
  void FSMCallback(const ros::TimerEvent& e);
  void safetyCallback(const ros::TimerEvent& e);
  void frontierCallback(const ros::TimerEvent& e);
  void triggerCallback(const nav_msgs::PathConstPtr& msg);
  void odometryCallback(const nav_msgs::OdometryConstPtr& msg);
  void visualize();
  void clearVisMarker();

  void positionCallback(const geometry_msgs::Point::ConstPtr& msg);
  void trajCallback(const bspline::TrajectoryInfo::ConstPtr& msg);
  void replanCallback(const bspline::replaninfo::ConstPtr& msg);

  

public:
  FastExplorationFSM(/* args */) {
  }
  ~FastExplorationFSM() {
  }

  void init(ros::NodeHandle& nh);

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

}  // namespace fast_planner

#endif