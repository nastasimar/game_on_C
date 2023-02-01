char fig_J[primitivSize*4][primitivSize*4] = {
	0, 0, 0, 0,
	0, 0, 1, 0,
	0, 0, 1, 0,
	0, 1, 1, 0
}
char fig_I[primitivSize*4][primitivSize*4] = {
	0, 0, 1, 0,
	0, 0, 1, 0,
	0, 0, 1, 0,
	0, 0, 1, 0
}
char fig_O[primitivSize*4][primitivSize*4] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	0, 1, 1, 0
}
char fig_L[primitivSize*4][primitivSize*4] = {
	0, 0, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 1, 0
}
char fig_Z[primitivSize*4][primitivSize*4] = {
	0, 0, 1, 0,
	0, 0, 1, 0,
	1, 1, 0, 0,
	0, 1, 1, 0
}
char fig_T[primitivSize*4][primitivSize*4] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 0, 0,
	1, 1, 1, 0
}
char fig_S[primitivSize*4][primitivSize*4] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 1, 1, 0,
	1, 1, 0, 0
}


struct figure{
	char model[primitivSize*4][primitivSize*4];
	char name; // J I O L Z T S
	int x, y;
}

struct number{
	char model[primitivSize*4][primitivSize*4];
	short num;
}

bool isCollision(char** staticlevel, figure fig){
	for(int i = 0; i < primitivSize; i++){
		for(int j = 0; j < primitivSize; j++){
			if((fig.model)[i][j]){
				if(staticlevel[StartPoint_y + fig.y + i][StartPoint_x + fig.x + j])
					return 0;
			}
		}
	}
}

void movRotate(char** staticlevel, figure *fig){
	char temp;
	for(int i = 0; i < primitivSize; i++){
		for(int j = 0; j < primitivSize; j++){
			temp = (*fig).model[i][j];
			(*fig).model[i][j] = (*fig).model[j][i];
		}
	}
	for(int i = 0; i < primitivSize; i++){
		for(int j = 0; j < primitivSize; j++){
			temp = (*fig).model[i][j];
			(*fig).model[i][j] = (*fig).model[i][primitivSize - j - 1];
			(*fig).model[i][primitivSize - j - 1] = temp;
		}
	}
	if(isCollision(staticlevel, *fig)){
		rotate(&fig);
		rotate(&fig);
		rotate(&fig);
	}
}

void movLeft(char** staticlevel, figure *fig){
	(*fig).x -= primitivSize;
	if(isCollision(staticlevel, (*fig))
		movRight(staticlevel, (*fig);
	return;
}

void movRight(char** staticlevel, figure *fig){
	(*fig).x += primitivSize;
	if(isCollision(staticlevel, (*fig))
		movLeft(staticlevel, (*fig);
	return;
}

bool movDown(char** staticlevel, figure *fig){ //if 0 - at the bottom
	(*fig).y -= primitivSize;
	if(isCollision(staticlevel, (*fig)){
		(*fig).y += primitivSize;
		return 0 ;
	}
	return 1;
}

void drawGameField(char** staticlevel, char** gamingfield, char** model){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			if(staticlevel[i][j])
				drawPrimitiv(staticlevel, primitive, j, i);
			else
				clearPrimitiv(staticlevel, primitive, j, i);
		}
	}
}

void drawPrimitiv(char** staticlevel, char** model, int xPos, int yPos){
	for(int i = 0; i < primitivSize; i++){
		for(int j = 0; j < primitivSize; j++){
			staticlevel[StartPoint_y + yPos * primitivSize + i][StartPoint_x + xPos * primitivSize + j] = model[primitivSize - 1 - i][j];
		}
	}
}

void clearPrimitiv(char** staticlevel, char** model, int xPos, int yPos){
	for(int i = 0; i < primitivSize; i++){
		for(int j = 0; j < primitivSize; j++){
			staticlevel[StartPoint_y + yPos * primitivSize + i][StartPoint_x + xPos * primitivSize + j] = 0;
		}
	}
}

void showScore(char** staticlevel, int score, int xPos, int yPos){
	for(long int i = 1; i < 1000001; i *= 10){
		switch (score/i) {
			case 0 : drawNum(staticlevel, fig_0, scorePos_x + 4 * (i - 1), scorePos_y); break;
			case 1 : drawNum(staticlevel, fig_1, scorePos_x + 4 * (i - 1), scorePos_y); break;
			case 2 : drawNum(staticlevel, fig_2, scorePos_x + 4 * (i - 1), scorePos_y); break;
			case 3 : drawNum(staticlevel, fig_3, scorePos_x + 4 * (i - 1), scorePos_y); break;
			case 4 : drawNum(staticlevel, fig_4, scorePos_x + 4 * (i - 1), scorePos_y); break;
			case 5 : drawNum(staticlevel, fig_5, scorePos_x + 4 * (i - 1), scorePos_y); break;
			case 6 : drawNum(staticlevel, fig_6, scorePos_x + 4 * (i - 1), scorePos_y); break;
			case 7 : drawNum(staticlevel, fig_7, scorePos_x + 4 * (i - 1), scorePos_y); break;
			case 8 : drawNum(staticlevel, fig_8, scorePos_x + 4 * (i - 1), scorePos_y); break;
			case 9 : drawNum(staticlevel, fig_9, scorePos_x + 4 * (i - 1), scorePos_y); break;
		}
	}
}

	switch (num.num) {
		case 0 : break;
		case 1 : break;
		case 2 : break;
		case 3 : break;
		case 4 : break;
		case 5 : break;
		case 6 : break;
		case 7 : break;
		case 8 : break;
		case 9 : break;

void drawNum(char** staticlevel, char** model, int xPos, int yPos){
	for(int i = 0; i < SIZEOFFONT; i++){
		for(int j = 0; j < SIZEOFFONT; j++){
			staticlevel[yPos][xPos] = model[SIZEOFFONT - 1 - i][j];
		}
	}
}