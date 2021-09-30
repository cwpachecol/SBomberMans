#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "EventHandler.h"
#include "Sprite.h"
#include "AABB2D.h"

enum DIRECTION{FACE_NORTH=0,FACE_EAST,FACE_SOUTH,FACE_WEST};
class Player:public EventHandler
{
public:
    bool Load(int tag);
    void Update();
    void Draw();
    virtual void OnKeyboardEvent(const SDL_KeyboardEvent&);
    void SetKeybindings(int up,int down, int left, int right,int bomb);
    bool GetRemoveMe()const;
    void RefundBomb();
    void SetPos(Vec2f);
    void Reset();
    AABB2D GetHitBox();
    int GetTag()const;
private:
    float speed_;
    Sprite sprite_;
    bool upCommand_;
    bool downCommand_;
    bool leftCommand_;
    bool rightCommand_;

    int bombCount_;
    int maxBomb_;
    int bombPower_;
    float bombDuration_;
    float bombFuseTime_;

    int upKey_;
    int downKey_;
    int leftKey_;
    int rightKey_;
    int bombKey_;

    AABB2D playerHitBox_;
    int direction_;//north=0,east=1,south=2,west=3
    bool removeMe_;
    int tag_;
	int bombScoreInterval;
};

#endif