#include <assert.h>
#include <stdlib.h> // rand, srand
#include <stdio.h>  // printf, sleep
#include <conio.h> // getch
#include <stdbool.h>  // true, false
#include <string.h>  // memset
#include <time.h>  // time
#include "list.h"

// Some workaround for a MSVC compiler.
#if defined(_MSC_VER) 
#define sleep _sleep
#define kbhit _kbhit
#endif

#define ARROW_KEY 224
#define ARROW_KEYPAD 0
#define DIR_LEFT 75
#define DIR_RIGHT 77
#define DIR_UP 72
#define DIR_DOWN 80

// Definition of a game state struct.
typedef struct game_state
{
	node* snake;
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
	if (kbhit())
	{
		int const ckey = _getch();
		
		// https://stackoverflow.com/questions/34256016/what-values-do-arrow-keys-return-with-getch
		// Arrow keys return two codes. First is arrow key origin - numpad or
		// dedicated arrow keys. Second arrow code is returned. Arrow codes are
		// not universal and may vary depending on platform.
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
	// Current head position.
	int x = gs->snake->x, y = gs->snake->y;

	// Update head position considering direction.
	if (gs->dir == DIR_LEFT)
		x -= 1;
	else if (gs->dir == DIR_RIGHT)
		x += 1;
	else if (gs->dir == DIR_UP)
		y -= 1;
	else if (gs->dir == DIR_DOWN)
		y += 1;

	// Game over if snake hits screen borders or itself. node_contains looks for a
	// node at point (x, y). Returns NULL if no such a node is not present. If
	// there is we've hit ourself.
	if (x <= 0 || x >= gs->width - 1 ||
		y <= 0 || y >= gs->height - 1 ||
		node_contains(gs->snake->next, x, y) != NULL)
	{
		printf("Game over!\nYou have earned %d snake points.\n",
			node_count(gs->snake));
		exit(0);
	}

	// Create new root at current point after one step move.
	gs->snake = node_push_front(gs->snake, x, y);

	if (gs->food_x == x && gs->food_y == y)
	{
		// Food drop is eaten. Reset drop. Do nothing to snake.
		gs->food_x = 0;
		gs->food_y = 0;
	}
	else
	{
		// Move towards food drop. Remove tail node. Snake size remains unchanged
		// since we've just created new root node.
		node_pop_back(gs->snake);
	}

	// Generate new food drop.
	if (gs->food_x == 0 && gs->food_y == 0)
	{
		int const x = 1 + rand() % (gs->width - 2);
		int const y = 1 + rand() % (gs->height - 2);

		if (node_contains(gs->snake->next, x, y) == NULL)
		{
			gs->food_x = x;
			gs->food_y = y;
		}
	}
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
			else if (x == gs->snake->x && y == gs->snake->y)
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
			else if ((n = node_contains(gs->snake->next, x, y)))
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
		if (y == 1)
		{
			printf(" %d", node_count(gs->snake));
		}

		printf("\n");
	}
}

int main()
{
	// Add some randomness to the game.
	srand((int)time(0));

	// Make head of a snake. We reference further snake head as simply snake.
	gs.snake = malloc(sizeof(node));
	memset(gs.snake, 0, sizeof(node));

	gs.snake->x = 39;
	gs.snake->y = 10;

	// Add two extra snake parts.
	node_push_back(gs.snake, 40, 10);
	node_push_back(gs.snake, 41, 10);

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

		// On Windows platform ignore warning.
		sleep(50);
	}
}
