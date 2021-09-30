#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "GameState.h"
#include "NonCopyable.h"
#include "Singleton.h"

class Game;
typedef Singleton<Game> TheGame;

class Game: public NonCopyable
{
public: 
    void Run();
    void SetState(GameState* state);

private:
    Game();
    void Update();
    void Draw();

private:
    GameState* currentState_;
    friend TheGame;

};

#endif