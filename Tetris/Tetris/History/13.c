#include <MDR32Fx.h>
#include "lcd.h"
#include "font.h"
#include "primitives.h"
#include "figures.h"
#include "buttons.h"
#include <math.h>

#define primitivSize	5

#define button_UP			(!(MDR_PORTC->RXTX&(1<<13))) 	//12
#define button_DOWN		(!(MDR_PORTC->RXTX&(1<<13)))//11
#define button_RIGHT	(!(MDR_PORTC->RXTX&(1<<11)))
#define button_LEFT		(!(MDR_PORTC->RXTX&(1<<12)))
#define button_CENTER (!(MDR_PORTC->RXTX&(1<<10)))

#define mapWidth		primitivSize*10
#define mapHeight		primitivSize*20
#define StartPoint_x	6
#define StartPoint_y	21

#define turnPoint_x 1
#define turnPoint_y 1

#define nextFigure_x 1
#define nextFigure_y 1

#define	ScorePoint_x	60
#define	ScorePoint_y	1

#define	NumHeight	5
#define NumWidth	3

#define ScreenHeight	128
#define ScreenWidth		64

struct figure{
	char name; // J I O L Z T S
	int x, y;
	int width;
	int height;
	int rightpoint;
	int leftpoint;
	int bottompoint;
	int toppoint;
	char model[4][4];
};

struct number{
	char model[primitivSize*4][primitivSize*4];
	short num;
};

void ScreenUpdate(char array[ScreenHeight][ScreenWidth]);
void fillArray_primitiv(char array_m[ScreenHeight][ScreenWidth], char array_s[primitivSize][primitivSize], short xPos, short yPos);
void fillArray(char array_m[ScreenHeight][ScreenWidth], char array_s[NumHeight][NumWidth], short xPos, short yPos);
void StartScreen(char array[ScreenHeight][ScreenWidth]);
void showScore(char staticlevel[ScreenHeight][ScreenWidth], int score, int xPos, int yPos);
void drawGameField(char staticlevel[ScreenHeight][ScreenWidth], char gamingfield[20][10], char model[primitivSize][primitivSize]);
void drawNum(char staticlevel[ScreenHeight][ScreenWidth], char model[NumHeight][NumWidth], int xPos, int yPos);
void clearPrimitive(char staticlevel[ScreenHeight][ScreenWidth], char model[primitivSize][primitivSize], int xPos, int yPos);
void drawPrimitive(char staticlevel[ScreenHeight][ScreenWidth], char model[primitivSize][primitivSize], int xPos, int yPos);
char movDown(char staticlevel[20][10], struct figure *fig);
void movRight(char staticlevel[20][10], struct figure *fig);
void movLeft(char staticlevel[20][10], struct figure *fig);
void movRotate(char staticlevel[20][10], struct figure *fig);
char isCollision(char staticlevel[20][10], struct figure fig);
void initFigure(struct figure *fig, char model[4][4], int xPos, int yPos);
void placeFigure(struct figure fig, char array[20][10]);
void mixLayer(char staticlevel[20][10], char dynamiclevel[20][10], char mixedlevel[20][10]);
int maxRight(char model[4][4]);
int minLeft(char model[4][4]);
int minBottom(char model[4][4]);
int maxTop(char model[4][4]);
void rotateArray_CW(char arr[4][4], int width, int height, int startPoint_x, int startPoint_y);
void rotateArray_ACW(char arr[4][4], int width, int height, int startPoint_x, int startPoint_y);
void drawOneFig(struct figure fig, char staticlayer[ScreenHeight][ScreenWidth], char primivite[primitivSize][primitivSize]);
void generateFigure(struct figure *fig);

	char screen[ScreenHeight][ScreenWidth] = {0};
	char staticLayer[20][10] = {0};
	char dynamicLayer[20][10] = {0};
	char mixedLayer[20][10] = {0};
	
	struct figure Long;
	struct figure Short;
	struct figure TEST;
	
