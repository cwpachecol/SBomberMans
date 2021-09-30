#ifndef BOARD_H
#define BOARD_H

#include "brick.h"
#include "wall.h"
#include "bombs.h"
#include <SDL.h>

class board
{
protected:
	std::vector<thing*> my_board;
	std::vector<std::vector<int> > board_index;
public:
	board();
	~board();

	void init();
	void draw(SDL_Texture* brick_pic, SDL_Texture* wall_pic, SDL_Renderer* ren);
	void update(std::vector<bomb*> my_bombs);
	void my_board_update();

	std::vector<std::vector<int> > get_board_index() { return board_index; }
};

#endif