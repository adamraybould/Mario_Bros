#include "Audio.h"

Audio::Audio(std::string path, AudioType type)
{
	this->type = type;

	//Loads the Audio depending on the Type of Audio it is
	switch (type)
	{
		case AudioType::SOUNDEFFECT:
			soundEffect = Mix_LoadWAV(path.c_str());
		break;

		case AudioType::MUSIC:
			music = Mix_LoadMUS(path.c_str());
		break;
	}
}

Audio::~Audio()
{
	//Deletes the Audio depending on the type of Audio it is
	switch (type)
	{
		case AudioType::SOUNDEFFECT:
			Mix_FreeChunk(soundEffect);
			delete soundEffect;
		break;

		case AudioType::MUSIC:
			Mix_FreeMusic(music);
			delete music;
		break;
	}
}

void Audio::PlayAudio(int loop)
{
	//Plays the Audio depending on the type of Audio it is
	switch (type)
	{
		case AudioType::SOUNDEFFECT:
			Mix_PlayChannel(-1, soundEffect, loop);
		break;

		case AudioType::MUSIC:
			Mix_PlayMusic(music, loop);
		break;
	}
}

void Audio::ChangeVolume(int volume)
{
	//Changes the Volume depending on the type of Audio it is
	switch (type)
	{
		case AudioType::SOUNDEFFECT:
 			Mix_VolumeChunk(soundEffect, volume);
		break;

		case AudioType::MUSIC:
			Mix_VolumeMusic(volume);
		break;
	}
}

void Audio::StopAudio()
{
	Mix_HaltMusic();
}
