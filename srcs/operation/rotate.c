#include "tetris.h"

void rotate(game_board *g) {
	Struct temp = create_shape(g->current);
	rotate_shape(temp);
	if(is_movable(temp, g))
		rotate_shape(g->current);
	delete_shape(temp);
	print_shape(g);
}