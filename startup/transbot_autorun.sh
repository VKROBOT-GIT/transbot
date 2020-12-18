#! /bin/bash
source /opt/ros/melodic/setup.bash
source /home/transbot/transbot_ws/devel/setup.bash
export TRANSBOT_MODEL=normal
export ROS_MASTER_URI=http://192.168.1.100:11311
export ROS_HOSTNAME=192.168.1.100

gnome-terminal --geometry=80x10+350+0 --title="ROS CORE" -x roscore #start transbot
sleep 5s
gnome-terminal --geometry=80x10+350+0 --title="ROS Transbot Bringup" -x roslaunch transbot_bringup transbot_robot.launch   #start transbot bringup
sleep 10s
gnome-terminal --geometry=80x10+350+0 --title="ROS Transbot SLAM" -x roslaunch transbot_slam transbot_slam.launch   #start transbot slam


