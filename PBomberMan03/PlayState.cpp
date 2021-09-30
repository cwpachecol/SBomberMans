#include "PlayState.h"
#include <algorithm>
#include "EventPoller.h"
#include "BombManager.h"
#include <iostream>
#include "Timer.h"
#include "Game.h"
#include "MenuState.h"
#include "Screen.h"
#include "LoadState.h"
#include "ExplosionManager.h"
#include "WallManager.h"
#include "AudioManager.h"
#include "ScoreManager.h"

PlayState::PlayState()
{
    background_=&TheLoadState::Instance()->gameboyBG;
    screen_=&TheLoadState::Instance()->gameboyScreenGrid;
    screenBackground_=&TheLoadState::Instance()->gameboyScreen;
    winBackground_=&TheLoadState::Instance()->gameboyWinScreen;
    players_.resize(4);

    players_[PLAYER_WHITE].Load(PLAYER_WHITE);
    players_[PLAYER_WHITE].SetKeybindings(SDLK_UP,SDLK_DOWN,SDLK_LEFT,SDLK_RIGHT,SDLK_SPACE);

    players_[PLAYER_BLACK].Load(PLAYER_BLACK);
    players_[PLAYER_BLACK].SetKeybindings(SDLK_w,SDLK_s,SDLK_a,SDLK_d,SDLK_e);

    players_[PLAYER_RED].Load(PLAYER_RED);
    players_[PLAYER_RED].SetKeybindings(SDLK_i,SDLK_k,SDLK_j,SDLK_l,SDLK_o);

    players_[PLAYER_BLUE].Load(PLAYER_BLUE);
    players_[PLAYER_BLUE].SetKeybindings(SDLK_t,SDLK_g,SDLK_f,SDLK_h,SDLK_y);

    TheExplosionManager::Instance()->Init();
    TheBombManager::Instance()->Load();
    isPaused_=false;
    isWin_=false;
    gameboyScreen_.minX_=60;
    gameboyScreen_.minY_=45;
    gameboyScreen_.maxX_=260;
    gameboyScreen_.maxY_=245;
}

PlayState::~PlayState()
{
}

void PlayState::Update()
{
    if(backgroundShifting_)
    {
        if(backgroundShift_>-300)
        {
            backgroundShift_-=2;
        }
        else
        {
            TheGame::Instance()->SetState(TheMenuState::Instance());
        }
    }
    else if(backgroundShift_<=-2)
    {
        backgroundShift_+=2;
    }
    //----------
    if(!isPaused_)
    {
        for(std::vector<Player*>::iterator it=activePlayers_.begin();
            it<activePlayers_.end();)
        {
            if((*it)!=0)
            {
                if((*it)->GetRemoveMe())
                {
                    TheEventPoller::Instance()->RemoveEventHandler((*it));
                    it=activePlayers_.erase(it);
                    continue;
                }
                (*it)->Update();
                ++it;
            }
        }
        if(numOfPlayers_!=1)
        {
            if(activePlayers_.size()<=1)
            {
                if(activePlayers_.size()<1)
                {
                    WinState(0);
                }
                else
                {
                    WinState(activePlayers_[0]->GetTag());
                }
            }
        }
        else
        {
            if(TheScoreManager::Instance()->GetHighestScore()>=
                TheScoreManager::Instance()->GetScore(-1))
            {
                WinState(0);
            }
        }
        TheBombManager::Instance()->Update();
        TheExplosionManager::Instance()->Update();
        TheWallManager::Instance()->Update();
        if(!TheAudioManager::Instance()->IsMusicPlaying())
        {
            TheAudioManager::Instance()->PlayMus(TheLoadState::Instance()->musicTracks[rand()%6],2);
        }
    }
}

void PlayState::Draw()
{	
    background_->Draw(0,backgroundShift_);
    if(!isPaused_)
    {
        if(!isWin_)
        {
            screenBackground_->Draw((int)gameboyScreen_.minX_,(int)gameboyScreen_.minY_);
            screen_->Draw((int)gameboyScreen_.minX_,(int)gameboyScreen_.minY_);
            TheLoadState::Instance()->pixelFont.Draw(banner_,60,25,TheLoadState::Instance()->WhiteColor);
            TheWallManager::Instance()->Draw();
            for(std::vector<Player*>::iterator it=activePlayers_.begin();
                it<activePlayers_.end();it++)
            {
                if((*it)!=0)
                {
                    (*it)->Draw();
                }

            }
            TheBombManager::Instance()->Draw();
            TheExplosionManager::Instance()->Draw();
        }
        else
        {
            winBackground_->Draw((int)gameboyScreen_.minX_,(int)gameboyScreen_.minY_);
        }
        TheScoreManager::Instance()->Draw();
    }


}

void PlayState::SetPlayerNum(int num)
{
    numOfPlayers_=num;
}

void PlayState::RefundBomb(int tag)
{
    players_[tag].RefundBomb();
}

void PlayState::OnActive()
{
    if(!isPaused_)
    {
        TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->mChunkGameStart,30);
        for(int i=0;i<numOfPlayers_;++i)
        {
            activePlayers_.push_back(&players_[i]);
            activePlayers_[i]->SetPos(Vec2f(TheLoadState::Instance()->spawnPoints[level_][i].x,
                TheLoadState::Instance()->spawnPoints[level_][i].y-5));
            TheEventPoller::Instance()->AddEventHandler(activePlayers_[i]);
        }
        TheScoreManager::Instance()->Init(numOfPlayers_);
        TheScoreManager::Instance()->SetPos(Vec2f(260,45));
        TheScoreManager::Instance()->SetSeperation(40);
        if(numOfPlayers_==1)
        {
            banner_="Practice: Destroy all the walls!";
        }
        else
        {
            banner_="Bomb the other players to win!";
        }
    }
    TheEventPoller::Instance()->AddEventHandler(this);
    isPaused_=false;
    backgroundShifting_=false;
    backgroundShift_=-2;
}

void PlayState::OnInactive()
{
    TheEventPoller::Instance()->RemoveEventHandler(this);
    isPaused_=true;
    backgroundShift_=false;
}

void PlayState::OnKeyboardEvent(const SDL_KeyboardEvent& event)
{
    if(event.state==SDL_PRESSED)
    {
        if(event.keysym.sym==SDLK_p)
        {
            TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->mChunkPause,5);
            TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->mChunkTransition,5);
            backgroundShifting_=!backgroundShifting_;
            isPaused_=!isPaused_;
        }
    }
}

AABB2D PlayState::GetScreenSize()const
{
    return gameboyScreen_;
}

void PlayState::SetLevel(int level)
{
    level_=level;
    TheWallManager::Instance()->Reset();
    TheWallManager::Instance()->Init(level_);
}

void PlayState::Reset()
{
    isPaused_=false;
    isWin_=false;
    activePlayers_.clear();
    TheWallManager::Instance()->Reset();
    TheBombManager::Instance()->Reset();
    TheExplosionManager::Instance()->Reset();
    TheScoreManager::Instance()->Reset();
    for(std::vector<Player>::iterator it=players_.begin();
        it!=players_.end();
        ++it)
    {
        TheEventPoller::Instance()->RemoveEventHandler(&(*it));
        it->Reset();
    }
    TheMenuState::Instance()->SetInPlay(false);
}

void PlayState::WinState(int winner)
{
    if(!isWin_)
    {
        TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->playerShouts[winner],35);
        TheScoreManager::Instance()->SetPos(Vec2f(140,185));
        TheScoreManager::Instance()->SetSeperation(12);
        isWin_=true;
    }
    //present scores and win banner
}