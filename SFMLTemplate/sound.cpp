//Kelvin Ip 100489417

#include "sound.h"
#include <time.h>
#include <string>
//initialization of listener position and velocity and setting rolloff to logerithmic
void sound::initialize(){
	result = System_Create(&fmodSystem);
	result = fmodSystem->init(NUM_CHANNELS, FMOD_INIT_NORMAL, 0);
	//listener position at origin
	listenerpos.x=0;
	listenerpos.y=0;
	listenerpos.z=0;
	//will not move so velociity set at 0
	listenervel.x=0;
	listenervel.y=0;
	listenervel.z=0;
	//set logerithmic rolloff
	rollOff= true;
}
//load sound Dawg
//taking in fileName as string and converting to const char*
void sound::load(const char* filename){
	result = fmodSystem->createSound(filename, FMOD_LOOP_NORMAL|FMOD_3D, 0, &Dawg);
	//Loop enabled for testing

	Dawg->setMode (FMOD_LOOP_OFF);

	channel->set3DMinMaxDistance(5,250);
}

void sound::update(){
	fmodSystem->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
	channel->set3DAttributes(&soundlocation, 0);
result = fmodSystem->update();
// roll off model for logarithmic and linear
if (rollOff)
channel->setMode(FMOD_3D_INVERSEROLLOFF);
//linear does not seem to change but most likely due to Min and Max distance
else
channel->setMode(FMOD_3D_LINEARROLLOFF);
}

//play sound
void sound::playDawg(){
	result = fmodSystem->playSound(FMOD_CHANNEL_FREE, Dawg, false, &channel);
}
//update location of sound 
void sound::updatelocation(float x, float y, float z){
soundlocation.x=x;
soundlocation.y=y;
soundlocation.z=z;
}
//toggle between log and linear 
void sound::toggle(){
rollOff = !rollOff;
}

void sound::setLoop( bool loop )
{
	if (loop)
		Dawg->setMode (FMOD_LOOP_NORMAL);
	else
		Dawg->setMode (FMOD_LOOP_OFF);
}

void sound::release()
{
	channel->stop();
	Dawg->release();
	fmodSystem->release();
}
