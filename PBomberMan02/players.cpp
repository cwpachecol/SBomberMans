#include "players.h"
#include "constants.h"

using namespace std;

players::players()
{
	my_players.push_back(new red_player(SIZE, SIZE));
	my_players.push_back(new yellow_player((WIDTH - 2) * SIZE, (HEIGHT - 2) * SIZE));
}


players::~players()
{
	for (auto pl : my_players)
		delete pl;
}

void players::draw(SDL_Renderer* ren, SDL_Texture* red, SDL_Texture* yellow)
{
	for (auto pl : my_players)
	{
		if (dynamic_cast<red_player*>(pl))
			pl->draw(red, ren);
		else
			pl->draw(yellow, ren);
	}
}

void players::handle_event(vector<vector<int> > index, vector<bomb*> my_bombs)
{
	for (auto pl : my_players)
	{
		pl->handle_event(index, my_bombs);
	}
}

bool players::update(vector<bomb*> my_bombs)
{
	for (auto m_player : my_players)
		m_player->update(my_bombs);

	int n = 0;
	for (auto m_player : my_players)
		if (m_player->get_is_shown())
			++n;

	if (n > 1)
		return true;
	else
		return false;
}