int main(void)
{
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			if(i < 1)
				staticLayer[i][j] = 1;
			else if((i < 5) && ((j < 3) | (j > 7)))
				staticLayer[i][j] = 1;
			else
				staticLayer[i][j] = 0;
	}
}
	initPerefirial();
	initButtons();
	InitLcd();
	SetPage(0, 0);
	SetAddr(0, 0);
	clear_lcd();
	StartScreen(screen);
	initFigure(&Long, fig_I, 5, 5);
	initFigure(&Short, fig_T, 4, 14);
	placeFigure(Long, dynamicLayer);
	placeFigure(Short, dynamicLayer);
	int n = (Short.toppoint);
	showScore(screen, n, ScorePoint_x, ScorePoint_y);
	generateFigure(&TEST);
	drawOneFig(TEST, screen, primitive);
	mixLayer(staticLayer, dynamicLayer, mixedLayer);
	drawGameField(screen, mixedLayer, primitive);
	ScreenUpdate(screen);
	while(1){
		if(button_LEFT){
			movLeft(staticLayer, &Short);
			placeFigure(Short, dynamicLayer);
			mixLayer(staticLayer, dynamicLayer, mixedLayer);
			drawGameField(screen, mixedLayer, primitive);
			//showScore(screen, 999999, ScorePoint_x, ScorePoint_y);
			ScreenUpdate(screen);
		while(button_LEFT);
		}
		if(button_RIGHT){
			movRight(staticLayer, &Short);
			placeFigure(Short, dynamicLayer);
			mixLayer(staticLayer, dynamicLayer, mixedLayer);
			drawGameField(screen, mixedLayer, primitive);
			//showScore(screen, 999999, ScorePoint_x, ScorePoint_y);
			ScreenUpdate(screen);
		while(button_RIGHT);
		}
		if(button_DOWN){
			movDown(staticLayer, &Short);
			placeFigure(Short, dynamicLayer);
			mixLayer(staticLayer, dynamicLayer, mixedLayer);
			drawGameField(screen, mixedLayer, primitive);
			//showScore(screen, 999999, ScorePoint_x, ScorePoint_y);
			ScreenUpdate(screen);
		while(button_DOWN);
		}
		if(button_CENTER){
			movRotate(staticLayer, &Short);
			placeFigure(Short, dynamicLayer);
			mixLayer(staticLayer, dynamicLayer, mixedLayer);
			//showScore(screen, maxRight(fig_I), ScorePoint_x, ScorePoint_y);
			drawGameField(screen, mixedLayer, primitive);
			
			ScreenUpdate(screen);
		while(button_CENTER);
		}
	}
}

void generateFigure(struct figure *fig){
	int n = 5; //kakoyto timer po osnovaniu 6
	switch (n) {
		case 0 : initFigure(fig, fig_I, nextFigure_x, nextFigure_y); break;
		case 1 : initFigure(fig, fig_J, nextFigure_x, nextFigure_y); break;
		case 2 : initFigure(fig, fig_L, nextFigure_x, nextFigure_y); break;
		case 3 : initFigure(fig, fig_O, nextFigure_x, nextFigure_y); break;
		case 4 : initFigure(fig, fig_S, nextFigure_x, nextFigure_y); break;
		case 5 : initFigure(fig, fig_T, nextFigure_x, nextFigure_y); break;
		case 6 : initFigure(fig, fig_Z, nextFigure_x, nextFigure_y); break;	
	}
}

void drawOneFig(struct figure fig, char staticlayer[ScreenHeight][ScreenWidth], char primivite[primitivSize][primitivSize]){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 4; j++){
			if(fig.model[i][j])
				drawPrimitive(staticlayer, primitive, nextFigure_x + j * primitivSize, nextFigure_y + i * primitivSize);
			else
				clearPrimitive(staticlayer, primitive, nextFigure_x + j * primitivSize, nextFigure_y + i * primitivSize);
		}	
	}
}

