#include <SoftwareSerial.h>

//#define CONTROL_CHECKSUM
#define GPS_10_HZ
#define BYTE_TO_BYTE

#define STR_LEN_MAX 100
#define STR_BUFF_MAX 15

// GPS PINS
#define SoftrxPin 2
#define SofttxPin 3
// SRF PINS
#define ECHOPIN1 3                            // Pin to receive echo pulse
#define TRIGPIN1 4                             // Pin to send trigger pulse
#define ECHOPIN2 5                            // Pin to receive echo pulse
#define TRIGPIN2 6                             // Pin to send trigger pulse

// initialisation de la liasion série
SoftwareSerial gps = SoftwareSerial(SoftrxPin, SofttxPin);
// variables
byte byteGPS = 0;

char *last_header = "VTG";

#ifdef CONTROL_CHECKSUM
char chartoval(char c){
	if((c >=48) && (c<=57)){
		//it's a digit (0-9)
		return c-48;
	}else if((c>=65)&&(c<=70)){
		//it's a letter A-F
		return c-65+10;
	}else{
		return -1;
	}
}

char checksum(char *s) {
	char c = 0;

	s++;
	while(*s!='*')
		c ^= *s++;

	if(c!=chartoval(*(++s))*16+chartoval(*(++s))){
		c=0;
	}else{
		c=1;
	}

	return c;
}
#endif


void setup(){
	Serial.begin(115200);// ouvre le port série et règle le debit à 115200 bps
	gps.begin(9600);	// open gps SoftwareSerial port at 9600 bauds (default)
	pinMode(SoftrxPin, INPUT);
#ifdef GPS_10_HZ
	gps.println("$PMTK251,38400*27"); //ask GPS to comunicate at 38.4 kbauds
	delay(200);
	gps.begin(38400); //change Software Serial baudrate after some time
	gps.println("$PMTK226,3,30*4"); //ask gps to update at 10Hz
#endif //GPS_10_HZ
}

void loop(){
#ifndef BYTE_TO_BYTE
	static char str_buff[STR_BUFF_MAX][STR_LEN_MAX];
	char buff;
	static int i=0,char_i=0,str_i=0;
	static int decompteOk=0;
#endif

	if(gps.available()!=0){
#ifdef BYTE_TO_BYTE
		Serial.write(gps.read());
#else
		str_buff[str_i][char_i]=gps.read();
		if((str_buff[str_i][char_i++]=='\n')||(char_i>=STR_LEN_MAX-1)){
			str_buff[str_i][char_i]=0;
			//check if it's the last string to receive
			decompteOk=3;
			for(char_i=0;char_i<3;char_i++){
				if(str_buff[str_i][char_i+3]==last_header[char_i]){
					decompteOk--;
				}
			}

#ifdef CONTROL_CHECKSUM
			if(checksum(str_buff[str_i])==0){
				//Serial.println("ERRORCHECKSUM");
				//do not transmit == do not increment str_i : will be overwritten or not transmitted
			}else
#endif //CONTROL_CHECKSUM
			{
				str_i++;
				if(str_i>=STR_BUFF_MAX){
					str_i--;
				}
			}
		char_i=0;
		}
	}else if (decompteOk==0){
		//transmit everything now:
		for (i=0;i<str_i;i++){
			Serial.print(str_buff[i]);
		}
		str_i=0;
		decompteOk=-1;
#endif //BYTE_TO_BYTE
	}

}

