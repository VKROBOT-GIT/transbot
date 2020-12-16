#! /bin/bash
source /opt/ros/melodic/setup.bash
source /home/transbot/transbot_ws/devel/setup.bash
export ROS_MASTER_URI=http://192.168.1.100:11311
export ROS_HOSTNAME=192.168.1.100

gnome-terminal --geometry=80x10+350+0 --title="ROS CORE" -x roslaunch turtlebot3_bringup transbot_robot.launch   #start transbot
gnome-terminal --geometry=80x10+350+0 --title="ROS Transbot Bringup" -x roslaunch turtlebot3_bringup transbot_robot.launch   #start transbot bringup
gnome-terminal --geometry=80x10+350+0 --title="ROS Transbot SLAM" -x roslaunch turtlebotslam transbot_slam.launch   #start transbot slam


