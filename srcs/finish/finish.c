#include "tetris.h"

void finish(game_board *g)
{
	delete_shape(g->current);
	endwin();
	for(int i = 0; i < R; i ++) {
		for(int j = 0; j < C; j ++)
			printf("%c ", g->table[i][j]);
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", g->final);
}