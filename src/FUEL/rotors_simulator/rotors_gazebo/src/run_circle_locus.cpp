//  run_circle_locus.cpp
// 飞一个圆形轨迹

#include <Eigen/Geometry>
#include <nav_msgs/Odometry.h>
#include <nodelet/nodelet.h>
#include <quadrotor_msgs/Corrections.h>
#include <quadrotor_msgs/PositionCommand.h>
#include <quadrotor_msgs/SO3Command.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Bool.h>
#include <tf/transform_datatypes.h>

#include <thread>
#include <chrono>
#include <cmath>
#include <Eigen/Core>
#include <mav_msgs/conversions.h>
#include <mav_msgs/default_topics.h>
#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <trajectory_msgs/MultiDOFJointTrajectory.h>


quadrotor_msgs::PositionCommand _cmd;

void positionCmdCallback(const quadrotor_msgs::PositionCommand::ConstPtr& cmd)
{
    _cmd = *cmd;
    // ROS_INFO("Received: [x: %f, y: %f, z: %f]",
    //          cmd->position.x, cmd->position.y, cmd->position.z);
}

// 回调函数，处理 odom 话题的消息
void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
    // ROS_INFO("Received odom: [x: %f, y: %f, z: %f]",
    //          msg->pose.pose.position.x, msg->pose.pose.position.y, msg->pose.pose.position.z);
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "circle_locus_example");
    ros::NodeHandle nh;
    // Create a private node handle for accessing node parameters.
    ros::NodeHandle nh_private("~");

    // ros::Publisher firefly_command_pub_ = nh.advertise<quadrotor_msgs::SO3Command>("so3_cmd", 10);

    ros::Subscriber odom_sub_ = nh.subscribe("odometry_sensor1/odometry", 10,odomCallback);
    // ros::Subscriber position_cmd_sub_ = n.subscribe("position_cmd", 10, &SO3ControlNodelet::position_cmd_callback, this,
    //                               ros::TransportHints().tcpNoDelay());

    ros::Subscriber position_cmd_sub_ = nh.subscribe<quadrotor_msgs::PositionCommand>("/planning/pos_cmd", 10,positionCmdCallback);
    // ros::Subscriber position_cmd_sub_ = nh.subscribe("/planning/pos_cmd", 10,positionCmdCallback);

    // 订阅 odom 话题
    // ros::Subscriber odom_sub = nh.subscribe("odom", 10, odomCallback);

    ros::Publisher trajectory_pub =
        nh.advertise<trajectory_msgs::MultiDOFJointTrajectory>(
            mav_msgs::default_topics::COMMAND_TRAJECTORY, 10);
    ROS_INFO("Started circle locus example.");

    // std_srvs::Empty srv;
    // bool unpaused = ros::service::call("/gazebo/unpause_physics", srv);
    // unsigned int i = 0;

    // // Trying to unpause Gazebo for 10 seconds.
    // while (i <= 10 && !unpaused) {
    // ROS_INFO("Wait for 1 second before trying to unpause Gazebo again.");
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // unpaused = ros::service::call("/gazebo/unpause_physics", srv);
    // ++i;
    // }

    // if (!unpaused) {
    // ROS_FATAL("Could not wake up Gazebo.");
    // return -1;
    // } else {
    // ROS_INFO("Unpaused the Gazebo simulation.");
    // }

    // // Wait for 5 seconds to let the Gazebo GUI show up.
    // ros::Duration(5.0).sleep();

    _cmd.position.x=0;_cmd.position.y=0;_cmd.position.z=0.1;
    trajectory_msgs::MultiDOFJointTrajectory trajectory_msg;
    trajectory_msg.header.stamp = ros::Time::now();
    double begin_t = ros::Time::now().toSec();
    double t = 0;
    double angle = 0;
    ros::Rate rate(10);
    // Default desired position and yaw.
    Eigen::Vector3d desired_position(0.0, 0.0, 1.0);
    double desired_yaw = 0.0;

    // Overwrite defaults if set as node parameters.
    // nh_private.param("x", desired_position.x(), desired_position.x());
    // nh_private.param("y", desired_position.y(), desired_position.y());
    // nh_private.param("z", desired_position.z(), desired_position.z());
    // nh_private.param("yaw", desired_yaw, desired_yaw);


    while (ros::ok())
    {
        // t = ros::Time::now().toSec() - begin_t;
        // angle = fmod(2 * M_PI / 10 * t , 2 * M_PI); // 10s飞一圈
        // desired_position.x() = cos(angle); // 圆的半径是1
        // desired_position.y() = sin(angle);
        // desired_position.z() = 1;
        // desired_yaw = fmod(angle + M_PI/2 , 2 * M_PI);
        


        // ROS_INFO("Received: [x: %f, y: %f, z: %f]", _cmd.position.x, _cmd.position.y, _cmd.position.z);
        desired_position.x() = _cmd.position.x; // 圆的半径是1
        desired_position.y() = _cmd.position.y;
        desired_position.z() = _cmd.position.z;
        desired_yaw = _cmd.yaw;
        trajectory_msg.header.stamp = ros::Time::now();
            mav_msgs::msgMultiDofJointTrajectoryFromPositionYaw(
            desired_position, desired_yaw, &trajectory_msg);
        trajectory_pub.publish(trajectory_msg);
        rate.sleep();
        ros::spinOnce();

    }
    
    ros::shutdown();

    return 0;
}
