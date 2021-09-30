#include <SDL.h>
#include "Game.h"
#include "Screen.h"
#include "EventPoller.h"
#include "AudioManager.h"
#include "Timer.h"
#include "PlayState.h"
#include "LoadState.h"

int main(int, char**)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TheScreen::Instance()->Init(320,300,SDL_SWSURFACE);
    TheGame::Instance()->SetState(TheLoadState::Instance());
    TheAudioManager::Instance()->Init();
    TheGame::Instance()->Run();
    SDL_Quit();
    return 0;
};