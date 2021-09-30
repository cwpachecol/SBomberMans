#include "WallManager.h"
#include "TileFunctions.h"
#include "ScoreManager.h"
WallManager::WallManager()
{

}

WallManager::~WallManager()
{

}

void WallManager::Init(int level)
{
    int maxPossibleScore=0;
    for(int i=0;i!=TheLoadState::Instance()->mapBuild[level].size();++i)
    {
        walls_.push_back(Wall(TheLoadState::Instance()->mapBuild[level][i],
            TheLoadState::Instance()->mapBuildBreakables[level][i]));
        if(TheLoadState::Instance()->mapBuildBreakables[level][i]==true)
        {
            maxPossibleScore+=TheLoadState::Instance()->wallScore;
        }
    }
    TheScoreManager::Instance()->SetMaxMapScore(maxPossibleScore);
}

int WallManager::ExplosionWallCheck(Vec2f pos,int tag)
{
    for(std::list<Wall>::iterator it= walls_.begin();
        it!=walls_.end();)
    {
        if(it->GetPos()==Settle(pos))
        {
            if(it->GetBreakable())
            {
                it=walls_.erase(it);
                TheScoreManager::Instance()->AddScore(TheLoadState::Instance()->wallScore,tag);
                return 2;

            }
            return 1;
        }
        ++it;
    }
    return 0;
}
bool WallManager::PlayerWallCheck(Vec2f pos,int tag)
{
    for(std::list<Wall>::iterator it= walls_.begin();
        it!=walls_.end();)
    {
        if(it->GetPos()==Settle(pos))
        {
            return true;
        }
        ++it;
    }
    return false;
}

bool WallManager::PlayerWallCheck(AABB2D& box,int tag)
{
    for(std::list<Wall>::iterator it= walls_.begin();
        it!=walls_.end();)
    {
        if(it->GetAABB2D().Intersects(box))
        {
            return true;
        }
        ++it;
    }
    return false;
}
void WallManager::Update()
{
    for (std::list<Wall>::iterator it=walls_.begin();
        it!=walls_.end();
        ++it)
    {
        it->Update();
    }
}

void WallManager::Draw()
{
    for (std::list<Wall>::iterator it=walls_.begin();
        it!=walls_.end();
        ++it)
    {
        if(it->GetAABB2D().minX_==200&&it->GetAABB2D().minY_==45)
        {
            int babs=10;
        }
        it->Draw();
    }

}

void WallManager::Reset()
{
    walls_.clear();
}