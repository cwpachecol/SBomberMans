#ifndef WALL_H
#define WALL_H

#include "thing.h"

class wall:public thing
{
public:
	wall(int x, int y);
	~wall();
	void change_is_shown() {}
};

#endif