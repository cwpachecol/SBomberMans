#ifndef BOMBS_H
#define BOMBS_H

#include "red_bomb.h"
#include "yellow_bomb.h"

class bombs
{
	std::vector<bomb*> my_bombs;
public:
	bombs();
	~bombs();

	void update(std::vector<std::vector<int> > my_board);
	void draw(SDL_Texture* pic, SDL_Renderer* ren, SDL_Texture* fire_pic);

	std::vector<bomb*> get_bombs() { return my_bombs; }
};

#endif