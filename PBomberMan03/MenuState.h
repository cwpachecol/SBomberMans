#ifndef MENUSTATE_H_INLCUDED
#define MENUSTATE_H_INCLUDED
#include "Singleton.h"
#include "GameState.h"
#include "Image.h"
class MenuState;
typedef Singleton<MenuState> TheMenuState;

class MenuState:public GameState
{
public:
    virtual void Update();
    virtual void Draw();
    virtual void OnActive();
    virtual void OnInactive();
    void OnKeyboardEvent(const SDL_KeyboardEvent&) = 0;
    void OnMouseMotionEvent(const SDL_MouseMotionEvent&) = 0;
    void OnMouseButtonEvent(const SDL_MouseButtonEvent&) = 0;
    void SetInPlay(bool);
    ~MenuState();
private:
    MenuState();
    friend TheMenuState;
private:
    Image background_;
    bool isPaused_;
    bool inPlay_;
    bool backgroundShifting_;
    int backgroundShift_;
};


#endif