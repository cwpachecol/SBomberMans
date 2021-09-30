#ifndef GAME_H
#define GAME_H

#include "SDL_Tools.h"
#include "board.h"
#include "players.h"
#include "bombs.h"

class game
{
	bool in_progress;
	SDL_Tools my_tools;
	board my_board;
	players my_players;
	bombs my_bombs;
public:
	game(int x = -1, int y = -1);
	~game();

	void init();
	void update();
	void handle_events();
	void draw();

	bool get_in_progress() { return in_progress; }
};

#endif