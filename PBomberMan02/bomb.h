#ifndef BOMB_H
#define BOMB_H

#include "thing.h"
#include "fire.h"

class bomb : public thing
{
protected:
	int time_left_till_explosion;
	std::vector<fire*> my_fire;
	
public:
	bomb();
	virtual ~bomb();

	int get_time_left() { return time_left_till_explosion; }

	void update(std::vector<std::vector<int> > my_board);
	void put_a_bomb(int x, int y);
	void set_fire(int x, int y);
	void draw_fire(SDL_Renderer* ren, SDL_Texture* fire_pic);
};

#endif