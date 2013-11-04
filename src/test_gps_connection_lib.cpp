#include <stdio.h>
#include <stdlib.h>

#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"

//tools for communication with gps via tcp
#include "GpsConnection.hpp"
//gps conversion tools
#include "./gps_conv.h"


void convert_and_pub(char *data,ros::Publisher &publisher){
	sensor_msgs::NavSatFix msgNav;
	msgNav.header.stamp = ros::Time::now();
	msgNav.header.frame_id="/ardrone/gps_antenna";

	degreesMinutesToDegrees(81.1);
	GeoPoint position = analyseGpsGga(data);

	//msgNav.status ?

	// Latitude [degrees]. Positive is north of equator; negative is south.
	msgNav.latitude = position.latitude;

	// Longitude [degrees]. Positive is east of prime meridian; negative is west.
	msgNav.longitude = position.longitude;

	// Altitude [m]. Positive is above the WGS 84 ellipsoid
	// (quiet NaN if no altitude is available).
	//msgNav.altitude;

	// Position covariance [m^2] defined relative to a tangential plane
	// through the reported position. The components are East, North, and
	// Up (ENU), in row-major order.
	//
	// Beware: this coordinate system exhibits singularities at the poles.

	//msgNav.position_covariance;

	// If the covariance of the fix is known, fill it in completely. If the
	// GPS receiver provides the variance of each measurement, put them
	// along the diagonal. If only Dilution of Precision is available,
	// estimate an approximate covariance from that.

	msgNav.position_covariance_type=msgNav.COVARIANCE_TYPE_UNKNOWN;

	publisher.publish(msgNav);
	return;
}


int main(int argc, char *argv[])
{

	int err;
	ros::init(argc,argv,"gps_remote_driver");
	ros::NodeHandle nh;

	ros::Publisher navdataPub= nh.advertise<sensor_msgs::NavSatFix>("gps",10);

	if (argc < 3) {
		ROS_ERROR("usage %s hostname port\n", argv[0]);
		exit(0);
	}

	std::string host(argv[1]), port(argv[2]);
	GpsConnection gps_conn(host,port);

	if((err=gps_conn.openSocket())!=0){
		ROS_ERROR("could not open socket");
		exit(err);
	}
	ROS_INFO("socket OK");

	if((err=gps_conn.connect_host())!=0){
		ROS_ERROR("could not connect to host");
		exit(err);
	}
	ROS_INFO("connection OK");

	while(ros::ok()){
		std::string data=gps_conn.read_line();
		if(data.empty()){
			ROS_WARN("connection lost");
			ROS_INFO("re connecting...");
			gps_conn.reconnect();
			ROS_INFO("RE-connection OK");
		}else{
			std::cout << data;
		}

	}

	return 0;
}

