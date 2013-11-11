GPS How To
=========

Here we will present how to use your GPS. First, be sure to have installed all required packages (see main README file).

On-board GPS
-----------

The GPS chip is not a default component of the drone. We use a GPS chip combined with an Arduino to communicate with the drone's system.

Communication
-------------

The communication is made via Wifi, with TCP.

		cat /dev/ttyACMO | netcat -lk <port>

TODO detail this 2 sections

Reception
---------
`gpsd` handles TCP communication for it's devices. Simply launch gpsd with the drone's ip and port corresponding to the gps:

		gpsd tcp://192.168.0.1:<port> -b
TODO : not sure for the drone's address

Nota: `-b` options forbids gpsd to send data to the gps, as our solution for gps (arduino + gps chip) wasn't made to support it.

ROS `gpsd_client`
----------------
		rosrun gpsd_client gpsd_client _use_gps_time:=false

ROS gps odometry
----------------
The ROS package `gps_common` provided with the package `gpsd_client` implements a node for converting GPS data to ROS standard UTM odometry messages.

		rosrun gps_common utm_odometry_node

Troubleshooting
---------------

Errors may occur when launching the ros node `gpsd_client` . Simply try to relaunch it once or twice. When launched successfully, it runs well.

If error persists, you can run `gpsmon` (from linux package `gpsd-clients`) to see if the data received by gpsd is OK.
