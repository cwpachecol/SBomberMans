#include "bombs.h"

using namespace std;

bombs::bombs()
{
	my_bombs.push_back(new red_bomb());
	my_bombs.push_back(new yellow_bomb());
}

bombs::~bombs()
{
	for (auto m_bomb : my_bombs)
		delete m_bomb;
}

void bombs::update(vector<vector<int> > my_board)
{
	for (auto m_bomb : my_bombs)
		m_bomb->update(my_board);
}

void bombs::draw(SDL_Texture* pic, SDL_Renderer* ren, SDL_Texture* fire_pic)
{
	for (auto m_bomb : my_bombs)
	{
		if(m_bomb->get_time_left() >= 202)
			m_bomb->draw(pic, ren);
		m_bomb->draw_fire(ren, fire_pic);
	}
}