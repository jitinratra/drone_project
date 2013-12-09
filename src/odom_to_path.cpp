#include "ros/ros.h"
#include "nav_msgs/Path.h"
#include "nav_msgs/Odometry.h"

ros::Publisher pathPub;

void odomCB(const nav_msgs::Odometry::ConstPtr& odom)
{
	static nav_msgs::Path pathMsg;
	geometry_msgs::PoseStamped poseMsg;

	poseMsg.header = odom->header;
	poseMsg.pose = odom->pose.pose;

	pathMsg.header = odom->header;
	pathMsg.poses.push_back(poseMsg);

	pathPub.publish(pathMsg);

	return;
}


int main(int argc, char *argv[])
{


	ros::init(argc,argv,"odom_to_path");
	ros::NodeHandle nh;

	pathPub=nh.advertise<nav_msgs::Path>("path",10);

  ros::Subscriber sub = nh.subscribe("odom", 20, odomCB);
	
  ros::spin();

	return 0;
}
		
