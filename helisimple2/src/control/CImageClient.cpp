#include "CImageClient.h"

#define NETWORK_BLOCK MSG_WAITALL

CImageClient::CImageClient(sem_t *im)
{
	imageSem = im;	
	stop=stopped=false;
}

void CImageClient::run(CRawImage *im)
{
	image  = im;
	codec = new CDecoder(imageSem,im);
	thread = SDL_CreateThread(StartThread,static_cast<void*>(this));
}

CImageClient::~CImageClient()
{
	stop = true;
	int wait = 10;
	while (stopped == false && wait > 0){
	       	usleep(100000);
		wait--;
	}
	close(socketNumber);
	delete codec;
}

int CImageClient::connectServer(const char * ip,const char* port)
{
  int result = -1;
  socketNumber = socket(AF_INET, SOCK_STREAM, 0);
  if (socketNumber <0 )
  {
    return -1;
  }
  struct sockaddr_in server_addr;
  struct hostent *host_info;
  host_info =  gethostbyname(ip);
  if (host_info != NULL)
  {
    server_addr.sin_family = host_info->h_addrtype;
    memcpy((char *) &server_addr.sin_addr.s_addr,
           host_info->h_addr_list[0], host_info->h_length);
    server_addr.sin_port = htons(atoi(port));
    fprintf(stdout,"Connecting to %s:%s \n",ip,port);
    result = connect(socketNumber,(struct sockaddr*) &server_addr,sizeof(server_addr));
    if (result == 0)
    {
      fprintf(stderr,"Connection established.\n");
    }
    else
    {
      fprintf(stderr,"Connect error is %s \n",strerror(errno));
    }
  }
  return result;
}

int CImageClient::DoExecute()
{
	unsigned char buf[100000];
	parrot_video_encapsulation_t pave;
	int lengthReceived;
	int i=0;
	int numRuns = 0;
	while (stop == false){
		bool pavedetected = false;
		lengthReceived = recv(socketNumber,&buf,64,NETWORK_BLOCK);
		if (memcmp(buf,"PaVE",4)!=0){
			fprintf(stdout,"Sync lost \n");
			while (pavedetected == false){
				lengthReceived = recv(socketNumber,&buf,1000,NETWORK_BLOCK);
				i=0;
				for (i = 0;i<lengthReceived-64 && pavedetected == false;i++){
					pavedetected = (memcmp(&buf[i],"PaVE",4)==0);
				}
			}
			i--;
		}
//		fprintf(stdout,"Pave %c%c%c%c detected at %i - ",buf[i],buf[i+1],buf[i+2],buf[i+3],i);
		memcpy(&pave,&buf[i],64);
//		fprintf(stdout,"%c%c%c%c: %05i - %ix%i - %i\n",pave.signature[0],pave.signature[1],pave.signature[2],pave.signature[3],pave.payload_size,pave.encoded_stream_width,pave.encoded_stream_height,pave.frame_type);
		lengthReceived = recv(socketNumber,buf,pave.payload_size,NETWORK_BLOCK);
		codec->decode(buf,lengthReceived,pave.frame_type);
		numRuns++;
	}
	stopped = true;
	return numRuns;
}

