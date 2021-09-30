#include "Player.h"
#include "EventPoller.h"
#include <iostream>
#include <string>
#include "Timer.h"
#include "BombManager.h"
#include "LoadState.h"
#include "ExplosionManager.h"
#include "PlayState.h"
#include "WallManager.h"
#include "AudioManager.h"
#include "ScoreManager.h"


bool Player::Load(int tag)
{
    sprite_.AssignImage(TheLoadState::Instance()->playerSprites[tag]);
    sprite_.Init(0.2f);
    sprite_.SetLoopBack(true);
    direction_=2;
    playerHitBox_=GetHitBox();
    removeMe_=false;

    maxBomb_=TheLoadState::Instance()->playerMaxBomb[tag];
    speed_=TheLoadState::Instance()->playerMoveSpeed[tag];
    bombPower_=TheLoadState::Instance()->bombPowers[tag];
    bombDuration_=TheLoadState::Instance()->explosionDuration[tag];
    bombFuseTime_=TheLoadState::Instance()->bombFuseTime[tag];
    bombCount_=maxBomb_;

    upCommand_=false;
    downCommand_=false;
    leftCommand_=false;
    rightCommand_=false;

    tag_=tag;
    return true;
}

void Player::Draw()
{
    sprite_.Draw();
}

void Player::Update()
{
    playerHitBox_=GetHitBox();//needs to be updated for hit detection
    AABB2D screenSize=ThePlayState::Instance()->GetScreenSize();
    Vec2f movVec;
	
	if(TheScoreManager::Instance()->GetScore(tag_)>100&&bombPower_==1)
	{
		bombPower_+=1;
		maxBomb_+=1;
	}
	if(TheScoreManager::Instance()->GetScore(tag_)>200&&bombPower_==2)
	{
		bombPower_+=1;
		maxBomb_+=1;
	}

    float dt=TheTimer::Instance()->GetDt();
    if(upCommand_==true)
    {
        movVec.y=-speed_;
        movVec.x=0;

    }
    if(downCommand_==true)
    {
        movVec.y=speed_;
        movVec.x=0;

    }
    if(leftCommand_==true)
    {
        movVec.x=-speed_;
        movVec.y=0;

    }
    if(rightCommand_==true)
    {
        movVec.x=speed_;
        movVec.y=0;

    }
    if(!(rightCommand_||leftCommand_||upCommand_||downCommand_))//if nothing is pressed
    {
        movVec=Vec2f(0,0);
        if(direction_==FACE_NORTH)
        {
            sprite_.SetFrameRange(10,10);
        }
        else if(direction_==FACE_EAST)
        {
            sprite_.SetFrameRange(4,4);
        }
        else if(direction_==FACE_SOUTH)
        {
            sprite_.SetFrameRange(7,7);
        }
        else if(direction_==FACE_WEST)
        {
            sprite_.SetFrameRange(1,1);
        }
    }
    int hit=TheExplosionManager::Instance()->CheckCollision(playerHitBox_);
    if(hit>=0)
    {
        if(hit==tag_)
        {
            TheScoreManager::Instance()->AddScore(TheLoadState::Instance()->playerSuicideScore,tag_);
        }
        else if(hit!=tag_)
        {
            TheScoreManager::Instance()->AddScore(TheLoadState::Instance()->playerScore,hit);
        }
        TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->mChunkPlayerDeath,20);
        removeMe_=true;
    }
    Vec2f oldPos=sprite_.GetPos();
    sprite_.SetVel(movVec);
    sprite_.Update();
    playerHitBox_=GetHitBox();
    if(TheWallManager::Instance()->PlayerWallCheck(playerHitBox_,tag_))
    {
        sprite_.SetPos(oldPos);
    }
    if(playerHitBox_.IsOutside(screenSize))
    {
        Vec2f spritePos=sprite_.GetPos();

        float playerWidth=playerHitBox_.maxX_-playerHitBox_.minX_;
        float playerHeight=playerHitBox_.maxY_-playerHitBox_.minY_;
        if(playerHitBox_.maxX_>screenSize.maxX_)
        {
            sprite_.SetPos(oldPos);
        }
        else if(playerHitBox_.minX_<screenSize.minX_)
        {
            sprite_.SetPos(oldPos);
        }
        else if(playerHitBox_.minY_<screenSize.minY_)
        {
            sprite_.SetPos(oldPos);
        }
        else if(playerHitBox_.maxY_>screenSize.maxY_)
        {
            sprite_.SetPos(oldPos);
        }
    }
}

void Player::OnKeyboardEvent(const SDL_KeyboardEvent& event)
{
    if(event.state==SDL_PRESSED)
    {
        if(event.keysym.sym==upKey_)
        {
            upCommand_=true;
            sprite_.SetFrameRange(9,12);
            direction_=FACE_NORTH;
        }
        if(event.keysym.sym==downKey_)
        {
            downCommand_=true;
            sprite_.SetFrameRange(6,9);
            direction_=FACE_SOUTH;
        }
        if(event.keysym.sym==leftKey_)
        {
            leftCommand_=true;
            sprite_.SetFrameRange(0,3);
            direction_=FACE_WEST;
        }
        if(event.keysym.sym==rightKey_)
        {
            rightCommand_=true;
            sprite_.SetFrameRange(3,6);
            direction_=FACE_EAST;
        }
        if(event.keysym.sym==bombKey_)
        {
            if(bombCount_>0)
            {
                if(TheBombManager::Instance()->SetBomb(bombPower_,bombFuseTime_,
                    sprite_.GetPos(),tag_))
                {
                    TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->mChunkSetBomb,20);
                    --bombCount_;
                }
            }
        }
    }
    if(event.state==SDL_RELEASED)
    {
        if(event.keysym.sym==upKey_)
        {
            upCommand_=false;
        }
        if(event.keysym.sym==downKey_)
        {
            downCommand_=false;
        }
        if(event.keysym.sym==leftKey_)
        {
            leftCommand_=false;
        }
        if(event.keysym.sym==rightKey_)
        {
            rightCommand_=false;
        }
    }

}

void Player::SetKeybindings(int up,int down, int left, int right,int bomb)
{
    upKey_=up;
    downKey_=down;
    leftKey_=left;
    rightKey_=right;
    bombKey_=bomb;
}

bool Player::GetRemoveMe()const
{
    return removeMe_;
}

void Player::RefundBomb()
{
    ++bombCount_;
    if(bombCount_>maxBomb_)
    {
        bombCount_=maxBomb_;
    }
}

AABB2D Player::GetHitBox()
{
    playerHitBox_.minY_=sprite_.GetPos().y+10;
    playerHitBox_.maxY_=sprite_.GetPos().y+25;
    playerHitBox_.minX_=sprite_.GetPos().x+3;
    playerHitBox_.maxX_=sprite_.GetPos().x+13;
    return playerHitBox_;
}

void Player::Reset()
{
    maxBomb_=TheLoadState::Instance()->playerMaxBomb[tag_];
    speed_=TheLoadState::Instance()->playerMoveSpeed[tag_];
    bombPower_=TheLoadState::Instance()->bombPowers[tag_];
    bombDuration_=TheLoadState::Instance()->explosionDuration[tag_];
    bombFuseTime_=TheLoadState::Instance()->bombFuseTime[tag_];
    bombCount_=maxBomb_;
    removeMe_=false;
}

void Player::SetPos(Vec2f vec)
{
    sprite_.SetPos(vec);
}

int Player::GetTag()const
{
    return tag_;
}