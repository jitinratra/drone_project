/**
 * author : Jules Waldhart
 * INSA Toulouse
 */

#include "gps_conv.h"
/* warning : approximations
 * approximation due to consideration of shperical earth
 * and to approximated values (pi, earth radius...)
 */

/** converts from format dddmm.mmmm to radians
 */
double degreesMinutesToDegrees(double value){
	double deg=0,min=0;
	deg=floor(value/100); //from format ddmm.mmmm gets dd and put it in deg
	//compute decimal part of degrees from minutes
	min=value/100-deg;
	deg=deg+min*100/60;
	return deg;
}

GeoPoint analyseGpsGga(char * data){
	GeoPoint point;
	char * result;
	char delims[]=",";
	char plizproceed=1;
	char step=0;
	double value=0;
	result=strtok(data,delims);
	if(strncmp(result,"$GPGGA",MAX_STR_LEN)==0){
		//ok it's a GPGGA string
	}else plizproceed=0;

	while((plizproceed)&&(result=strtok(NULL,delims))){
		errno=0;
		switch (step){
			case 0:
				//time
				if((value=atof(result))!=0){
					//do nothing
				}else plizproceed=0;
				break;
			case 1:
				//latitude
				if(((value=strtod(result,NULL))!=0)||(errno==ERANGE)){
					point.latitude=degreesMinutesToDegrees(value);
				}else plizproceed=0;
				break;
			case 2:
				//north or south
				if(strncmp(result,"S",MAX_STR_LEN)==0){
					point.latitude=-point.latitude;
				} 
				break;
			case 3:
				//latitude
				if(((value=strtod(result,NULL))!=0)||(errno==ERANGE)){
					point.longitude=degreesMinutesToDegrees(value);
				}else plizproceed=0;
				break;
			case 4:
				//east or west
				if(strncmp(result,"E",MAX_STR_LEN)==0){
					point.longitude=-point.longitude;
				} 
				break;
			default:
				plizproceed=0;
		}
		++step;
	}
	return point;
}

double distance(const GeoPoint *a, const GeoPoint *b){
	double t1,t2,t3,t4,t5,rad_dist;
	t1 = sin(a->latitude*PI/180) * sin(b->latitude*PI/180);
	t2 = cos(a->latitude*PI/180) * cos(b->latitude*PI/180);
	t3 = cos(a->longitude*PI/180 - b->longitude*PI/180);
	t4 = t2 * t3;
	t5 = t1 + t4;
	rad_dist = atan(-t5/sqrt(-t5 * t5 +1)) + 2 * atan(1);
	return (rad_dist * 3437.74677 * 1.1508) * 1.6093470878864446 *1000;
}

void test_distance(){
	short int nb_pts=7,i=0;
	GeoPoint pointsA[nb_pts], pointsB[nb_pts];

	pointsA[0].latitude = 0;
	pointsA[0].longitude = 0;

	pointsB[0].latitude = 0;
	pointsB[0].longitude = 180;

	pointsA[1].latitude = 45;
	pointsA[1].longitude = 0;

	pointsB[1].latitude = 45;
	pointsB[1].longitude = 180;

	pointsA[2].latitude = 45;
	pointsA[2].longitude = 0;

	pointsB[2].latitude = 45;
	pointsB[2].longitude = 90;

	pointsA[3].latitude = 43.545148;
	pointsA[3].longitude = 1.473478;

	pointsB[3].latitude = 43.545110;
	pointsB[3].longitude = 1.473234;

	pointsA[4].latitude = 45;
	pointsA[4].longitude =179.9999999;

	pointsB[4].latitude = 45;
	pointsB[4].longitude =-179.9999999;

	pointsA[5].latitude = 0;
	pointsA[5].longitude =179;

	pointsB[5].latitude = 0;
	pointsB[5].longitude =-179;

	pointsA[6].latitude = 0;
	pointsA[6].longitude =179.999999;

	pointsB[6].latitude = 0;
	pointsB[6].longitude =-179.999999;

	for(i=0;i<nb_pts;i++){
		printf("%d : distance = %f meters\n",i,distance(&pointsA[i],&pointsB[i]));
	}
	printf("end test\n");
}
