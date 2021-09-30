#ifndef BRICK_H
#define BRICK_H

#include "thing.h"
class brick : public thing
{
public:
	brick(int x, int y);
	~brick();
};

#endif