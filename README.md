# RoboND-HomeServiceRobot
This is the final project of Udacity Nano Degree Program Robotics Software Engineer. 

## Implementation:

Firstly, upgrade the system using the following command:
	sudo apt-get update && apt-get upgrade

This is followed by creating a shellscript launch.sh file

The commands in this file is executed by a single command:

		chmod +x launch.sh
		./launch.sh
        
## Installation of Packages:

The following packages are installed using the link provided in the tutorial.

	1.gmapping
	2.turtlebot_teleop
	3.turtlebot_rviz_launchers
	4.turtlebot_gazebo

## Creating Packages for pickup and addmarkers:

Packages for picking virtual objects and marking them are created using the following command:

		catkin_create_pkg <packagename>
  
Required shell scripts are created as instructed in the tutorial. 
  
Add pick_object.cpp and add_markers.cpp nodes and edit them as instructed in the tutorial.
Then, test the program and check the results.
  
Finally, create home_service.sh file which launches turtlebot, AMCL, rviz config file, pickup and add markers nodes  