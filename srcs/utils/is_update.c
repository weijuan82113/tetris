#include "tetris.h"

bool is_update(game_board *board) {
	suseconds_t time_now;
	suseconds_t time_before;

	time_now = board->now.tv_sec * 1000000 + board->now.tv_usec;
	time_before = board->before_now.tv_sec * 1000000 + board->before_now.tv_usec;

	return (time_now - time_before) > board->timer;
}