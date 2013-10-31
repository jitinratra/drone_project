ROS easy start
==============

I'll try to present ROS so you can do a few things with it, but you need to read and do some tutorials to understand it well.

Installation
----------
Here we'll install a very basic distribution of fuerte, and some dependencies we need:

	apt-get install ros-fuerte-ros-comm ros-fuerte-image-transport-plugins ros-fuerte-image-pipeline

Create a workspace with:

	rosws init ~/fuerte_workspace /opt/ros/fuerte
	source ~/fuerte_workspace/setup.bash

Your workspace is were you will download, create and build code for ROS. To use it in a terminal, you need to source the `setup.bash` file of the workspace.
It's more convenient to add it to your bashrc. You can do it this way:

	echo "source ~/fuerte_workspace/setup.bash" >> ~/.bashrc

You _can_ create a sandbox for developping (the project will _not_ be there, we will create an other packag):

	mkdir ~/fuerte_workspace/sandbox
	rosws set ~/fuerte_workspace/sandbox

cd in the fuerte workspace (with `roscd` for instance, no args) and do :

	rosws set ardrone_autonomy --git https://github.com/AutonomyLab/ardrone_autonomy.git
	rosws update ardrone_autonomy

It will create a package for the driver `ardrone_autonomy` and link it with the git (first line) and update from the repository (second line).

Now build it:

	#cd to the package dir (you'll need to re-source the setup.bash of your workspace to perform this command)
	roscd ardrone_autonomy 
	#build the sdk, this will install some dependencies and may ask for confirmation and sudo password
	./build_sdk.sh
	#build the ros package
	rosmake ardrone_autonomy

Now you can start ros : `roscore`
and start the driver (with the drone connected by WiFi)

	rosrun ardrone_autonomy ardrone_driver


STOP HERE
========


Installation
-----------
First you need to install ROS to use this project.
The version we use is groovy. Just follow the instructions on the [webpage](wiki.ros.org/groovy/Installation) (tip: there is a link to download a virtual machine for virtualbox with ROS already installed)
If you choose to install on your own OS (not with virtualbox), just follow the instructions, and install the desktop-full version of ROS.

Now that ROS is installed, you have to tell your system you are using it: simply source the script provided by ROS to update you path and other environement variables:

	source /opt/ros/hydro/setup.bash

Create a workspace
------------------

All is [here](http://wiki.ros.org/catkin/Tutorials/create_a_workspace).
You will create a folder were we will download, write, and build code.
Source the devel/setup.bash as indicated. You can put this command in your bashrc so it is launched automatically, otherwise you will have to do it in every console you want to use this workspace.

Now you can add packages into your workspace under src (`~/catkin_ws/src` for instance). cd into this folder and

* create a package with `catkin_create_pkg` (see [tutorials](http://wiki.ros.org/ROS/Tutorials))
* download a package from source to build it or modify it (this one for instance: `git clone https://github.com/clems4ever/drone_project.git` )

Building
--------
ROS Groovy comes with a tool called catkin which makes building tasks easy. It uses the CMakelist.txt of the package to know what to build.
When you download a package, (re)build your workspace with `catkin_make` from the root of your workspace (`~/catkin_ws`).
When adding source files, you need to modify the CMakelist.txt to take changes into acount.
Binaries are put in another file, so don't worry if you don't see a build/ or bin/ file in your package after building. You can also forget about adding binaries to gitignore lists or so!
