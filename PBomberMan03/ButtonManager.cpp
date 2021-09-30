#include "ButtonManager.h"
#include "TextButton.h"
#include "AudioManager.h"

ButtonManager::ButtonManager()
{
    buttons_.push_back(&TheLoadState::Instance()->upArrowButton);
    buttons_.push_back(&TheLoadState::Instance()->downArrowButton);
    buttons_.push_back(&TheLoadState::Instance()->rightArrowButton);
    buttons_.push_back(&TheLoadState::Instance()->leftArrowButton);
    buttons_.push_back(&TheLoadState::Instance()->startButton);
    buttons_.push_back(&TheLoadState::Instance()->resetButton);
    inPlay_=false;
}

void ButtonManager::HandleButtonClick(int buttonTag)
{
    if(buttonTag==PUP_TAG)
    {
        dPad.PlayersUp();

    }
    else if(buttonTag==PDOWN_TAG)
    {
        dPad.PlayersDown();

    }
    else if(buttonTag==LVLUP_TAG)
    {
        dPad.LevelUp();

    }
    else if(buttonTag==LVLDOWN_TAG)
    {
        dPad.LevelDown();

    }
    if(buttonTag==PLAY_TAG)
    {
        if(!inPlay_)
        {
            ThePlayState::Instance()->SetLevel(dPad.GetLevel());
            ThePlayState::Instance()->SetPlayerNum(dPad.GetPlayerNum());
            TheGame::Instance()->SetState(ThePlayState::Instance());
            TheAudioManager::Instance()->StopMusic();
            TheAudioManager::Instance()->PlayMus(TheLoadState::Instance()->musicTracks[rand()%6].c_str(),2);
            TheAudioManager::Instance()->SetMusicVolume(10);
            inPlay_=true;
        }
    }
    if(buttonTag==QUIT_TAG)
    {
        exit(0);
    }

    if(buttonTag==RESET_TAG)
    {
        TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->mChunkReset,20);
        ThePlayState::Instance()->Reset();
        inPlay_=false;
    }

}

void ButtonManager::Draw()
{
    for(std::vector<Button*>::iterator it=buttons_.begin();
        it!=buttons_.end();
        ++it)
    {
        (*it)->Draw();
    }
    dPad.Draw();
}

void ButtonManager::ClickAt(Vec2f mouseClick)
{
    for(std::vector<Button*>::iterator it= buttons_.begin();
        it!=buttons_.end();
        ++it)
    {
        if((*it)->GetAABB2D().Intersects(mouseClick))
        {
            (*it)->OnClick();
            TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->mChunkClick,20);
            HandleButtonClick((*it)->GetTag());
        }
        else
        {
            (*it)->OnUp();
        }
    }
}

void ButtonManager::MouseMove(Vec2f mousePos)
{
    for(std::vector<Button*>::iterator it= buttons_.begin();
        it!=buttons_.end();
        ++it)
    {
        if((*it)->GetAABB2D().Intersects(mousePos))
        {
            (*it)->OnOver();
        }
        else
        {
            (*it)->OnUp();
        }
    }
}