#ifndef THING_H
#define THING_H

#include <SDL.h>
#include "coordinates.h"
#include <iostream>
#include <vector>

class thing
{
protected:
	bool is_shown;
	coordinates my_coordinates;
public:
	thing(int x = 0, int y = 0, bool val = true);
	virtual ~thing();
	virtual void change_is_shown();
	void draw(SDL_Texture* pic, SDL_Renderer* ren);

	bool get_is_shown() { return is_shown; }
	coordinates get_coordinates() { return my_coordinates; }

	void change_to_show();
	void change_not_to_show();
};

#endif