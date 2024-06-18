#pragma once
#include "SDL_mixer.h"
#include <string>

enum AudioType
{
	SOUNDEFFECT,
	MUSIC,
};

class Audio
{
private:
	Mix_Chunk* soundEffect; //A Sound Effect
	Mix_Music* music; //Music

	AudioType type; //The Type of audio 

public:
	Audio(std::string path, AudioType type);
	~Audio();

	void PlayAudio(int loop); //Plays the Audio with a passed in loop value to say how many times it loops
	void ChangeVolume(int volume);
	void StopAudio(); //Stops the Audio
};

