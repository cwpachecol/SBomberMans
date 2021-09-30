#ifndef RED_H
#define RED_H

#include "player.h"

class red_player : public player
{
public:
	red_player(int x, int y);
	~red_player();
	void handle_event(std::vector<std::vector<int> > index, std::vector<bomb*> my_bombs);
};

#endif