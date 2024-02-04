#include "tetris.h"

void print_shape(game_board *g) {
	char buffer[R][C];

	for (int i = 0; i < g->current.width; i ++) {
		for (int j = 0; j < g->current.width; j ++)
			buffer[g->current.row + i][g->current.col + j] = g->table[i][j];
	}
	for (int i = 0; i < g->current.width; i ++) {
		for (int j = 0; j < g->current.width; j ++) {
			if (g->current.array[i][j] == '#')
				buffer[g->current.row + i][g->current.col + j] = '#';
		}
	}
	clear();
	for (int i = 0; i < C - 9; i ++)
		printw(" ");
	printw("42 Tetris\n");
	for (int i = 0; i < R; i ++) {
		for (int j = 0; j < C; j ++)
			printw("%c ", buffer[i][j]);
		printw("\n");
	}
	printw("\nScore: %d\n", g->final);
}