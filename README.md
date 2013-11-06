drone\_project
=============

Implement autopilot to Parrot AR.Drone to allow it to move from point A to point B avoiding all the obstacles.

Installation
-----------
### Pre-requirements
#### Install ROS
First you need to install ROS to use this SUMMARY
project.
The version we use is groovy. Just follow the instructions on the [webpage](http://wiki.ros.org/groovy/Installation) (tip: there is a link to download a virtual machine for virtualbox with ROS already installed)
If you choose to install on your own OS (not with virtualbox), just follow the instructions, and install the desktop-full version of ROS.

You can take a look to some [tutorials](http://wiki.ros.org/ROS/Tutorials) to understand what is ROS and what it's made of.

#### Install ardrone\_autonomy driver
It's the driver to interface the ARDrone with ROS.
Info is [here](https://github.com/AutonomyLab/ardrone_autonomy#ardrone_autonomy--a-ros-driver-for-ardrone-10--20)

#### Install tum_ardrone


	# cd into ros root dir
	roscd

	# clone repository
	git clone https://github.com/tum-vision/tum_ardrone.git
	
	# add to ros path (if required)
	export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:`pwd`/tum_ardrone
	
	# download lib
	sudo apt-get install libblas-dev
	sudo apt-get install liblapack-dev
	
	#In the file Navata.msg in the folder ardrone_autonomy/msg Add this lines : 
	#motor commands (unit 0 to 255)
	uint8 motor1
	uint8 motor2
	uint8 motor3
	uint8 motor4

	# build package (may take up to 10 minutes)
	rosmake tum_ardrone


#### run tum_ardrone


	# run driver
	rosrun ardrone_autonomy ardrone_driver
  
	# if unknown command
	export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:`pwd`/tum_ardrone
	
	# run stateestimation node
	rosrun tum_ardrone drone_stateestimation
  
	# run autopilot node
	rosrun tum_ardrone drone_autopilot
  
	# run gui node
	rosrun tum_ardrone drone_gui



#### Other mandatory dependencies

- `gpsd` (ubuntu repo)
- `gpsd_client` : http://wiki.ros.org/gpsd_client

		$ cd ~/fuerte_workspace/sandbox
		$ git clone -b fuerte_released https://github.com/ktossell/gps_umd.git
		$ rosstack profile && rospack profile
		$ rosmake gps_umd

- `ar_track_alvar` : http://wiki.ros.org/ar_track_alvar
