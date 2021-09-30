#include "Sprite.h"
#include "Timer.h"

Sprite::Sprite():m_pos(),m_vel()
{
    m_frame=0;
    m_frameRangeTop=0;
    m_frameRangeBottom=0;
    m_frameTimer=0;
    m_maxElapsedTime=0.1f;
    loopBack_=false;
    playForward_=true;
    play_=true;
}
Sprite::Sprite(SpriteSheet &spriteSheet)
{
    *m_spriteSheet = spriteSheet;
    m_frame=0;
    m_frameRangeTop=m_spriteSheet->GetTotalFrames();
    m_frameRangeBottom=0;
    m_frameTimer=0;
    m_maxElapsedTime=0.1f;
    loopBack_=false;
    playForward_=true;
    play_=true;
}
Sprite::Sprite(SpriteSheet &spriteSheet,float maxElapsedTime)
{
    *m_spriteSheet = spriteSheet;
    m_frame=0;
    m_frameRangeTop=m_spriteSheet->GetTotalFrames();
    m_frameRangeBottom=0;
    m_frameTimer=0;
    m_maxElapsedTime=maxElapsedTime;
    loopBack_=false;
    playForward_=true;
    play_=true;
}

void Sprite::Init(float maxElapsedTime)
{
    m_maxElapsedTime=maxElapsedTime;
}

void Sprite::AssignImage(SpriteSheet &spriteSheet)
{

    m_spriteSheet=&spriteSheet;
    m_frameRangeTop=m_spriteSheet->GetTotalFrames();
}

void Sprite::SetVel(const Vec2f v)
{
    m_vel=v;
}

void Sprite::SetPos(const Vec2f p)
{
    m_pos=p;
}

const Vec2f& Sprite::GetPos()const
{
    return m_pos;
}

const Vec2f& Sprite::GetVel()const
{
    return m_vel;
}

AABB2D Sprite::GetAABB()const
{
    return AABB2D(m_pos.x,
        m_pos.y,
        m_pos.x+m_spriteSheet->GetCellSize().x,
        m_pos.y+m_spriteSheet->GetCellSize().y);
}

void Sprite::Update()
{
    float dt=TheTimer::Instance()->GetDt();
    if(play_)
    {
        m_frameTimer+=dt;
    }
    if(m_frameTimer>m_maxElapsedTime)
    {
        if(!loopBack_)
        {
            m_frameTimer=0;
            m_frame++;
            if(m_frame==m_spriteSheet->GetTotalFrames()||
                m_frame==m_frameRangeTop)
            {
                m_frame=m_frameRangeBottom;
            }
        }
        else
        {
            m_frameTimer=0;
            if(playForward_)
            {
                m_frame++;
            }
            else
            {
                m_frame--;
            }
            if(m_frame==m_spriteSheet->GetTotalFrames()||
                m_frame==m_frameRangeTop)
            {
                --m_frame;
                playForward_=false;
            }
            else if(m_frame==0||
                m_frame==m_frameRangeBottom)
            {
                playForward_=true;
            }

        }

    }
    m_pos.x += (m_vel.x * dt);
    m_pos.y += (m_vel.y * dt);
}

void Sprite::Draw()
{
    m_spriteSheet->Draw((int)m_pos.x,(int)m_pos.y,m_frame);
}

void Sprite::SetFrameRange(int fMin,int fMax)
{
    if(fMin>=0)
    {
        m_frameRangeBottom=fMin;
    }
    else
    {
        m_frameRangeBottom=0;
    }
    if(fMax<=m_spriteSheet->GetTotalFrames())
    {
        m_frameRangeTop=fMax;
    }
    else
    {
        m_frameRangeTop=m_spriteSheet->GetTotalFrames();
    }
    m_frame=m_frameRangeBottom;
    playForward_=true;
    play_=true;
    if(fMin==fMax)
    {
        play_=false;
    }

}
void Sprite::SetLoopBack(bool toggle)
{
    loopBack_=toggle;
}

void Sprite::Play()
{
    play_=true;
}
void Sprite::Stop()
{
    play_=false;
}