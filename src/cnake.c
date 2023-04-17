#include <assert.h>
#include <stdlib.h> // rand, srand
#include <stdio.h>  // printf, sleep
#include <conio.h> // getch
#include <stdbool.h>  // true, false
#include <string.h>  // memset
#include <time.h>  // time
//#include <unistd.h>
#include "list.h"

#if defined(_MSC_VER) 
#define sleep _sleep
#endif

#define ARROW_KEY 224
#define ARROW_KEYPAD 0
#define DIR_LEFT 75
#define DIR_RIGHT 77
#define DIR_UP 72
#define DIR_DOWN 80

// Game state struct definition.
typedef struct
{
	node snake;
	int dir;
	int food_x;
	int food_y;
	int width;
	int height;

} game_state;

// Game state global struct.
game_state gs;

int read_input(game_state* gs)
{
	repeat:
	if (_kbhit())
	{
		int const ckey = _getch();

		// ƒл¤ стрелок возвращаетс¤ два кода. —перва код откуда была нажата стрелка
		// 224 дл¤ непосредственно стрелок и 0 дл¤ numpad'а. ѕоток код стрелки. Ёти
		// коды не ¤вл¤ютс¤ универсальными и могут отличатьс¤ на других платформах.
		// For arrow buttons two codes are returned insted of one. First arrow key
		// source is returned either arrow keys or keypad arrow.
		if (ckey == ARROW_KEY || ckey == ARROW_KEYPAD)
			goto repeat;

		// Forbid opposite directions. For example if current direction is
		// leftwards it is impossible to switch direction to rightwards.
		if ((ckey == DIR_LEFT && ckey != DIR_RIGHT) ||
			(ckey == DIR_RIGHT && ckey != DIR_LEFT) ||
			(ckey == DIR_UP && ckey != DIR_DOWN) ||
			(ckey == DIR_DOWN && ckey != DIR_UP))
		{
			gs->dir = ckey;
		}
	}

	// Get input direction. Assume this function return only valid directions.
	assert(gs->dir == DIR_LEFT || gs->dir == DIR_RIGHT ||
		gs->dir == DIR_UP || gs->dir == DIR_DOWN);

	// Return direction for convenience.
	return gs->dir;
}

void process_game(game_state* gs)
{
	node* const new_node = malloc(sizeof(node));
	new_node->x = gs->snake.x;
	new_node->y = gs->snake.y;

	node_push_front(&gs->snake, new_node);

	// Update snake from head to tail.
	if (gs->dir == DIR_LEFT)
		gs->snake.x -= 1;
	else if (gs->dir == DIR_RIGHT)
		gs->snake.x += 1;
	else if (gs->dir == DIR_UP)
		gs->snake.y -= 1;
	else if (gs->dir == DIR_DOWN)
		gs->snake.y += 1;

	// Game over if snake hits screen borders or itself.
	if (gs->snake.x <= 0 || gs->snake.x >= gs->width - 1 ||
		gs->snake.y <= 0 || gs->snake.y >= gs->height - 1 ||
		node_contains(gs->snake.next, gs->snake.x, gs->snake.y) != NULL)
	{
		printf("Game over!\nYou have earned %d snake points\n",
			node_size(&gs->snake));
		exit(0);
	}

	//if (false)
		//food = point(0, 0);
	//else
		node_pop_back(&gs->snake);

	// Generate new food drop.
	#if 0
	if (food == point(0, 0))
	{
		point const food_drop = point(1 + rand() % (width - 2), 1 + rand() % (height - 2));

		if (std::find(snake.begin(), snake.end(), food_drop) == snake.end())
		{
			food = food_drop;
		}
	}
	#endif
}

void draw_screen(game_state* gs)
{
	for (int y = 0; y < gs->height; ++y)
	{
		for (int x = 0; x < gs->width; ++x)
		{
			node* n = NULL;

			// Draw corner, top and bottom margin.
			if (y == 0 || y == gs->height - 1)
			{
				if (x > 0 && x < gs->width - 1)
					printf("-");
				else
					printf("+");
			}

			// Draw left and right margin.
			else if (x == 0 || x == gs->width - 1)
			{
				if (y > 0 && y < gs->height)
					printf("|");
			}

			// Draw food drop.
			else if (x == gs->food_x && y == gs->food_y)
			{
				printf("o");
			}

			// Draw head.
			else if (x == gs->snake.x && y == gs->snake.y)
			{
				if (gs->dir == DIR_LEFT)
					printf("<");
				else if (gs->dir == DIR_RIGHT)
					printf(">");
				else if (gs->dir == DIR_UP)
					printf("A");
				else if (gs->dir == DIR_DOWN)
					printf("V");
			}

			// Draw the rest of a snake.
			else if ((n = node_contains(gs->snake.next, x, y)))
			{
				// Draw tail (last node) with different char.
				if (n->next == NULL)
					printf("?");
				else
					printf(".");
			}

			// Draw emptyness.
			else
			{
				printf(" ");
			}
		}

		// Print score.
		if (y == 4)
			printf("\tscore: %d", node_size(&gs->snake));

		printf("\n");
	}
}

int main()
{
	// Add some randomness to the game.
	srand((int)time(0));

	// Make head of a snake. We reference further snake head as simply snake.
	memset(&gs.snake, 0, sizeof(node));

	gs.snake.x = 39;
	gs.snake.y = 10;

	// Add two extra snake parts.
	node_push_back(&gs.snake, 40, 10);
	node_push_back(&gs.snake, 41, 10);

	// Console window size in chars.
	gs.width = 59;
	gs.height = 29;

	// Initial food drop set to zero point.
	gs.food_x = 0;
	gs.food_y = 0;

	// Set initial direction.
	gs.dir = DIR_LEFT;

	// Simple game loop: clear, input, update, draw.
	while (1)
	{
		// Clear screen. Thanks to Jamesits.
		// https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
		system("@cls||clear");

		read_input(&gs);
		process_game(&gs);
		draw_screen(&gs);

		sleep(50);
	}
}
