#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager()
{
    audio_rate_=22050;
    audio_format_=AUDIO_S16SYS;
    audio_channels_=2;
    audio_buffers_=4096;
}

bool AudioManager::Init()
{
    if(Mix_OpenAudio(audio_rate_,audio_format_,audio_channels_,audio_buffers_)!=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool AudioManager::PlayWav(const std::string& filename)
{
    Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    assert(sound);
    int channel = Mix_PlayChannel(-1,sound,0);
    audio_flags_.push_front(channel);
    return true;
}

bool AudioManager::PlayWav(const std::string& filename, int percentVol)
{
    Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
    assert(sound);
    int channel = Mix_PlayChannel(-1,sound,0);
    Mix_Volume(channel,128/100*percentVol);
    audio_flags_.push_front(channel);
    return true;
}

bool AudioManager::PlayMus(const std::string& filename,int fadeIn)
{
    Mix_Music* music=0;
    music=Mix_LoadMUS(filename.c_str());
    assert(music);
    int channel;
    if(fadeIn==0)
    {
        channel = Mix_PlayMusic(music,1);
    }
    else
    {
        channel = Mix_FadeInMusic(music,1,1000*fadeIn);
    }
    std::cout<<SDL_GetError();
    audio_flags_.push_front(channel);
    return true;
}

void AudioManager::Update()
{
    for(std::list<int>::iterator it=audio_flags_.begin();
        it!=audio_flags_.end();++it)
    {

    }
}

bool AudioManager::IsMusicPlaying()
{
    return (Mix_PlayingMusic!=0);
}

void AudioManager::SetMusicVolume(int percent)
{
    Mix_VolumeMusic(128/100*percent);
}

void AudioManager::StopMusic()
{
    Mix_HaltMusic();
}
