#include "game.h"
#include <iostream>
#include <SDL.h>

using namespace std;

game::game(int x, int y): in_progress(true), my_tools(x, y), my_board(), my_players(), my_bombs() { }


game::~game() { }

void game::init()
{
	my_tools.init();
	my_board.init();
}

void game::update()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
		in_progress = false;

	const auto state = SDL_GetKeyboardState(NULL);
	SDL_PumpEvents();
	if (state[SDL_SCANCODE_Q])
		in_progress = false;

	my_board.update(my_bombs.get_bombs());
	my_bombs.update(my_board.get_board_index());

	if (!my_players.update(my_bombs.get_bombs()))
		in_progress = false;
}

void game::handle_events()
{
	my_players.handle_event(my_board.get_board_index(), my_bombs.get_bombs());
}

void game::draw()
{
	SDL_RenderClear(my_tools.get_renderer());

	my_board.draw(my_tools.get_brick(), my_tools.get_wall(), my_tools.get_renderer());
	my_bombs.draw(my_tools.get_bomb(), my_tools.get_renderer(), my_tools.get_fire());
	my_players.draw(my_tools.get_renderer(), my_tools.get_red_player(), my_tools.get_yellow_player());

	SDL_RenderPresent(my_tools.get_renderer());
}