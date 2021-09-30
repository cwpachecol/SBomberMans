#include "yellow_player.h"

using namespace std;

yellow_player::yellow_player(int x, int y) : player(x, y) { }

yellow_player::~yellow_player() { }

void yellow_player::handle_event(vector<vector<int> > index, vector<bomb*> my_bombs)
{
	const auto state = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();

	//ėjimas aukštyn
	if (state[SDL_SCANCODE_UP]) {
		if (check_go_up(index, my_bombs))
			my_coordinates.add_to_y(-1);
	}

	//ėjimas žemyn
	if (state[SDL_SCANCODE_DOWN]) {
		if (check_go_down(index, my_bombs))
			my_coordinates.add_to_y(1);
	}

	//ėjimas dešinėn
	if (state[SDL_SCANCODE_RIGHT]) {
		if (check_go_right(index, my_bombs))
			my_coordinates.add_to_x(1);
	}

	//ėjimas kairėn
	if (state[SDL_SCANCODE_LEFT]) {
		if (check_go_left(index, my_bombs))
			my_coordinates.add_to_x(-1);
	}

	if (state[SDL_SCANCODE_SPACE]) {
		for (auto m_bomb : my_bombs)
			if (dynamic_cast<yellow_bomb*>(m_bomb))
				if (!m_bomb->get_is_shown())
					m_bomb->put_a_bomb(my_coordinates.get_x(), my_coordinates.get_y());
	}
}