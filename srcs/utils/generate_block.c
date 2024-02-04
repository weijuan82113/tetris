#include "tetris.h"

Struct generate_block(char **block_shape) {
	Struct origin_block;

	origin_block.width = 0;
	origin_block.row = 0;
	origin_block.array = block_shape;

	while (block_shape[origin_block.width] != NULL)
		origin_block.width ++;
	origin_block.col = rand() % (C - origin_block.width + 1);

	return create_shape(origin_block);
}
