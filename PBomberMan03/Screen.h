#ifndef SCREEN_H
#define SCREEN_H
#include <SDL.h>
#include "Vec2.h"
#include "Singleton.h"
class Screen;
typedef Singleton<Screen> TheScreen;
class Screen : public NonCopyable
{
public:
    bool Init(int w, int h, unsigned int flag);
    void Flip();
    void Clear();
    //SDL_Surface* GetScreen() const;
    SDL_Window* GetScreen() const;

    Vec2<int> ScreenBounds();
private:
    int m_screenWidth;
    int m_screenHeight;
    unsigned int m_flag;
    //SDL_Surface* m_screenLoc;
    SDL_Window* m_screenLoc;
    Screen();
    friend TheScreen;
};


#endif