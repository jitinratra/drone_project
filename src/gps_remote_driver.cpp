#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sstream>

#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"

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
	int sockfd, portno, n=0;
	struct sockaddr_in serv_addr;
	struct hostent *server;


	ros::init(argc,argv,"gps_remote_driver");
	ros::NodeHandle nh;

	ros::Publisher navdataPub= nh.advertise<sensor_msgs::NavSatFix>("gps",10);

	char buffer[256];
	char buffer2[256*4];
	if (argc < 3) {
		ROS_ERROR("usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		ROS_ERROR("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		ROS_ERROR("ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		ROS_ERROR("ERROR connecting");
	//printf("Please enter the message: ");
	//bzero(buffer,256);
	//fgets(buffer,255,stdin);
	//n = write(sockfd,buffer,strlen(buffer));

	int i=0,i2=0;
	while(ros::ok()){
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if (n < 0) {
			ROS_ERROR("ERROR reading from socket");
			break;
		}else if(n==0){
			ROS_WARN("nothing received");
		}
		i=0;
		ROS_INFO("\t\treceived %s",buffer);
		while((buffer[i]!='\0') && (i<static_cast<int>(sizeof(buffer)))){
			//put char in buffer2
			buffer2[i2]=buffer[i];
			if((buffer2[i2]=='\n') || (i2>=static_cast<int>(sizeof(buffer2))-1)){
				//we received an entire NMEA frame, go converting it
				buffer[i2+1]='\0';
				ROS_INFO(buffer2);
				if ( std::string(buffer2).find("$GPGGA") == 0){
					convert_and_pub(buffer2,navdataPub);
				}
				bzero(buffer2,256*4);
				i2=-1;
			}
			i++;
			i2++;
		}
	}
	close(sockfd);
	return 0;
}
