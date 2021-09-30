#include "red_player.h"

using namespace std;

red_player::red_player(int x, int y) : player(x, y) { }

red_player::~red_player() { }

void red_player::handle_event(vector<vector<int> > index, vector<bomb*> my_bombs)
{
	const auto state = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();

	//ėjimas aukštyn
	if (state[SDL_SCANCODE_W]) {
		if (check_go_up(index, my_bombs))
			my_coordinates.add_to_y(-1);
	}

	//ėjimas žemyn
	if (state[SDL_SCANCODE_S]) {
		if (check_go_down(index, my_bombs))
			my_coordinates.add_to_y(1);
	}

	//ėjimas dešinėn
	if (state[SDL_SCANCODE_D]) {
		if (check_go_right(index, my_bombs))
			my_coordinates.add_to_x(1);
	}

	//ėjimas kairėn
	if (state[SDL_SCANCODE_A]) {
		if (check_go_left(index, my_bombs))
			my_coordinates.add_to_x(-1);
	}

	if (state[SDL_SCANCODE_Z]) {
		for (auto m_bomb : my_bombs)
			if (dynamic_cast<red_bomb*>(m_bomb))
				if (!m_bomb->get_is_shown())
					m_bomb->put_a_bomb(my_coordinates.get_x(), my_coordinates.get_y());
	}
}