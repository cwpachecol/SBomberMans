#ifndef SPRITE_H
#define SPRITE_H
#include "SpriteSheet.h"
#include "Vec2.h"
#include <string>
#include <SDL.h>
#include "AABB2D.h"

class Sprite
{
public:
    Sprite();
    Sprite(SpriteSheet& spriteSheet);
    Sprite(SpriteSheet& spriteSheet, float maxElapsedTime);
    void Init(float maxElapsedTime);
    void AssignImage(SpriteSheet& spriteSheet);
    void SetVel(const Vec2f v);
    void SetPos(const Vec2f p);
    void SetFrameRange(int frameMin,int frameMax);
    void SetLoopBack(bool);
    const Vec2f& GetVel()const;
    const Vec2f& GetPos()const;
    void Update();
    void Draw();
    void Play();
    void Stop();
    AABB2D GetAABB()const;


private:
    Vec2f m_pos;
    Vec2f m_vel;
    SpriteSheet* m_spriteSheet;
    float m_frameTimer;
    float m_maxElapsedTime;
    int m_frame;
    int m_frameRangeTop;
    int m_frameRangeBottom;
    bool play_;
    bool loopBack_;
    bool playForward_;
};
#endif