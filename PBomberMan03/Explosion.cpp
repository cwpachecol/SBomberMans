#include "Explosion.h"
#include "Timer.h"
#include "WallManager.h"
#include "AudioManager.h"

void Explosion::Update()
{
    explosionDuration_-=TheTimer::Instance()->GetDt();
    if(explosionDuration_<0)
    {
        hasFinished_=true;
    }
    else
    {
        for (std::vector<Sprite>::iterator it=sprites_.begin();
            it!=sprites_.end();
            ++it)
        {
            it->Update();
        }
    }
}

void Explosion::Draw()
{
    for (std::vector<Sprite>::iterator it=sprites_.begin();
        it!=sprites_.end();
        ++it)
    {
        it->Draw();
    }
}
bool Explosion::HasFinished()const
{
    return hasFinished_;
}

int Explosion::GetTag()const
{
    return tag_;
}

void Explosion::Explode(Vec2f pos, int power, int tag, SpriteSheet& sse)
{
    TheAudioManager::Instance()->PlayWav(TheLoadState::Instance()->mChunkExplode,20);
    explosionDuration_=0.5;//deal with this, have a lookup table
    hasFinished_=false;
    centerPos_=pos;
    tag_=tag;
    float minSideSize=centerPos_.x-(20*power);
    float maxSideSize=centerPos_.x+(20*power);
    int iterations=0;
    //right loop
    for(int i=(int)centerPos_.x;i<=maxSideSize;i+=20)
    {

        Vec2f pos((float)i,centerPos_.y);
        int collision=TheWallManager::Instance()->ExplosionWallCheck(pos,tag);
        if(collision==2)
        {
            maxSideSize=centerPos_.x+(20*iterations);
            i=(int)maxSideSize;
        }
        else if(collision==1)
        {
            maxSideSize=centerPos_.x+(20*iterations);
            break;
        }
        Sprite newBoom;
        newBoom.SetPos(pos);
        newBoom.AssignImage(sse);
        newBoom.Init(explosionDuration_/4);
        if(i==maxSideSize)
        {
            newBoom.SetFrameRange(20,24);
        }
        else if(i==centerPos_.x)
        {
            newBoom.SetFrameRange(0,4);
        }
        else
        {
            newBoom.SetFrameRange(8,12);
        }
        sprites_.push_back(newBoom);
        ++iterations;
    }
    iterations=0;
    for(int i=(int)centerPos_.x-20;i>=minSideSize;i-=20)
    {	

        Vec2f pos ((float)i,centerPos_.y);
        int collision=TheWallManager::Instance()->ExplosionWallCheck(pos,tag);
        if(collision==2)
        {
            minSideSize=centerPos_.x+(20*iterations);
            i=(int)minSideSize;
        }
        else if(collision==1)
        {
            minSideSize=centerPos_.x+(20*iterations);
            break;
        }
        Sprite newBoom;
        newBoom.SetPos(pos);
        newBoom.AssignImage(sse);
        newBoom.Init(explosionDuration_/4);
        if(i==minSideSize)
        {
            newBoom.SetFrameRange(24,28);
        }
        else
        {
            newBoom.SetFrameRange(8,12);
        }
        sprites_.push_back(newBoom);
        ++iterations;
    }
    iterations=0;
    float minVertSize=centerPos_.y-(20*power);
    float maxVertSize=centerPos_.y+(20*power);

    //upLoop
    for(int i=(int)centerPos_.y-20;i>=minVertSize;i-=20)
    {

        Vec2f pos (centerPos_.x,(float)i);
        int collision=TheWallManager::Instance()->ExplosionWallCheck(pos,tag);
        if(collision==2)
        {
            minVertSize=centerPos_.y-(20*iterations);
            i=(int)minVertSize;
        }
        else if(collision==1)
        {
            minVertSize=centerPos_.y-(20*iterations);
            break;
        }
        Sprite newBoom;
        newBoom.SetPos(pos);
        newBoom.AssignImage(sse);
        newBoom.Init(explosionDuration_/4);
        if(i==minVertSize)
        {
            newBoom.SetFrameRange(16,20);
        }
        else
        {
            newBoom.SetFrameRange(4,8);
        }
        sprites_.push_back(newBoom);
        ++iterations;
    }
    //downLoop
    iterations=0;
    for(int i=(int)centerPos_.y+20;i<=maxVertSize;i+=20)
    {

        Vec2f pos (centerPos_.x,(float)i);
        int collision=TheWallManager::Instance()->ExplosionWallCheck(pos,tag);
        if(collision==2)
        {
            maxVertSize=centerPos_.y+(20*iterations);
            i=(int)maxVertSize;
        }
        else if(collision==1)
        {
            maxVertSize=centerPos_.y+(20*iterations);
            break;
        }
        Sprite newBoom;
        newBoom.SetPos(pos);
        newBoom.AssignImage(sse);
        newBoom.Init(explosionDuration_/4);
        if(i==maxVertSize)
        {
            newBoom.SetFrameRange(12,16);
        }
        else
        {
            newBoom.SetFrameRange(4,8);
        }
        sprites_.push_back(newBoom);
        ++iterations;
    }
    AABB2D vertBox(centerPos_.x,minVertSize,centerPos_.x+20,maxVertSize+20);
    verticalHitbox_=vertBox;
    AABB2D sideBox(minSideSize,centerPos_.y,maxSideSize+20,centerPos_.y+20);
    horizontalHitbox_=sideBox;
}

AABB2D Explosion::GetHozHitbox()const
{
    return horizontalHitbox_;
}

AABB2D Explosion::GetVertHitbox()const
{
    return verticalHitbox_;
}
