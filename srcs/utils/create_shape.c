#include "tetris.h"

Struct create_shape(Struct shape) {
	Struct	new_shape;
	char	**copyshape;

	new_shape = shape;
	copyshape = shape.array;
	new_shape.array = (char **) malloc(new_shape.width * sizeof(char *));

    for (int i = 0; i < new_shape.width; i ++) {
		new_shape.array[i] = (char *) malloc(new_shape.width * sizeof(char));
		for (int j = 0; j < new_shape.width; j ++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
    }

    return new_shape;
}
