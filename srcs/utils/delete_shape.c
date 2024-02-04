#include "tetris.h"

void delete_shape(Struct shape) {
    for (int i = 0; i < shape.width; i ++) {
		free(shape.array[i]);
    }
    free(shape.array);
}