void initFigure(struct figure *fig, char model[4][4], int xPos, int yPos){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			(*fig).model[i][j] = model[3 - i][j];
		}
	}
	(*fig).rightpoint = maxRight((*fig).model);
	(*fig).leftpoint = minLeft((*fig).model);
	(*fig).bottompoint = minBottom((*fig).model);
	(*fig).toppoint = maxTop((*fig).model);
	(*fig).width = (*fig).rightpoint - (*fig).leftpoint + 1;
	(*fig).height = ((*fig).toppoint - (*fig).bottompoint + 1);
	(*fig).x = xPos;
	(*fig).y = yPos;
}

void placeFigure(struct figure fig, char array[20][10]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			array[i][j] = 0;
		}
	}
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(fig.model[i][j])
				array[i + fig.y][j + fig.x] = fig.model[i][j];
		}
	}
}

int maxRight(char model[4][4]){
	int max = 0;
	int buf = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(model[i][j]){
				buf = j;
			}
		}
		if(buf > max) max = buf;
	}
	return max;
}

int minLeft(char model[4][4]){
	int min = 3;
	int buf = 3;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(model[i][j]){
				buf = j;
				if(buf < min) min = buf;
			}
		}
	}
	return min;
}

int minBottom(char model[4][4]){
	int min = 3;
	int cnt = 0;
	int buf = 3;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(model[i][j]){
				buf = cnt;
			}
			
		}
		cnt++;
		if(buf < min) min = buf;
	}
	return min;
}

int maxTop(char model[4][4]){
	int max = 0;
	int cnt = 3;
	int buf = 0;
	int a = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if((model[3 - i][j] == 1) && (a == 0)){
				buf = cnt;
				a = 1;
			}
		}
		cnt--;
		if(buf > max) max = buf;
	}
	return max;
}

void mixLayer(char staticlevel[20][10], char dynamiclevel[20][10], char mixedlevel[20][10]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			mixedlevel[i][j] = dynamiclevel[i][j] + staticlevel[i][j];
		}
	}
}

char isCollision(char staticlevel[20][10], struct figure fig){
	if(((fig.y + fig.bottompoint) < 0) | ((fig.x + minLeft(fig.model)) < 0) | ((fig.x + maxRight(fig.model)) > 9))
				return 1;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(((fig.model)[i][j]) && (staticlevel[fig.y + i][fig.x + j])){
				return 1;
			}
		}
	}
	return 0;
}

void movRotate(char staticlevel[20][10], struct figure *fig){
	char temp;
	int yPos_L = (*fig).y + minBottom((*fig).model) + turnPoint_y;
	int yPos = (*fig).y;
	int xPos = (*fig).x;
	int xPos_L = (*fig).x + minLeft((*fig).model) + turnPoint_x;
	int xPos_R = (*fig).x + maxRight((*fig).model);
	if((((*fig).height) == 3) | ((*fig).width == 3))
		rotateArray_CW((*fig).model, (*fig).width, (*fig).height, (*fig).leftpoint, (3 - (*fig).height) );
	else if((((*fig).height) == 4) | ((*fig).width == 4))
		rotateArray_CW((*fig).model, (*fig).width, (*fig).height, 0, 0);
	(*fig).rightpoint = maxRight((*fig).model);
	(*fig).leftpoint = minLeft((*fig).model);
	(*fig).bottompoint = minBottom((*fig).model);
	if((isCollision(staticlevel, *fig)) | ((*fig).x + minLeft((*fig).model) < 0) | ((*fig).x + maxRight((*fig).model) > 9)){
		rotateArray_ACW((*fig).model, (*fig).width, (*fig).height, (*fig).leftpoint, (3 - (*fig).toppoint) );
		(*fig).x = xPos;
		(*fig).y = yPos;
		(*fig).rightpoint = maxRight((*fig).model);
		(*fig).leftpoint = minLeft((*fig).model);
		(*fig).bottompoint = minBottom((*fig).model);
		return;
	}
	else{
		(*fig).x = xPos_L - minLeft((*fig).model) - turnPoint_x;
		(*fig).y = yPos_L - minBottom((*fig).model) - turnPoint_y;
		(*fig).rightpoint = maxRight((*fig).model);
		(*fig).leftpoint = minLeft((*fig).model);
		(*fig).bottompoint = minBottom((*fig).model);		
	}	
}

