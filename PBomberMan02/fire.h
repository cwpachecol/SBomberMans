#ifndef FIRE_H
#define FIRE_H

#include "thing.h"
class fire : public thing
{
	int time_left_shown;
public:
	fire();
	~fire();

	void update();

	void set_middle(int x, int y);
	void set_up(int x, int y);
	void set_down(int x, int y);
	void set_left(int x, int y);
	void set_right(int x, int y);
	void edit_is_shown(std::vector<std::vector<int> > my_board);
};

#endif