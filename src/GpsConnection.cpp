#include "GpsConnection.hpp"


GpsConnection::GpsConnection(const std::string &host, const std::string &port){
	this->limit_watchdog=10;
	this->_host=host;
	this->_port=port;
}

int GpsConnection::openSocket(){
	this->_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_sockfd < 0){ 
		//ROS_ERROR("ERROR opening socket");
		return GpsConnection::OPEN_SOCKET_ERROR;
	}
	return 0;
}

int GpsConnection::connect_host(){
	this->_server = gethostbyname(this->_host.c_str());
	if (this->_server == NULL) {
		//ROS_ERROR("ERROR, no such host\n");
		return GpsConnection::NO_SUCH_HOST_ERROR;
	}
	bzero((char *) &(this->_serv_addr), sizeof(this->_serv_addr));
	this->_serv_addr.sin_family = AF_INET;
	bcopy((char *)this->_server->h_addr, 
			(char *)&(this->_serv_addr.sin_addr.s_addr),
			this->_server->h_length);
	this->_serv_addr.sin_port = htons(atoi(this->_port.c_str()));
	if (connect(this->_sockfd,(struct sockaddr *) &this->_serv_addr,sizeof(this->_serv_addr)) < 0) 
		return GpsConnection::CONNECTION_ERROR;
		//ROS_ERROR("ERROR connecting");
	return 0;
}


int GpsConnection::reconnect(){
	return (this->disconnect()==0) && (this->openSocket()==0) && (this->connect_host()==0);
}

int GpsConnection::disconnect(){
	return close(this->_sockfd);
}

std::string GpsConnection::read_frame(){
	std::string data;
	char buffer[256];
	int n;
	bzero(buffer,256);
	n = read(this->_sockfd,buffer,255);
	if (n >= 0) {
		data=std::string(buffer);
	}//otherwise return empty string
	return data;
}

std::string GpsConnection::read_line(){
	int watchdog=0;
	std::string data;
	static std::string buffer;
	size_t pos=std::string::npos;
	//in this loop, we copy first copy the previous content of buffer, if any
	//then we successively read and copy data until new line is found.
	while(pos==std::string::npos){
		//copy the content of buffer to data until new line is found (incl. new line)
		pos=buffer.find_first_of('\n');
		if(pos==std::string::npos){
			//\n not found
				data+=buffer;
				buffer=std::string();
		}else{
			//\n found
			data+=buffer.substr(0,pos+1);
			buffer=buffer.substr(pos+1);
		}

		if((buffer.empty()) && (pos==std::string::npos)){
			//read one frame from socket
			buffer=this->read_frame();
			//detects loss of connection
			if(buffer.empty()){
				if(++watchdog>this->limit_watchdog){
					break;
				}
			}else if(watchdog){
				//reset watchdog when data is received
				watchdog=0;
			}
		}
	}
	return data;
}
