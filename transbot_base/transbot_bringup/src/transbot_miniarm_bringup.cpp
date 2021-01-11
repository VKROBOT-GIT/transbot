/*******************************************************************************
* Copyright 2020 VKROBOT CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Jiapeng.feng */

#include "transbot_miniarm_bringup.h"


TransbotMiniarmBringup::TransbotMiniarmBringup()
: nh_(""),
  arm_action_server_(nh_, 
    "arm_controller/follow_joint_trajectory", 
    boost::bind(&TransbotMiniarmBringup::armActionCallback, this, _1), 
    false),
  gripper_action_server_(nh_, 
    "gripper_controller/follow_joint_trajectory", 
    boost::bind(&TransbotMiniarmBringup::gripperActionCallback, this, _1), 
    false)
{
  // Init Publisher
  joint_trajectory_point_pub_ = nh_.advertise<std_msgs::Float64MultiArray>("joint_trajectory_point", 10);
  gripper_pub_ = nh_.advertise<std_msgs::Float64MultiArray>("gripper_position", 10);

  // Start Server
  arm_action_server_.start();
  gripper_action_server_.start();
}

TransbotMiniarmBringup::~TransbotMiniarmBringup() {}

void TransbotMiniarmBringup::armActionCallback(const control_msgs::FollowJointTrajectoryGoalConstPtr &goal)
{
  trajectory_msgs::JointTrajectory jnt_tra = goal->trajectory;
  std_msgs::Float64MultiArray jnt_tra_pts;

  uint32_t jnt_tra_pts_size = jnt_tra.points.size();
  const uint8_t POINTS_STEP_SIZE = 10;
  uint32_t steps = floor((double)jnt_tra_pts_size/(double)POINTS_STEP_SIZE);

  for (uint32_t i = 0; i < jnt_tra_pts_size; i = i + steps)
  {
    jnt_tra_pts.data.push_back(jnt_tra.points[i].time_from_start.toSec());
    for (std::vector<uint32_t>::size_type j = 0; j < jnt_tra.points[i].positions.size(); j++)
    {
      jnt_tra_pts.data.push_back(jnt_tra.points[i].positions[j]);
    }
  }
  joint_trajectory_point_pub_.publish(jnt_tra_pts);

  arm_action_server_.setSucceeded();
}

void TransbotMiniarmBringup::gripperActionCallback(const control_msgs::FollowJointTrajectoryGoalConstPtr &goal)
{
  trajectory_msgs::JointTrajectory jnt_tra = goal->trajectory;
  std_msgs::Float64MultiArray jnt_tra_pts;

  uint32_t jnt_tra_pts_size = jnt_tra.points.size();
  jnt_tra_pts.data.push_back(jnt_tra.points[jnt_tra_pts_size-1].positions[0]);
  gripper_pub_.publish(jnt_tra_pts);

  gripper_action_server_.setSucceeded();
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "transbot_miniarm_bringup");
  TransbotMiniarmBringup transbot_miniarm_bringup;
  ros::spin();
  return 0;
}
