#include <assert.h>
#include "EventPoller.h"
#include "Game.h"
#include "Screen.h"
#include "Timer.h"

Game::Game()
{
    currentState_=0;
}

void Game::SetState(GameState* newState)
{
    if(currentState_)
    {
        currentState_->OnInactive();
    }
    currentState_=newState;
    currentState_->OnActive();
}

void Game::Run()
{
    while (true)
    {
        Update();
        Draw();
        TheScreen::Instance()->Flip();
    }
}
void Game::Update()
{
    TheTimer::Instance()->Update();
    TheEventPoller::Instance()->Update();
    assert(currentState_);
    currentState_->Update();
}
void Game::Draw()
{
    TheScreen::Instance()->Clear();
    assert(currentState_);
    currentState_->Draw();
}