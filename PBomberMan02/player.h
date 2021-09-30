#ifndef PLAYER_H
#define PLAYER_H

#include "thing.h"
#include "red_bomb.h"
#include "yellow_bomb.h"

class player : public thing
{
public:
	player(int x, int y);
	~player();

	virtual void handle_event(std::vector<std::vector<int> > index, std::vector<bomb*> my_bombs) = 0;

	bool check_go_up(std::vector<std::vector<int> > index, std::vector<bomb*> my_bombs);
	bool check_go_down(std::vector<std::vector<int> > index, std::vector<bomb*> my_bombs);
	bool check_go_left(std::vector<std::vector<int> > index, std::vector<bomb*> my_bombs);
	bool check_go_right(std::vector<std::vector<int> > index, std::vector<bomb*> my_bombs);

	void update(std::vector<bomb*> my_bombs);
};

#endif