#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  //code for moving the robot to the location for picking up the virtual object
  move_base_msgs::MoveBaseGoal pick;

  // set up the frame parameters
  pick.target_pose.header.frame_id = "map";
  pick.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pick.target_pose.pose.position.x = 1.0;
  pick.target_pose.pose.position.y = -5.0;
  pick.target_pose.pose.orientation.z = 1.0;
  pick.target_pose.pose.orientation.w = 0.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending to the location for picking up object");
  ac.sendGoal(pick);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base reached the location for picking up virtual object");
    ros::Duration(5).sleep();
    ROS_INFO("Hooray, the robot picked up");
  	}
  else
    ROS_INFO("Oops!, The base failed to reach the location for picking up virtual object");
  
  //end of coding part for sending the pickup message
  
  //add a little duration inorder to pick the virtual object
  //ros::Duration(5.0).sleep();
  
  
  
  //code for moving the robot to the location for dropping the virtual object
  
  move_base_msgs::MoveBaseGoal dropit;

  // set up the frame parameters
  dropit.target_pose.header.frame_id = "map";
  dropit.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  dropit.target_pose.pose.position.x = -5.0;
  dropit.target_pose.pose.position.y = -5.0;
  dropit.target_pose.pose.orientation.z = 0.0;
  dropit.target_pose.pose.orientation.w = 0.4;
  
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending to the location for dropping object");
  ac.sendGoal(dropit);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base reached the location for dropping the virtual object");
  else
    ROS_INFO("Oops!, The base failed to reach the location for dropping virtual object");
  

  return 0;
}