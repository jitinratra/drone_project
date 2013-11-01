/**
 * \file testusb.c
 * \brief Test d'une communication par XBee sur un AR Drone 2.0
 * \author S. Di Mercurio et P.-E. Hladik
 * \modif J. Waldhart
 * \version 0.1
 * \date septembre 2012
 * \modif oct. 2013
 *
 * Test d'une communication XBee sur AR Drone
 * => communication serial GPS vers ROS topics
 *
 */

#include <stdio.h> /* Standard input/output definitions */
#include <string.h> /* String function definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>

//for ROS
#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int i;
char c;
int com_fd;

char *RobotComFilename = "/dev/ttyACM0";

/* Variable pour select */
fd_set set;
struct timeval timeout;

int d_robot_open_device(void) {
	struct termios options;

	int fd; /* File descriptor for the port */
	fd = open(RobotComFilename, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		/* Could not open the port. */
		fprintf(stderr, "[Error %d] : Can't open device file %s\n", -1, RobotComFilename);
		return -1;
	} else {
		printf("Opened %s successfully\n", RobotComFilename);
	}
	fcntl(fd, F_SETFL, FNDELAY);
	/* Get the current options for the port...  */
	tcgetattr(fd, &options);
	/*Set the baud rates to 9600 bauds 8N1, no hardware flow control... */
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CRTSCTS;
	/* Enable the receiver and set local mode...  */
	options.c_cflag |= (CLOCAL | CREAD);
	/* Set the new options for the port... */
	tcsetattr(fd, TCSANOW, &options);
	com_fd = fd;
	/* Initialize the file descriptor set. */
	FD_ZERO(&set);
	FD_SET(fd, &set);
	/* Initialize the timeout data structure. */
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;

	return 1;
}

void d_robot_send_char( char c) {
	write(com_fd, &c, 1);
}

void d_robot_get_char(char *c) {
	int n;
	int delay;

	delay = 0;
	n = 0;

	while (n <= 0) {
		n = read(com_fd, c, 1);
		if (n <= 0) {
			delay++;
			usleep(5000);
		}
	}
}

int main (void)
{
	char data;
	ros::NodeHandle nh;

	ros::init(argc,argv,"gps_serial_driver");

	ros::Publisher gps_text = nh.advertise<std_msgs::String>("gps_text",10);

	ROS_INFO("c'est partit");
	d_robot_open_device();

	while (1)
	{
		d_robot_get_char(&data);
		printf ("%c", data);
		ROS_INFO("%c",data);
	}	
	return 0;
}
