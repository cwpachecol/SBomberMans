#ifndef TOOLS_H
#define TOOLS_H

#include <SDL.h>

class SDL_Tools
{
	SDL_Window* my_window;
	SDL_Renderer* my_renderer;
	int x_position_of_window;
	int y_position_of_window;

	SDL_Texture* brick;
	SDL_Texture* block;

	SDL_Texture* red_player;
	SDL_Texture* yellow_player;

	SDL_Texture* m_bomb;
	SDL_Texture* fire;
public:
	SDL_Tools(int x, int y);
	~SDL_Tools();

	void init(const char* name = "Bomberman");
	void window_init(const char* name);
	void textures_init();


	SDL_Renderer* get_renderer() { return my_renderer; }
	SDL_Texture* get_brick() { return brick; }
	SDL_Texture* get_wall() { return block; }
	SDL_Texture* get_red_player() { return red_player; }
	SDL_Texture* get_yellow_player() { return yellow_player; }
	SDL_Texture* get_bomb() { return m_bomb; }
	SDL_Texture* get_fire() { return fire; }
};

#endif