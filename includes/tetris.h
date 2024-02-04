#ifndef TETRIS_H
# define TETRIS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <time.h>
# include <sys/time.h>
# include <ncurses.h>

# define R 20
# define C 15
# define TIMER 400000
# define DECREASE 10000
# define BLOCKS_SIZE 7

/* struct */

typedef struct {
    char **array;
    int width, row, col;
} Struct;

typedef struct {
    int             final;
    bool            game_on;
    Struct          current;
    char            table[R][C];
    suseconds_t     timer;
    int             decrease;
    struct timeval  before_now, now;
} game_board;

/* init */
void            init(game_board *g);

/* finish */
void            finish(game_board *g);

/* utils/function */
bool            is_movable(Struct shape, game_board *g);
Struct          create_shape(Struct shape);
void            delete_shape(Struct shape);
void            rotate_shape(Struct shape);
void            print_shape(game_board *g);
Struct          generate_block(char **block_shape);
bool            is_update(game_board *g);

/* operation */
void            rotate(game_board *g);
void            move_down(game_board *g);
void            move_left(game_board *g);
void            move_right(game_board *g);
void            handle_blocks(game_board *g);

#endif