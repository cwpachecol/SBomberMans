#include "fire.h"
#include "constants.h"

using namespace std;

fire::fire():thing(), time_left_shown(FIRE_TIME) { change_not_to_show(); }

fire::~fire() { }

void fire::update()
{
	if (get_is_shown())
		if (time_left_shown > 0)
			time_left_shown -= 2;

	if (time_left_shown == 0)
	{
		change_not_to_show();
		time_left_shown = FIRE_TIME;
	}
}

void fire::set_middle(int x, int y)
{
	my_coordinates.change_x_to(x);
	my_coordinates.change_y_to(y);
}

void fire::set_up(int x, int y)
{
	my_coordinates.change_x_to(x);
	my_coordinates.change_y_to(y);
}

void fire::set_down(int x, int y)
{
	my_coordinates.change_x_to(x);
	my_coordinates.change_y_to(y);
}

void fire::set_left(int x, int y)
{
	my_coordinates.change_x_to(x);
	my_coordinates.change_y_to(y);
}

void fire::set_right(int x, int y)
{
	my_coordinates.change_x_to(x);
	my_coordinates.change_y_to(y);
}

void fire::edit_is_shown(vector<vector<int> > my_board)
{
	if (my_board[my_coordinates.get_y() / SIZE][my_coordinates.get_x() / SIZE] == 2)
		change_not_to_show();
	else
		change_to_show();
}