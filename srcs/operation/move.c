#include "tetris.h"

void move_down(game_board *g) {
	Struct temp = create_shape(g->current);
	temp.row ++;
	if(is_movable(temp, g))
		g->current.row ++;
	else
		handle_blocks(g);
	delete_shape(temp);
	print_shape(g);
}

void move_left(game_board *g) {
	Struct temp = create_shape(g->current);
	temp.col --;
	if(is_movable(temp, g))
		g->current.col --;
	delete_shape(temp);
	print_shape(g);
}

void move_right(game_board *g) {
	Struct temp = create_shape(g->current);
	temp.col ++;
	if(is_movable(temp, g))
		g->current.col ++;
	delete_shape(temp);
	print_shape(g);
}
