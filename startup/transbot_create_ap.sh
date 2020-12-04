#! /bin/bash
gnome-terminal --geometry=80x10+350+0 --title="ROS transbot creat_ap" -e "bash -c \"echo vktransbot |sudo -S create_ap -n wlan0 Transbot_ap vktransbot ; read \""     #start transbot wifi ap
