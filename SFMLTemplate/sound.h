//Kelvin Ip 100489417

#pragma once
#ifndef NUM_CHANNELS
#define NUM_CHANNELS 32
#endif
#include <iostream>
#include "fmod/fmod.hpp"

class sound {
public: FMOD::System *fmodSystem;
		FMOD_RESULT result;
		char name[256];
		//channel
		FMOD::Channel *channel;
		//not very creative sound name
		FMOD::Sound *Dawg;
		//position of listener
		FMOD_VECTOR listenerpos;
		//location of sound source
		FMOD_VECTOR soundlocation;
		//velocity of listener *will stay 0
		FMOD_VECTOR listenervel;
		//toggler for rolloff
		bool rollOff;
		//starting
		void initialize();
		//updating location of sound
		void updatelocation(float x, float y, float z);
		//passes in sound name so the appropriate sound can be played
		void load(const char* filename);
		//updates the position of the sound
		void update();
		//plays
		void playDawg();
		//toggler for rolloff
		void toggle();

		void setLoop (bool loop);

		void release ();
};