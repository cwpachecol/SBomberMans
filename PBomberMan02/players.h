#ifndef PLAYERS_H
#define PLAYERS_H

#include <vector>
#include <SDL.h>
#include "red_player.h"
#include "yellow_player.h"

class players
{
	std::vector<player*> my_players;
public:
	players();
	~players();

	void draw(SDL_Renderer* ren, SDL_Texture* red, SDL_Texture* yellow);
	void handle_event(std::vector<std::vector<int> > index, std::vector<bomb*> my_bombs);
	bool update(std::vector<bomb*> my_bombs);
};

#endif