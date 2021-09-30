#ifndef YELLOW_H
#define YELLOW_H

#include "player.h"

class yellow_player : public player
{
public:
	yellow_player(int x, int y);
	~yellow_player();
	void handle_event(std::vector<std::vector<int> > index, std::vector<bomb*> my_bombs);
};

#endif