//adding the required header files:
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

//adding geometry messages:
geometry_msgs::Pose pick;
geometry_msgs::Pose dropit;

//adding visualization:
bool rStatus = true;
bool rgrabbed = false;
visualization_msgs::Marker marker;
visualization_msgs::Marker rMarker;
ros::Publisher marker_pub;

//amcl call back:
void amclCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg) {
    
    const bool rpick = (abs(pick.position.x - msg->pose.pose.position.x) < 1) && (abs(pick.position.y - msg->pose.pose.position.y) < 1);
    const bool rdropit = (abs(dropit.position.x - msg->pose.pose.position.x) <1) && (abs(dropit.position.y - msg->pose.pose.position.y) < 1);
  
//conditional loop:  
  if(rStatus){
        rStatus = false;
        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
        ROS_INFO("virtual object appears at pick location");
     }

    if(rpick && !rgrabbed){
        sleep(5);
        ROS_INFO("virtual object is deleted from pick location");
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        rgrabbed = true;
    	}
  
    if(rdropit && rgrabbed){
        sleep(5);
        ROS_INFO("virtual object appears at drop location");
        marker_pub.publish(rMarker);
    }
}

//starting main:  
  

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  //adding position cordinates for pickup and drop locations:
  pick.position.x = 1.0; // ## x cord of pick loc
  pick.position.y = -5.0; // ## y cord of pick loc
  dropit.position.x = -5.0; // ## x cord of drop loc
  dropit.position.y = -5.0; // ## y cord of drop loc
  
  //adding subscriber comm:
  ros::Subscriber marker_sub = n.subscribe("/amcl_pose",1000,amclCallback);
  
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::SPHERE;
  
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  
  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;
  
  // Set the marker type.  
  marker.type = shape;
  
  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  //marker.action = visualization_msgs::Marker::ADD;
  
  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  
  marker.lifetime = ros::Duration();
  
  // Set the pose of the marker.
  marker.pose.position.x = pick.position.x;
  marker.pose.position.y = pick.position.y;
  
  rMarker = marker;
  rMarker.id = 1;
  rMarker.pose.position.x = dropit.position.x;
  rMarker.pose.position.y = dropit.position.y;
  
  
  //while loop:
  
  while (ros::ok()){
    ros::spinOnce();
    r.sleep();
  }
}