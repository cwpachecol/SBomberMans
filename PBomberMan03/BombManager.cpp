#include "BombManager.h"
#include "PlayState.h"
#include "TileFunctions.h"
#include "LoadState.h"
#include "ExplosionManager.h"
BombManager::BombManager()
{
}

void BombManager::Load()
{
    bombSheet_=&TheLoadState::Instance()->bomb;
}
bool BombManager::SetBomb(int power, float fuse, Vec2f pos,int owner)
{
    for(std::list<Bomb>::iterator it=bombQueue_.begin();
        it!=bombQueue_.end();
        ++it)
    {
        if(Settle(pos)==it->GetPos())
        {
            return false;
        }
    }
    bombQueue_.push_back(Bomb(power,fuse,pos,*bombSheet_,owner));
    return true;
}

void BombManager::Update()
{
    for(std::list<Bomb>::iterator it=bombQueue_.begin();
        it!=bombQueue_.end();)
    {
        if(it->HasExploded())
        {
            ThePlayState::Instance()->RefundBomb(it->GetTag());
            TheExplosionManager::Instance()->SpawnExplosion(it->GetPos(),it->GetPower(),it->GetTag());
            it=bombQueue_.erase(it);
            continue;
            //pass bomb to expolosion
        }
        it->Update();
        ++it;

    }
}

void BombManager::Draw()
{
    for(std::list<Bomb>::iterator it=bombQueue_.begin();
        it!=bombQueue_.end();
        ++it)
    {
        it->Draw();
    }
}

void BombManager::Reset()
{
    bombQueue_.clear();
}