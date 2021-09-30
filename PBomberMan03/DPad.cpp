#include "DPad.h"
#include <sstream>

DPad::DPad()
{
    currentLevel=0;
    currentPlayerNum=1;
}

bool DPad::LevelDown()
{
    if(currentLevel>0)
    {
        --currentLevel;
        return true;
    }
    return false;
}

bool DPad::LevelUp()
{
    if(currentLevel<TheLoadState::Instance()->mapBuild.size()-1)
    {
        ++currentLevel;
        return true;
    }
    return false;
}

bool DPad::PlayersUp()
{
    if(currentPlayerNum<4)
    {
        ++currentPlayerNum;
        return true;
    }
    return false;
}

bool DPad::PlayersDown()
{
    if(currentPlayerNum>1)
    {
        --currentPlayerNum;
        return true;
    }
    return false;
}

void DPad::Draw()
{
    std::stringstream sstream;
    sstream <<currentPlayerNum;
    std::string totalString =sstream.str();
    TheLoadState::Instance()->pixelFont.Draw(totalString,50,185,TheLoadState::Instance()->RedColor);
    sstream.str(std::string());
    if(currentPlayerNum>1)
    {
        sstream<<" P's in map:";
    }
    else
    {
        sstream<<" P in map:";
    }
    totalString=sstream.str();
    TheLoadState::Instance()->pixelFont.Draw(totalString,52,185,TheLoadState::Instance()->BlackColor);
    sstream.str(std::string());
    sstream<<TheLoadState::Instance()->levelNames[currentLevel];
    totalString=sstream.str();
    TheLoadState::Instance()->pixelFont.Draw(totalString,50,197,TheLoadState::Instance()->BlueColor);
}

int DPad::GetPlayerNum()const 
{
    return currentPlayerNum;
}

int DPad::GetLevel()const
{
    return currentLevel;
}