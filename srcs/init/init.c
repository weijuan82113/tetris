#include "tetris.h"

extern const char **StructsArray[BLOCKS_SIZE];

void init(game_board *g) {
    srand(time(0));
    g->final = 0;
    g->game_on = true;
    g->table[R][C];
    g->timer = TIMER;
    g->decrease = DECREASE;
	g->current = generate_block(StructsArray[rand() % BLOCKS_SIZE]);

    for (int i = 0; i < R; i ++) {
        for (int j = 0; j < C; j ++)
            g->table[i][j] = 0;
    }
    printf("test1");
    initscr();
    printf("test2");
	gettimeofday(&g->before_now, NULL);
	timeout(1);
	if (!is_movable(g->current, g))
		g->game_on = false;
    print_shape(g);
}