drone\_project
=============

Implement autopilot to Parrot AR.Drone to allow it to move from point A to point B avoiding all the obstacles.

Installation
-----------
### Pre-requirements
#### Install ROS
First you need to install ROS to use this project.
The version we use is groovy. Just follow the instructions on the [webpage](http://wiki.ros.org/groovy/Installation) (tip: there is a link to download a virtual machine for virtualbox with ROS already installed)
If you choose to install on your own OS (not with virtualbox), just follow the instructions, and install the desktop-full version of ROS.

You can take a look to some [tutorials](http://wiki.ros.org/ROS/Tutorials) to understand what is ROS and what it's made of.

#### Install ardrone\_autonomy driver
It's the driver to interface the ARDrone with ROS.
Info is [here](https://github.com/AutonomyLab/ardrone_autonomy#ardrone_autonomy--a-ros-driver-for-ardrone-10--20)

#### Other mandatory dependencies

- `gpsd_client` : http://wiki.ros.org/gpsd_client
- `ar_track_alvar` : http://wiki.ros.org/ar_track_alvar
