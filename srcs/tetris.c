#include "tetris.h"

int main(void)
{
	game_board board;

	init(&board);
	while (board.game_on) {
		switch (getch()) {
			case 's':
				move_down(&board);
				break;
			case 'd':
				move_right(&board);
				break;
			case 'a':
				move_left(&board);
				break;
			case 'w':
				rotate(&board);
				break;
			case ERR:
				//board.game_on = false;
				break;
		}
		gettimeofday(&(board.now), NULL);
		if (is_update(&board) && board.game_on) {
			move_down(&board);
			gettimeofday(&(board.before_now), NULL);
		}
	}

	finish(&board);

	return 0;
}