#include "thing.h"
#include "constants.h"

using namespace std;

thing::thing(int x, int y, bool val) : is_shown(val), my_coordinates(x, y) { }

thing::~thing() { }

void thing::change_is_shown() { is_shown = false; }

void thing::draw(SDL_Texture* pic, SDL_Renderer* ren)
{
	if (is_shown)
	{
		SDL_Rect drect = { my_coordinates.get_x(), my_coordinates.get_y(), SIZE, SIZE };
		SDL_RenderCopy(ren, pic, nullptr, &drect);
	}
}

void thing::change_to_show()
{
	is_shown = true;
}

void thing::change_not_to_show()
{
	is_shown = false;
}