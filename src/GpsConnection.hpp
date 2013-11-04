#ifndef GPS_CONNECTION_H
#define GPS_CONNECTION_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#include <string>
#include <sstream>
#include <iostream>

class GpsConnection
{
	public:
		static const int OPEN_SOCKET_ERROR=1,CONNECTION_ERROR=2,NO_SUCH_HOST_ERROR=3;
	public:
		/** Constructor with host (ip or hostname) and port (service or number)
		 * Do not connect nor open socket
		 */
		GpsConnection(const std::string &host,const std::string &port);

		/** open socket.
		 * \return 0, GpsConnection::OPEN_SOCKET_ERROR on error*/
		int openSocket();
		/** connect to host, as set in constructor.
		 * \return 0, GpsConnection::CONNECTION_ERROR or GpsConnection::NO_SUCH_HOST_ERROR on error*/
		int connect_host();
		/** disconnect and reconnect.
		 * equivalent to succesive calls of disconnect(), openSocket() and connect_host()*/
		int reconnect();
		/** deconnect */
		int disconnect();

		/** read one frame and returns it.
		 * string is empty on error.
		 * Reads only one TCP frame
		 */
		std::string read_frame();

		/**
		 * \warning do not use in concurrence with GpsConnection::read(), you may loose data
		 */
		std::string read_line();

		int limit_watchdog;

	private:
		std::string  _host;
		std::string _port;
		int _sockfd;
		struct sockaddr_in _serv_addr;
		struct hostent *_server;
};

#endif // GPS_CONNECTION_H
