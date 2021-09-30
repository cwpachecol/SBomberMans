#include  "ExplosionManager.h"
#include "LoadState.h"

ExplosionManager::ExplosionManager()
{
}
void ExplosionManager::Update()
{
    for(std::deque<Explosion>::iterator it=currentExplosions_.begin();
        it!=currentExplosions_.end();
        )
    {
        if(it->HasFinished())
        {
            it=currentExplosions_.erase(it);
            continue;
        }
        it->Update();
        ++it;
    }
}

void ExplosionManager::Draw()
{
    for(std::deque<Explosion>::iterator it=currentExplosions_.begin();
        it!=currentExplosions_.end();
        ++it)
    {
        it->Draw();
    }
}

void ExplosionManager::SpawnExplosion(Vec2f pos,int power, int tag)
{
    Explosion newBoom;
    newBoom.Explode(pos,power,tag,(*explosion_));
    currentExplosions_.push_back(newBoom);
}

void ExplosionManager::Init()
{
    explosion_=&TheLoadState::Instance()->explosion;
}

int ExplosionManager::CheckCollision(AABB2D box)
{
    if(currentExplosions_.size()>0)
    {
        for(std::deque<Explosion>::iterator it=currentExplosions_.begin();
            it!=currentExplosions_.end();
            ++it)
        {
            if(it->GetHozHitbox().Intersects(box)||
                it->GetVertHitbox().Intersects(box))
            {
                return it->GetTag();
            }
        }
        return -1;
    }
    else
    {
        return -1;
    }
}

void ExplosionManager::Reset()
{
    currentExplosions_.clear();
}