#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"
#include "EventPoller.h"
#include "LoadState.h"
#include "ButtonManager.h"
#include "AudioManager.h"


MenuState::MenuState()
{
    background_.Load("GameBoyBackground.jpg");
    backgroundShift_=-300;
    backgroundShifting_=false;
    isPaused_=false;
    inPlay_=false;
}

MenuState::~MenuState()
{}

void MenuState::Update()
{
    if(backgroundShifting_)//when shifting
    {
        if(backgroundShift_<-2)//and were below the target
        {
            backgroundShift_+=2;//move us until
        }
        else//were at the target
        {
            TheGame::Instance()->SetState(ThePlayState::Instance());
        }
    }
    else if(backgroundShift_>=-300)//if were not shifting, then return the image back
    {
        backgroundShift_-=2;
    }
    else
    {
        isPaused_=false;
    }
    //----------
    if(!isPaused_)
    {
        //decide between paused with an active game and not
    }
}

void MenuState::Draw()
{
    background_.Draw(0,backgroundShift_);
    if(!isPaused_)
    {
        TheButtonManager::Instance()->Draw();
    }
}

void MenuState::OnActive()
{
    TheEventPoller::Instance()->AddEventHandler(this);
    backgroundShifting_=false;
    isPaused_=false;
    backgroundShift_=-300;
}

void MenuState::OnInactive()
{
    inPlay_=true;
    TheEventPoller::Instance()->RemoveEventHandler(this);
    backgroundShift_=false;
    isPaused_=true;
}

void MenuState::OnKeyboardEvent(const SDL_KeyboardEvent& event)
{
    if(event.state==SDL_PRESSED)
    {
        if(event.keysym.sym==SDLK_p)
        {
            if(inPlay_)
            {
                TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->mChunkTransition,5);
                backgroundShifting_=!backgroundShifting_;
                isPaused_=!isPaused_;
            }
        }
    }
}

void MenuState::OnMouseMotionEvent(const SDL_MouseMotionEvent& event)
{
    TheButtonManager::Instance()->MouseMove(Vec2f(event.x,event.y));
}

void MenuState::OnMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
    if(event.state==SDL_PRESSED)
    {
        if(event.type==SDL_MOUSEBUTTONDOWN)
        {
            TheButtonManager::Instance()->ClickAt(Vec2f(event.x,event.y));
        }
    }
}

void MenuState::SetInPlay(bool inPlay)
{
    inPlay_=inPlay;
}