#include "player.h"
#include "constants.h"

using namespace std;

player::player(int x, int y) : thing(x, y) { }

player::~player() { }

bool player::check_go_up(vector<vector<int> > index, vector<bomb*> my_bombs)
{
	int temp_x = my_coordinates.get_x();
	int temp_y = my_coordinates.get_y();

	if (temp_x % SIZE == 0)
	{
		if (temp_y % SIZE == 0)
		{
			if (index[temp_y / SIZE - 1][temp_x / SIZE] > 0)
				return false;
		}
	}
	
	else if (temp_x % SIZE != 0)
	{
		if (temp_y % SIZE == 0)
		{
			if (index[temp_y / SIZE - 1][temp_x / SIZE] > 0)
				return false;
			if (index[temp_y / SIZE - 1][temp_x / SIZE + 1] > 0)
				return false;
		}
	}

	for (auto m_bomb : my_bombs)
		if (m_bomb->get_is_shown())
			if (m_bomb->get_coordinates().get_x() == temp_x)
				if (m_bomb->get_coordinates().get_y() + SIZE == temp_y)
					return false;

	return true;
}

bool player::check_go_down(vector<vector<int> > index, vector<bomb*> my_bombs)
{
	int temp_x = my_coordinates.get_x();
	int temp_y = my_coordinates.get_y();

	if (temp_x % SIZE == 0)
	{
		if (temp_y % SIZE == 0)
		{
			if (index[temp_y / SIZE + 1][temp_x / SIZE] > 0)
				return false;
		}
	}

	else if (temp_x % SIZE != 0)
	{
		if (temp_y % SIZE == 0)
		{
			if (index[temp_y / SIZE + 1][temp_x / SIZE] > 0)
				return false;
			if (index[temp_y / SIZE + 1][temp_x / SIZE + 1] > 0)
				return false;
		}
	}

	for (auto m_bomb : my_bombs)
		if (m_bomb->get_is_shown())
			if (m_bomb->get_coordinates().get_x() == temp_x)
				if (m_bomb->get_coordinates().get_y() - SIZE == temp_y)
					return false;
					
	return true;
}

bool player::check_go_left(vector<vector<int> > index, vector<bomb*> my_bombs)
{
	int temp_x = my_coordinates.get_x();
	int temp_y = my_coordinates.get_y();

	if (temp_y % SIZE == 0)
	{
		if (temp_x % SIZE == 0)
		{
			if (index[temp_y / SIZE][temp_x / SIZE - 1] > 0)
				return false;
		}
	}
	else if (temp_y % SIZE != 0)
	{
		if (temp_x % SIZE == 0)
		{
			if (index[temp_y / SIZE][temp_x / SIZE - 1] > 0)
				return false;
			if (index[temp_y / SIZE + 1][temp_x / SIZE - 1] > 0)
				return false;
		}
	}

	for (auto m_bomb : my_bombs)
		if (m_bomb->get_is_shown())
			if (m_bomb->get_coordinates().get_y() == temp_y)
				if (m_bomb->get_coordinates().get_x() + SIZE == temp_x)
					return false;

	return true;
}

bool player::check_go_right(vector<vector<int> > index, vector<bomb*> my_bombs)
{
	int temp_x = my_coordinates.get_x();
	int temp_y = my_coordinates.get_y();

	if (temp_y % SIZE == 0)
	{
		if (temp_x % SIZE == 0)
		{
			if (index[temp_y / SIZE][temp_x / SIZE + 1] > 0)
				return false;
		}
	}

	else if (temp_y % SIZE != 0)
	{
		if (temp_x % SIZE == 0)
		{
			if (index[temp_y / SIZE][temp_x / SIZE + 1] > 0)
				return false;
			if (index[temp_y / SIZE + 1][temp_x / SIZE + 1] > 0)
				return false;
		}
	}

	for (auto m_bomb : my_bombs)
		if (m_bomb->get_is_shown())
			if (m_bomb->get_coordinates().get_y() == temp_y)
				if (m_bomb->get_coordinates().get_x() - SIZE == temp_x)
					return false;

	return true;
}

void player::update(std::vector<bomb*> my_bombs)
{
	for (auto m_bomb : my_bombs)
	{
		//if (m_bomb->get_is_shown())
		//{
			if (m_bomb->get_time_left() <= 202)
			{
				if ((my_coordinates.get_x() > m_bomb->get_coordinates().get_x() - 2 * SIZE) &&
					(my_coordinates.get_x() < m_bomb->get_coordinates().get_x() + 2 * SIZE))
					if (my_coordinates.get_y() == m_bomb->get_coordinates().get_y())
						change_is_shown();
				else if ((my_coordinates.get_y() > m_bomb->get_coordinates().get_y() - 2 * SIZE) &&
					(my_coordinates.get_y() < m_bomb->get_coordinates().get_y() + 2 * SIZE))
					if (my_coordinates.get_x() == m_bomb->get_coordinates().get_x())
						change_is_shown();
				//papildomai, jei kampu
				//kairys viršutinis
				/*else if ((my_coordinates.get_x() > m_bomb->get_coordinates().get_x() - SIZE) &&
					(my_coordinates.get_x() < m_bomb->get_coordinates().get_x()))
					if ((my_coordinates.get_y() == m_bomb->get_coordinates().get_y() - SIZE))
						change_is_shown();
				//kairys apatinis
				//dešinys viršutinis
				//dešinys apatinis
				/*if ((my_coordinates.get_x() > m_bomb->get_coordinates().get_x() - 2 * SIZE) &&
					(my_coordinates.get_x() < m_bomb->get_coordinates().get_x() + 2 * SIZE))
					if ((my_coordinates.get_y() > m_bomb->get_coordinates().get_y() - 2 * SIZE) &&
						(my_coordinates.get_y() < m_bomb->get_coordinates().get_y() + 2 * SIZE))
						change_is_shown();*/
			}
		//}
	}
}