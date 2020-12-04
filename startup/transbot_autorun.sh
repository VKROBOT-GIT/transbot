#! /bin/bash
source /opt/ros/melodic/setup.bash
source /home/vktransbot/transbot_ws/devel/setup.bash
source /home/vktransbot/.bashrc
export ROS_MASTER_URI=http://192.168.1.100:11311
export ROS_HOSTNAME=192.168.1.100

gnome-terminal --geometry=80x10+350+0 --title="ROS turtlebot3 robot" -x roslaunch turtlebot3_bringup turtlebot3_robot.launch   #start turtlebot3


