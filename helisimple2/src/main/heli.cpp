#include <stdlib.h>
#include "CGui.h"
#include "CRecognition.h"
#include "CHeli.h"

int i = 0;
int numSaved = 0;
bool stop = false;
CGui* gui;
CRawImage *image;
SDL_Event event;
CRecognition *recognition;
SPixelPosition pos;
bool move = false;
Uint8 lastKeys[10000];
int keyNumber = 10000;
Uint8 *keys = NULL;
CHeli *heli;
float pitch,roll,yaw,height;
SDL_Joystick* joystick;
TJoyState joy,lastJoy;

void processJoystick()
{	
	SDL_JoystickUpdate();
	printf("Joystick ");
	for (int i = 0;i<6;i++){
		joy.axis[i] = SDL_JoystickGetAxis (joystick, i);
		printf("%i ",joy.axis[i]);
		if (fabs(joy.axis[i]) < 20) joy.axis[i] = 0;
	}
	for (int i = 0;i<11;i++){
		 joy.buttons[i+1] =  SDL_JoystickGetButton (joystick,i);
	}
	printf("\n");
	roll	= joy.axis[0];	
	pitch 	= joy.axis[1];
	yaw 	= joy.axis[2];
	height 	= joy.axis[3];

	if (joy.buttons[7] && lastJoy.buttons[7] == false) heli->takeoff();
	if (joy.buttons[5] && lastJoy.buttons[5] == false) heli->land();
	for (int i = 1;i<5;i++){
		if (joy.buttons[i] && lastJoy.buttons[i]==false) heli->switchCamera(i-1);
	}
	lastJoy = joy;
}

void processKeys()
{
	while (SDL_PollEvent(&event)){
		if (event.type == SDL_MOUSEBUTTONDOWN) recognition->learnPixel(&image->data[3*(image->width*event.motion.y + event.motion.x)]);
	}
	keys = SDL_GetKeyState(&keyNumber);
	if (keys[SDLK_ESCAPE]) stop = true;
	if (keys[SDLK_r]) recognition->resetColorMap();
	if (keys[SDLK_RETURN])image->saveBmp();

	/* Old command
	if (keys[SDLK_KP7])  yaw = -20000.0;	
	if (keys[SDLK_KP9])  yaw = 20000.0;	
	if (keys[SDLK_KP4])  roll = -20000.0;
	if (keys[SDLK_KP6])  roll = 20000.0;
	if (keys[SDLK_KP8])  pitch = -20000.0;
	if (keys[SDLK_KP2])  pitch = 20000.0;
	if (keys[SDLK_KP_PLUS])  height = 20000.0;
	if (keys[SDLK_KP_MINUS])  height = -20000.0;
	*/

	// Yves's commands
	if (keys[SDLK_a])  yaw = -20000.0;
	if (keys[SDLK_e])  yaw = 20000.0;
	if (keys[SDLK_q])  roll = -20000.0;
	if (keys[SDLK_d])  roll = 20000.0;
	if (keys[SDLK_z])  pitch = -20000.0;
	if (keys[SDLK_s])  pitch = 20000.0;
	if (keys[SDLK_j])  height = 20000.0;
	if (keys[SDLK_n])  height = -20000.0;

	//changes camera
	/* Old	
	if (keys[SDLK_z]) heli->switchCamera(0);
	if (keys[SDLK_x]) heli->switchCamera(1);
	if (keys[SDLK_c]) heli->switchCamera(2);
	if (keys[SDLK_v]) heli->switchCamera(3);

	if (keys[SDLK_q]) heli->takeoff();
	if (keys[SDLK_a]) heli->land();
	*/
	
	// Yves's commands
	if (keys[SDLK_u]) heli->switchCamera(0);
	if (keys[SDLK_i]) heli->switchCamera(1);
	if (keys[SDLK_o]) heli->switchCamera(2);
	if (keys[SDLK_p]) heli->switchCamera(3);

	if (keys[SDLK_m]) heli->takeoff();
	if (keys[SDLK_l]) heli->land();
	
	memcpy(lastKeys,keys,keyNumber);
}

int main(int argc,char* argv[])
{
	//initializing stuff	
	heli = new CHeli();
	gui = new CGui(640,368);

	//opening joystick - modify the number if needed 
	joystick = SDL_JoystickOpen(0);
	fprintf(stdout,"Joystick with %i axes, %i buttons and %i hats initialized.\n",SDL_JoystickNumAxes(joystick),SDL_JoystickNumButtons(joystick),SDL_JoystickNumHats(joystick));

	//this class holds the image	
	image = new CRawImage(640,368);
	recognition = new CRecognition();
	image->getSaveNumber();

	while (stop == false){
		fprintf(stdout,"Angles %.2lf %.2lf %.2lf ",helidata.phi,helidata.psi,helidata.theta);
		fprintf(stdout,"Speeds %.2lf %.2lf %.2lf ",helidata.vx,helidata.vy,helidata.vz);
		fprintf(stdout,"Battery %.0lf ",helidata.battery);
		fprintf(stdout,"Largest blob %i %i\n",pos.x,pos.y);

		//image capture 
		heli->renewImage(image);
		processJoystick();
		processKeys();
		heli->setAngles(pitch,roll,yaw,height);
		//image->saveBmp();

		//finding a blob in the image 
		pitch=roll=yaw=height=0.0;
		pos = recognition->findSegment(image);

		//turns the drone towards the colored blob 
		//yaw = 100*(pos.x-160); //uncomment to make the drone to turn towards a colored target

		//drawing the image, the cross etc.
		image->plotLine(pos.x,pos.y);
		image->plotCenter();
		gui->drawImage(image);
		gui->update();	
		i++;

		usleep(20000);
	}
	delete recognition;
	delete heli;
	delete image;
	delete gui;
	return 0;
}

