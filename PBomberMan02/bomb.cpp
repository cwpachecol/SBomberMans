#include "bomb.h"
#include "constants.h"

using namespace std;

bomb::bomb() : thing(false), time_left_till_explosion(BOMB_TIME) {
	change_is_shown();
	for (size_t i = 0; i < 5; ++i)
		my_fire.push_back(new fire());
}

bomb::~bomb()
{
	for (auto m_fire : my_fire)
		delete m_fire;
}

void bomb::update(vector<vector<int> > my_board)
{
	if (get_is_shown()) 
		time_left_till_explosion -= 2;

	if (time_left_till_explosion == 202)
	{
		for (auto m_fire : my_fire)
			m_fire->edit_is_shown(my_board);
	}

	if (time_left_till_explosion == 0)
	{
		change_not_to_show();
		time_left_till_explosion = BOMB_TIME;
	}

	for (auto m_fire : my_fire)
		m_fire->update();
}

void bomb::put_a_bomb(int x, int y)
{
	if (x % SIZE == 0)
	{
		if (y % SIZE == 0)
		{
			my_coordinates.change_x_to(x);
			my_coordinates.change_y_to(y);
			change_to_show();
			set_fire(x, y);
		}
		else if (y % SIZE != 0)
		{
			if (y % SIZE < SIZE / 2)
				y = y - y % SIZE;
			else if (y % SIZE >= SIZE / 2)
				y = y - y % SIZE + SIZE;
			my_coordinates.change_x_to(x);
			my_coordinates.change_y_to(y);
			change_to_show();
			set_fire(x, y);
		}
	}

	else if(x % SIZE != 0)
	{
		if (x % SIZE < SIZE / 2)
			x = x - x % SIZE;
		else if (x % SIZE >= SIZE / 2)
			x = x - x % SIZE + SIZE;
		my_coordinates.change_x_to(x);
		my_coordinates.change_y_to(y);
		change_to_show();
		set_fire(x, y);
	}
}

void bomb::set_fire(int x, int y)
{
	my_fire[0]->set_middle(x, y);
	my_fire[1]->set_up(x, y - SIZE);
	my_fire[2]->set_down(x, y + SIZE);
	my_fire[3]->set_left(x - SIZE, y);
	my_fire[4]->set_right(x + SIZE, y);
}

void bomb::draw_fire(SDL_Renderer* ren, SDL_Texture* fire_pic)
{
	for (auto m_fire : my_fire)
		m_fire->draw(fire_pic, ren);
}