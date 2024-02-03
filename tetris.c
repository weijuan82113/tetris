#include "tetris.h"

char Table[R][C] = {0};
int final = 0;
char GameOn = T;
suseconds_t timer = 400000;
int decrease = 1000;
Struct current;
const Struct StructsArray[7]= {
	{(char *[]){(char []){0,1,1},(char []){1,1,0}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1,0},(char []){0,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,1,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){0,0,1},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,0,0},(char []){1,1,1}, (char []){0,0,0}}, 3},
	{(char *[]){(char []){1,1},(char []){1,1}}, 2},
	{(char *[]){(char []){0,0,0,0}, (char []){1,1,1,1}, (char []){0,0,0,0}, (char []){0,0,0,0}}, 4}
};
struct timeval before_now, now;

Struct FunctionCS(Struct shape) {
	Struct	new_shape;
	char	**copyshape;

	new_shape = shape;
	copyshape = shape.array;
	new_shape.array = (char **) malloc(new_shape.width * sizeof(char *));

    for(int i = 0; i < new_shape.width; i ++) {
		new_shape.array[i] = (char *) malloc(new_shape.width * sizeof(char));
		for(int j = 0; j < new_shape.width; j ++) {
			new_shape.array[i][j] = copyshape[i][j];
		}
    }

    return new_shape;
}

void FunctionDS(Struct shape) {
    for(int i = 0; i < shape.width; i ++) {
		free(shape.array[i]);
    }
    free(shape.array);
}

int FunctionCP(Struct shape) {
	for(int i = 0; i < shape.width; i ++) {
		for(int j = 0; j < shape.width; j ++) {
			if(shape.array[i][j] &&
					(shape.col + j < 0 || shape.col + j >= C || shape.row + i >= R ||
							Table[shape.row + i][shape.col + j]))
				return F;
		}
	}

	return T;
}

void FunctionRS(Struct shape) {
	Struct	temp;

	temp = FunctionCS(shape);

	for(int i = 0; i < shape.width; i ++) {
		for(int j = 0; j < shape.width; j ++) {
			int k = shape.width - 1 - j;
			shape.array[i][j] = temp.array[k][i];
		}
	}
	FunctionDS(temp);
}

void FunctionPT(void) {
	char buffer[R][C];

	for(int i = 0; i < current.width; i ++) {
		for(int j = 0; j < current.width; j ++) {
			if(current.array[i][j])
				buffer[current.row + i][current.col + j] = current.array[i][j];
		}
	}
	clear();
	for(int i = 0; i < C - 9; i ++)
		printw(" ");
	printw("42 Tetris\n");
	for(int i = 0; i < R; i ++) {
		for(int j = 0; j < C; j ++) {
			if (Table[i][j] + buffer[i][j])
				printw("# ");
			else
				printw(". ");
		}
		printw("\n");
	}
	printw("\nScore: %d\n", final);
}

int hasToUpdate(void) {
	return ((suseconds_t)(now.tv_sec * 1000000 + now.tv_usec) - (suseconds_t)(before_now.tv_sec * 1000000 + before_now.tv_usec)) > timer;
}

void set_timeout(int time) {
	timeout(time);
}

int main(void) {
    srand(time(0));
    final = 0;
    int c;
    initscr();
	gettimeofday(&before_now, NULL);
	set_timeout(1);
	Struct new_shape = FunctionCS(StructsArray[rand()%7]);
    new_shape.col = rand()%(C-new_shape.width+1);
    new_shape.row = 0;
    FunctionDS(current);
	current = new_shape;
	if(!FunctionCP(current)){
		GameOn = F;
	}
    FunctionPT();
	while(GameOn){
		if ((c = getch()) != ERR) {
			Struct temp = FunctionCS(current);
			switch(c){
				case 's':
					temp.row++;  //move down
					if(FunctionCP(temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									Table[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<R;n++){
							sum = 0;
							for(m=0;m< C;m++) {
								sum+=Table[n][m];
							}
							if(sum==C){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<C;l++)
										Table[k][l]=Table[k-1][l];
								for(l=0;l<C;l++)
									Table[k][l]=0;
								timer-=decrease--;
							}
						}
						final += 100*count;
						Struct new_shape = FunctionCS(StructsArray[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width+1);
						new_shape.row = 0;
						FunctionDS(current);
						current = new_shape;
						if(!FunctionCP(current)){
							GameOn = F;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCP(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCP(temp))
						current.col--;
					break;
				case 'w':
					FunctionRS(temp);
					if(FunctionCP(temp))
						FunctionRS(current);
					break;
			}
			FunctionDS(temp);
			FunctionPT();
		}
		gettimeofday(&now, NULL);
		if (hasToUpdate()) {
			Struct temp = FunctionCS(current);
			switch('s'){
				case 's':
					temp.row++;
					if(FunctionCP(temp))
						current.row++;
					else {
						int i, j;
						for(i = 0; i < current.width ;i++){
							for(j = 0; j < current.width ; j++){
								if(current.array[i][j])
									Table[current.row+i][current.col+j] = current.array[i][j];
							}
						}
						int n, m, sum, count=0;
						for(n=0;n<R;n++){
							sum = 0;
							for(m=0;m< C;m++) {
								sum+=Table[n][m];
							}
							if(sum==C){
								count++;
								int l, k;
								for(k = n;k >=1;k--)
									for(l=0;l<C;l++)
										Table[k][l]=Table[k-1][l];
								for(l=0;l<C;l++)
									Table[k][l]=0;
								timer-=decrease--;
							}
						}
						Struct new_shape = FunctionCS(StructsArray[rand()%7]);
						new_shape.col = rand()%(C-new_shape.width+1);
						new_shape.row = 0;
						FunctionDS(current);
						current = new_shape;
						if(!FunctionCP(current)){
							GameOn = F;
						}
					}
					break;
				case 'd':
					temp.col++;
					if(FunctionCP(temp))
						current.col++;
					break;
				case 'a':
					temp.col--;
					if(FunctionCP(temp))
						current.col--;
					break;
				case 'w':
					FunctionRS(temp);
					if(FunctionCP(temp))
						FunctionRS(current);
					break;
			}
			FunctionDS(temp);
			FunctionPT();
			gettimeofday(&before_now, NULL);
		}
	}
	FunctionDS(current);
	endwin();
	int i, j;
	for(i = 0; i < R ;i++){
		for(j = 0; j < C ; j++){
			printf("%c ", Table[i][j] ? '#': '.');
		}
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", final);
    return 0;
}