void rotateArray_CW(char arr[4][4], int width, int height, int startPoint_x, int startPoint_y){
	int n = 0;
	if(width > height) n = width;
	else n = height;
	for (int i=(startPoint_y);i<n/2;i++) 
  { 
    for (int j=(startPoint_x);j<n-i-1;j++) 
    { 
        // Swapping elements after each iteration in Clockwise direction
            int temp=arr[i][j]; 
            arr[i][j]=arr[n-1-j][i]; 
            arr[n-1-j][i]=arr[n-1-i][n-1-j]; 
            arr[n-1-i][n-1-j]=arr[j][n-1-i]; 
            arr[j][n-1-i]=temp; 
    } 
  }
}

void rotateArray_ACW(char arr[4][4], int width, int height, int startPoint_x, int startPoint_y){
	int n = 0;
	if(width > height) n = width;
	else n = height;
	for (int i=(startPoint_y);i<n/2;i++) 
  { 
    for (int j=(startPoint_x);j<n-i-1;j++) 
    { 
			// Swapping elements after each iteration in Anticlockwise direction
				int temp=arr[i][j];
				arr[i][j]=arr[j][n-i-1];
				arr[j][n-i-1]=arr[n-i-1][n-j-1];
				arr[n-i-1][n-j-1]=arr[n-j-1][i];
				arr[n-j-1][i]=temp;
		}
	}
}

	
void movLeft(char staticlevel[20][10], struct figure *fig){
	(*fig).x--;
	if(isCollision(staticlevel, (*fig)))
		(*fig).x++;
	return;
}

void movRight(char staticlevel[20][10], struct figure *fig){
	(*fig).x++;
	if(isCollision(staticlevel, (*fig)))
		(*fig).x--;
	return;
}

char movDown(char staticlevel[20][10], struct figure *fig){ //if 0 - at the bottom
	(*fig).y--;
	if(isCollision(staticlevel, (*fig))){
		(*fig).y++;
		return 0 ;
	}
	return 1;
}

void drawPrimitive(char staticlevel[ScreenHeight][ScreenWidth], char model[primitivSize][primitivSize], int xPos, int yPos){
	int x = xPos;
	int y = yPos;
	for(int i = 0; i < primitivSize; i++){
		for(int j = 0; j < primitivSize; j++){
			staticlevel[y][x] = model[primitivSize - 1 - i][j];
			x++;
		}
		x = xPos;
		y++;
	}
}

void clearPrimitive(char staticlevel[ScreenHeight][ScreenWidth], char model[primitivSize][primitivSize], int xPos, int yPos){
	int x = xPos;
	int y = yPos;
	for(int i = 0; i < primitivSize; i++){
		for(int j = 0; j < primitivSize; j++){
			staticlevel[y][x] = 0;
			x++;
		}
		x = xPos;
		y++;
	}
}

void drawGameField(char staticlevel[ScreenHeight][ScreenWidth], char gamingfield[20][10], char model[primitivSize][primitivSize]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			if(gamingfield[i][j])
				drawPrimitive(staticlevel, primitive, (StartPoint_x + 1 + j * primitivSize), (StartPoint_y + 1 + i * primitivSize));
			else
				clearPrimitive(staticlevel, primitive, (StartPoint_x + 1 + j * primitivSize), (StartPoint_y + 1 + i * primitivSize));
		}
	}
}



