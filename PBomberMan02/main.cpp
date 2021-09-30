#include "game.h"

using namespace std;

int main(int argv, char* argc[])
{
	const int FPS = 60;
	const int frame_delay = 700 / FPS;
	Uint32 frame_start;
	int frame_time;

	game* my_game = new game();

	my_game->init();

	while (my_game->get_in_progress())
	{
		frame_start = SDL_GetTicks();

		my_game->draw();
		my_game->handle_events();
		my_game->update();

		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time)
			SDL_Delay(frame_delay - frame_time);
	}

	delete my_game;
	return 0;
}