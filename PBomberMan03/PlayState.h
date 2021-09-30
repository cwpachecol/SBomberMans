#ifndef PLAYSTATE_H_INCLUDED
#define PLAYSTATE_H_INCLUDED
#include "GameState.h"
#include "Singleton.h"
#include "NonCopyable.h"
#include "Player.h"
#include <vector>
class PlayState;
typedef Singleton<PlayState> ThePlayState;

class PlayState:public GameState
{
public:
    ~PlayState();
    virtual void OnActive();
    virtual void OnInactive();
    virtual void Update();
    virtual void Draw();
    void OnKeyboardEvent(const SDL_KeyboardEvent&) = 0;
    void SetPlayerNum(int num);
    void SetLevel(int level);
    void RefundBomb(int tag);
    void Reset();
    AABB2D GetScreenSize()const;
private:
    PlayState();
    friend ThePlayState;
    void AddPlayers();
    void WinState(int winner);

private:
    //pointer to container of data from load state
    std::vector<Player> players_;
    std::vector<Player*> activePlayers_;
    Image* background_;
    Image* screen_;
    Image* screenBackground_;
    Image* winBackground_;
    int numOfPlayers_;
    int level_;
    std::string banner_;
    bool isPaused_;
    bool isWin_;
    bool backgroundShifting_;
    int backgroundShift_;
    AABB2D gameboyScreen_;
};

#endif