void drawNum(char staticlevel[ScreenHeight][ScreenWidth], char model[NumHeight][NumWidth], int xPos, int yPos){
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 3; j++){
			staticlevel[yPos + i][xPos + j] = model[NumHeight - 1 - i][j];
		}
	}
}

void showScore(char staticlevel[ScreenHeight][ScreenWidth], int score, int xPos, int yPos){
	int razryad[6] = {0};
	razryad[0] = score % 10;
	razryad[1] = (score / 10) % 10;
	razryad[2] = (score / 100) % 10;
	razryad[3] = (score / 1000) % 10;
	razryad[4] = (score / 10000) % 10;
	razryad[5] = (score / 100000) % 10;
	for(long int i = 0; i < 6; i++){
		switch (razryad[i]) {
			case 0 : drawNum(staticlevel, num_0, xPos - 4 * i, yPos); break;
			case 1 : drawNum(staticlevel, num_1, xPos - 4 * i, yPos); break;
			case 2 : drawNum(staticlevel, num_2, xPos - 4 * i, yPos); break;
			case 3 : drawNum(staticlevel, num_3, xPos - 4 * i, yPos); break;
			case 4 : drawNum(staticlevel, num_4, xPos - 4 * i, yPos); break;
			case 5 : drawNum(staticlevel, num_5, xPos - 4 * i, yPos); break;
			case 6 : drawNum(staticlevel, num_6, xPos - 4 * i, yPos); break;
			case 7 : drawNum(staticlevel, num_7, xPos - 4 * i, yPos); break;
			case 8 : drawNum(staticlevel, num_8, xPos - 4 * i, yPos); break;
			case 9 : drawNum(staticlevel, num_9, xPos - 4 * i, yPos); break;
		}
	}
}



void ScreenUpdate(char array[ScreenHeight][ScreenWidth]){
	int byte = 0;
	int x = (ScreenWidth - 1);
	int y = (ScreenHeight - 1);
	for(int crystal = 0; crystal < 2; crystal++){
		for(int page = 0; page < 8; page++){
			SetAddr(0, crystal);
			SetPage(page, crystal);
			for(int height = 0; height < 64; height++){
				for(int bit = 0; bit < 8; bit++) {
					if(array[y - (crystal * 64) - height][x - (page * 8) - bit])
						byte |= (1 << bit);
					else
						byte &= ~(1 << bit);
				}
				Send_Data(byte, crystal);
			}
			byte = 0;
		}
	}				
}

void StartScreen(char array[ScreenHeight][ScreenWidth]){
	for(int y = 0; y < 128; y++){
		for(int x = 0; x < 64; x++){
			if(((x == StartPoint_x) | (x == (StartPoint_x + mapWidth + 1))) && ((y >= StartPoint_y) && (y <= (StartPoint_y + mapHeight + 1))))
				array[y][x] = 1;
			else if(((x >= StartPoint_x) && (x <= (StartPoint_x + mapWidth + 1))) && ((y == StartPoint_y) | (y == (StartPoint_y + mapHeight + 1))))
				array[y][x] = 1;
			else
				array[y][x] = 0;
		}
	}
}

void fillArray(char array_m[ScreenHeight][ScreenWidth], char array_s[NumHeight][NumWidth], short xPos, short yPos){
	int i = 0;
	int j = 0;
	for(int y = yPos; y < (yPos + NumHeight); y++){
		for(int x = xPos; x < (xPos + NumWidth); x++){
			array_m[y][x] = array_s[(NumHeight - 1 - j)][i];
			i++;
		}
		i = 0;
		j++;
	}
}

void fillArray_primitiv(char array_m[ScreenHeight][ScreenWidth], char array_s[primitivSize][primitivSize], short xPos, short yPos){
	int i = 0;
	int j = 0;
	for(int y = yPos; y < (yPos + primitivSize); y++){
		for(int x = xPos; x < (xPos + primitivSize); x++){
			array_m[y][x] = array_s[(primitivSize - 1 - j)][i];
			i++;
		}
		i = 0;
		j++;
	}
}
