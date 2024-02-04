#include "tetris.h"

bool is_movable(Struct shape, game_board *g) {
	for (int i = 0; i < shape.width; i ++) {
		for (int j = 0; j < shape.width; j ++) {
			if (shape.array[i][j] &&
					(shape.col + j < 0 || shape.col + j >= C || shape.row + i >= R ||
							g->table[shape.row + i][shape.col + j]))
				return false;
		}
	}
	return true;
}