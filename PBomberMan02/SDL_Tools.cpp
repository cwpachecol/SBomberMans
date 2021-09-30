#include "SDL_Tools.h"
#include "constants.h"
#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

SDL_Tools::SDL_Tools(int x, int y): my_window(nullptr), my_renderer(nullptr),
	x_position_of_window(x), y_position_of_window(y),
	brick(nullptr), block(nullptr), red_player(nullptr), yellow_player(nullptr),
	m_bomb(nullptr), fire(nullptr) { }


SDL_Tools::~SDL_Tools()
{
	SDL_DestroyTexture(brick);
	SDL_DestroyTexture(block);
	SDL_DestroyTexture(red_player);
	SDL_DestroyTexture(yellow_player);
	SDL_DestroyTexture(m_bomb);
	SDL_DestroyTexture(fire);

	SDL_DestroyWindow(my_window);
	SDL_DestroyRenderer(my_renderer);
	SDL_Quit();
}

void SDL_Tools::init(const char* name)
{
	window_init(name);
	textures_init();
}

void SDL_Tools::window_init(const char* name)
{
	assert(SDL_Init(SDL_INIT_VIDEO) >= 0);

	//skirtingi pozicijų atvejai langui atidaryti
	if ((x_position_of_window == -1) && (y_position_of_window == -1)) {
		my_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * SIZE, HEIGHT * SIZE, SDL_WINDOW_SHOWN);
		assert(my_window);
	}
	if ((x_position_of_window == -1) && (y_position_of_window != -1)) {
		my_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, y_position_of_window, WIDTH * SIZE, HEIGHT * SIZE, SDL_WINDOW_SHOWN);
		assert(my_window);
	}
	if ((x_position_of_window != -1) && (y_position_of_window == -1)) {
		my_window = SDL_CreateWindow(name, x_position_of_window, SDL_WINDOWPOS_CENTERED, WIDTH * SIZE, HEIGHT * SIZE, SDL_WINDOW_SHOWN);
		assert(my_window);
	}
	if ((x_position_of_window != -1) && (y_position_of_window != -1)) {
		my_window = SDL_CreateWindow(name, x_position_of_window, y_position_of_window, WIDTH * SIZE, HEIGHT * SIZE, SDL_WINDOW_SHOWN);
		assert(my_window);
	}

	my_renderer = SDL_CreateRenderer(my_window, -1, 0);
	SDL_SetRenderDrawColor(my_renderer, 34, 139, 34, 255);
	assert(my_renderer);

}

void SDL_Tools::textures_init()
{
	SDL_Surface* surface = SDL_LoadBMP("plyta.bmp");
	assert(surface);
	brick = SDL_CreateTextureFromSurface(my_renderer, surface);
	SDL_FreeSurface(surface);

	surface = SDL_LoadBMP("blokas.bmp");
	assert(surface);
	block = SDL_CreateTextureFromSurface(my_renderer, surface);
	SDL_FreeSurface(surface);

	surface = SDL_LoadBMP("red.bmp");
	assert(surface);
	red_player = SDL_CreateTextureFromSurface(my_renderer, surface);
	SDL_FreeSurface(surface);

	surface = SDL_LoadBMP("yellow.bmp");
	assert(surface);
	yellow_player = SDL_CreateTextureFromSurface(my_renderer, surface);
	SDL_FreeSurface(surface);

	surface = SDL_LoadBMP("bomba.bmp");
	assert(surface);
	m_bomb = SDL_CreateTextureFromSurface(my_renderer, surface);
	SDL_FreeSurface(surface);

	surface = SDL_LoadBMP("fire.bmp");
	assert(surface);
	fire = SDL_CreateTextureFromSurface(my_renderer, surface);
	SDL_FreeSurface(surface);
}
