#include "tetris.h"

void rotate_shape(Struct shape) {
	Struct temp;

	temp = create_shape(shape);

	for (int i = 0; i < shape.width; i ++) {
		for (int j = 0; j < shape.width; j ++) {
			int k = shape.width - 1 - j;
			shape.array[i][j] = temp.array[k][i];
		}
	}
	delete_shape(temp);
}