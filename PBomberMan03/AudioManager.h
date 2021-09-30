#ifndef AUDIOMANAGER_H_INCLUDED
#define AUDIOMANAGER_H_INCLUDED

#include "NonCopyable.h"
#include "Singleton.h"
#include <SDL_mixer.h>
#include <assert.h>
#include <string>
#include <list>
class AudioManager;
typedef Singleton<AudioManager> TheAudioManager;
class AudioManager: public NonCopyable
{
public:
    bool PlayWav(const std::string& filename);
    bool PlayWav(const std::string& filename,int percentVol);
    bool PlayMus(const std::string& filename,int fadeIn);
    bool IsMusicPlaying();
    void SetMusicVolume(int percent);
    void SetMasterVolume(int percent);
    void StopMusic();
    bool Init();
    void Update();

private:
    AudioManager();
    std::list<int> audio_flags_;
    friend TheAudioManager;
    int audio_rate_;
    Uint16 audio_format_;
    int audio_channels_;
    int audio_buffers_;
};

#endif