#include "tetris.h"

extern const char **StructsArray[BLOCKS_SIZE];

static int count_matched_line(game_board *g);

void handle_blocks(game_board *g) {
	g->final += 100 * count_matched_line(g);
	delete_shape(g->current);
	g->current = generate_block(StructsArray[rand() % BLOCKS_SIZE]);
	if(!is_movable(g->current, g))
		g->game_on = false;
}

static int count_matched_line(game_board *g) {
	for (int i = 0; i < g->current.width; i ++) {
		for (int j = 0; j < g->current.width; j ++) {
			if (g->current.array[i][j] == '#')
				g->table[g->current.row + i][g->current.col + j] = g->current.array[i][j];
		}
	}
	int count = 0;
	for(int n = 0; n < R; n ++) {
		int sum = 0;
		for(int m = 0; m < C; m ++) {
			if (g->table[n][m] == '#')
				sum ++;
		}
		if(sum == C) {
			count ++;
			for(int k = n; k > 0; k --) {
				for(int l = 0; l < C; l ++)
					g->table[k][l] = g->table[k - 1][l];
			}
			for(int l = 0; l < C; l ++)
				g->table[0][l] = 0;
			g->timer -= g->decrease --;
		}
	}

	return count;
}