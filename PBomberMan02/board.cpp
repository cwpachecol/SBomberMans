#include "board.h"
#include "constants.h"
#include <iostream>
#include <time.h>
using namespace std;

board::board()
{
	for (size_t i = 0; i < HEIGHT; ++i)
	{
		vector<int> temp;
		//pirma eilutė ir paskutinė eilutės
		if ((i == 0) || (i == HEIGHT - 1))
		{
			for (size_t j = 0; j < WIDTH; ++j)
			{
				my_board.push_back(new wall(j * SIZE, i * SIZE));
				temp.push_back(2);
			}
		}

		//lyginės eilutės
		else if (i % 2 == 0)
		{
			for (size_t j = 0; j < WIDTH; ++j)
			{
				if (j % 2 == 1)
				{
					my_board.push_back(new brick(j * SIZE, i * SIZE));
					temp.push_back(1);
				}
				else
				{
					my_board.push_back(new wall(j * SIZE, i * SIZE));
					temp.push_back(2);
				}
			}
		}

		//nelyginės eilutės
		else if (i % 2 == 1)
		{
			for (size_t j = 0; j < WIDTH; ++j)
			{
				if ((j == 0) || (j == WIDTH - 1))
				{
					my_board.push_back(new wall(j * SIZE, i * SIZE));
					temp.push_back(2);
				}
				else
				{
					my_board.push_back(new brick(j * SIZE, i * SIZE));
					temp.push_back(1);
				}
			}
		}

		board_index.push_back(temp);
	}
}

board::~board()
{
	for (auto tile : my_board)
		delete tile;

	/*for (size_t i = 0; i < HEIGHT; ++i)
	{
		//for (size_t j = 0; j < WIDTH; ++j)
			board_index.erase(board_index.begin() + WIDTH);
	}*/
}

void board::init()
{
	srand(time(0));
	int z = 0;
	for (size_t i = 0; i < HEIGHT; ++i)
	{
		for (size_t j = 0; j < WIDTH; ++j)
		{
			if (board_index[i][j] == 1)
			{
				int x = rand() % 4;
				if (x == 0)
				{
					my_board[z]->change_is_shown();
					board_index[i][j] = 0;
				}
			}

			//laisvos pradinės pozicijos
			//kairys viršutinis kampas
			if (i == 1)
			{
				if ((j == 1) || (j == 2))
				{
					if (board_index[i][j] == 1)
					{
						my_board[z]->change_is_shown();
						board_index[i][j] = 0;
					}
				}
			}
			if (i == 2)
			{
				if (j == 1)
				{
					if (board_index[i][j] == 1)
					{
						my_board[z]->change_is_shown();
						board_index[i][j] = 0;
					}
				}
			}
			//dešinys apatinis kampas
			if (i == HEIGHT - 2)
			{
				if ((j == WIDTH - 2) || (j == WIDTH - 3))
				{
					if (board_index[i][j] == 1)
					{
						my_board[z]->change_is_shown();
						board_index[i][j] = 0;
					}
				}
			}
			if (i == HEIGHT - 3)
			{
				if (j == WIDTH - 2)
				{
					if (board_index[i][j] == 1)
					{
						my_board[z]->change_is_shown();
						board_index[i][j] = 0;
					}
				}
			}
			++z;
		}
	}
}

void board::draw(SDL_Texture* brick_pic, SDL_Texture* wall_pic, SDL_Renderer* ren)
{
	for (auto tile : my_board)
	{
		if (dynamic_cast<wall*>(tile))
			tile->draw(wall_pic, ren);
		else if (dynamic_cast<brick*>(tile))
			tile->draw(brick_pic, ren);
	}
}

void board::update(vector<bomb*> my_bombs)
{
	for (auto m_bomb : my_bombs)
	{
		if (m_bomb->get_is_shown())
		{
			if (m_bomb->get_time_left() == 2)
			{
				int temp_x = m_bomb->get_coordinates().get_x();
				int temp_y = m_bomb->get_coordinates().get_y();

				//kai iš kairės
				if (board_index[temp_y / SIZE][temp_x / SIZE - 1] == 1)
					board_index[temp_y / SIZE][temp_x / SIZE - 1] = 0;
				//dešinė
				if (board_index[temp_y / SIZE][temp_x / SIZE + 1] == 1)
					board_index[temp_y / SIZE][temp_x / SIZE + 1] = 0;
				//viršus
				if (board_index[temp_y / SIZE - 1][temp_x / SIZE] == 1)
					board_index[temp_y / SIZE - 1][temp_x / SIZE] = 0;
				//apačia
				if (board_index[temp_y / SIZE + 1][temp_x / SIZE] == 1)
					board_index[temp_y / SIZE + 1][temp_x / SIZE] = 0;
			}
		}
	}
	my_board_update();
}

void board::my_board_update()
{
	int z = 0;
	for (size_t i = 0; i < HEIGHT; ++i)
	{
		for (size_t j = 0; j < WIDTH; ++j)
		{
			if (board_index[i][j] == 0)
				if (my_board[z]->get_is_shown())
					my_board[z]->change_is_shown();
			++z;
		}
	}
}