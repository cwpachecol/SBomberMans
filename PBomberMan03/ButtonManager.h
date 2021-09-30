#ifndef BUTTONMANAGER_H_INCLUDED
#define BUTTONMANAGER_H_INCLUDED	
#include "Singleton.h"
#include "NonCopyable.h"
#include <vector>
#include "Button.h"
#include "LoadState.h"
#include "PlayState.h"
#include "DPad.h"
#include "Game.h"

class ButtonManager;
typedef Singleton<ButtonManager> TheButtonManager;
enum BUTTON_TAGS{PUP_TAG=0,PDOWN_TAG,LVLUP_TAG,LVLDOWN_TAG,PLAY_TAG,QUIT_TAG,RESET_TAG};
class ButtonManager:public NonCopyable
{
public:
    void HandleButtonClick(int tag);
    void ClickAt(Vec2f click);
    void MouseMove(Vec2f click);
    void Draw();
private:
    ButtonManager();
    DPad dPad;
    bool inPlay_;
    friend TheButtonManager;
    std::vector<Button*> buttons_;
};

#endif