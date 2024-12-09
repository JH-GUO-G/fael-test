/*
 * Copyright 2015 Fadri Furrer, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Michael Burri, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Mina Kamel, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Janosch Nikolic, ASL, ETH Zurich, Switzerland
 * Copyright 2015 Markus Achtelik, ASL, ETH Zurich, Switzerland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ros/ros.h>
#include <mav_msgs/default_topics.h>
#include <geometry_msgs/PoseStamped.h>
#include <gazebo_msgs/ModelState.h>
#include <gazebo_msgs/SetModelState.h>
#include <trajectory_msgs/MultiDOFJointTrajectory.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>

ros::ServiceClient set_state_client;

// 订阅MultiDOFJointTrajectory消息的回调函数
void MultiDofJointTrajectoryCallback(
    const trajectory_msgs::MultiDOFJointTrajectory::ConstPtr& msg) {
    if (msg->points.empty()) {
        ROS_WARN("Received an empty trajectory message, skipping...");
        return;
    }

    // 假设只有一个点，取第一个点的信息
    const trajectory_msgs::MultiDOFJointTrajectoryPoint& point = msg->points[0];

    // 检查是否包含位置和方向
    if (point.transforms.empty()) {
        // ROS_WARN("No transforms in the trajectory point, skipping...");
        return;
    }

    // 创建SetModelState服务请求
    gazebo_msgs::SetModelState set_model_state;
    set_model_state.request.model_state.model_name = "firefly";  // 替换成你的无人机模型名称
    set_model_state.request.model_state.reference_frame = "world";

    // 设置位置
    set_model_state.request.model_state.pose.position.x = point.transforms[0].translation.x;
    set_model_state.request.model_state.pose.position.y = point.transforms[0].translation.y;
    set_model_state.request.model_state.pose.position.z = point.transforms[0].translation.z;

    // 设置方向
    set_model_state.request.model_state.pose.orientation = point.transforms[0].rotation;

    // 调用服务来设置模型状态
    if (set_state_client.call(set_model_state)) {
        // ROS_INFO("Updated UAV position to: x=%f, y=%f, z=%f",
        //          point.transforms[0].translation.x,
        //          point.transforms[0].translation.y,
        //          point.transforms[0].translation.z);
    } else {
        ROS_ERROR("Failed to call service /gazebo/set_model_state");
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "uav_position_controller");
    ros::NodeHandle nh;

    // 设置服务客户端
    set_state_client = nh.serviceClient<gazebo_msgs::SetModelState>("/gazebo/set_model_state");

    // 订阅COMMAND_TRAJECTORY话题
    ros::Subscriber cmd_pose_sub = nh.subscribe(
        mav_msgs::default_topics::COMMAND_TRAJECTORY, 1, MultiDofJointTrajectoryCallback);

    ros::spin();
    return 0;
}