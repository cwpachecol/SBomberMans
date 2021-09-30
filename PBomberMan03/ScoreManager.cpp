#include"ScoreManager.h"
#include <sstream>
#include "LoadState.h"

ScoreManager::ScoreManager()
{
    numOfPlayers=0;
    seperation=0;
    for(int i=0;i<4;++i)
    {
        scores_.push_back(0);
    }
}
void ScoreManager::Draw()
{
    for(unsigned int i=0;i!=numOfPlayers;++i)
    {
        std::stringstream sstream;
        sstream <<"P"<<i+1<<": "<<scores_[i];
        std::string text=sstream.str();
        SDL_Colour col;
        if(i==0)
        {
            col=TheLoadState::Instance()->WhiteColor;
        }
        else if(i==1)
        {
            col=TheLoadState::Instance()->PinkColor;
        }
        else if(i==2)
        {
            col=TheLoadState::Instance()->RedColor;
        }
        else if(i==3)
        {
            col=TheLoadState::Instance()->BlueColor;
        }
        TheLoadState::Instance()->pixelFont.Draw(text,pos_.x,pos_.y+i*seperation,col);
    }
}

void ScoreManager::Init(int playerNum)
{
    numOfPlayers=playerNum;
}

void ScoreManager::AddScore(int score, int tag)
{
    scores_[tag]+=score;
}

void ScoreManager::MinusScore(int score,int tag)
{
    scores_[tag]-=score;
}

void ScoreManager::Reset()
{
    for(std::vector<int>::iterator it=scores_.begin();
        it!=scores_.end();
        ++it)
    {
        (*it)=0;
    }
}

void ScoreManager::SetPos(Vec2f pos)
{
    pos_=pos;
}

void ScoreManager::SetSeperation(int sep)
{
    seperation=sep;
}

int ScoreManager::GetScore(int tag)
{
    if(tag==-1)
    {
        return maxMapScore_;
    }
    if(tag<scores_.size())
    {
        return scores_[tag];
    }
    return -1;
}

int ScoreManager::GetHighestScore()
{
    int highestScore=0;
    for(unsigned int i=0;i<scores_.size();++i)
    {
        if(scores_[i]>highestScore)
        {
            highestScore=scores_[i];
        }
    }
    return highestScore;
}

void ScoreManager::SetMaxMapScore(int maxScore)
{
    maxMapScore_=maxScore;
}