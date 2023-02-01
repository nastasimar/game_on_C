#include <MDR32Fx.h>
#include "lcd.h"
#include "font.h"
#include "primitives.h"
#include "figures.h"
#include "buttons.h"

#define primitivSize	5

#define button_UP			(!(MDR_PORTC->RXTX&(1<<12)))	//12
#define button_DOWN		(!(MDR_PORTC->RXTX&(1<<11)))	//11
#define button_RIGHT	(!(MDR_PORTC->RXTX&(1<<10)))
#define button_LEFT		(!(MDR_PORTC->RXTX&(1<<13)))

#define mapWidth		primitivSize*10
#define mapHeight		primitivSize*20
#define StartPoint_x	6
#define StartPoint_y	21

#define	ScorePoint_x	60
#define	ScorePoint_y	1

#define	NumHeight	5
#define NumWidth	3

#define ScreenHeight	128
#define ScreenWidth		64

struct figure{
	char model[4][4];
	char name; // J I O L Z T S
	int x, y;
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


	char screen[ScreenHeight][ScreenWidth] = {0};
	char staticLayer[20][10] = {0};
	char dynamicLayer[20][10] = {0};
	char mixedLayer[20][10] = {0};
	
	struct figure Long;
	struct figure Short;
	
	
int main(void)
{
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
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
	initFigure(&Short, fig_S, 2, 1);
	placeFigure(Long, dynamicLayer);
	placeFigure(Short, dynamicLayer);
	mixLayer(staticLayer, dynamicLayer, mixedLayer);
	drawGameField(screen, mixedLayer, primitive);
	showScore(screen, 999999, ScorePoint_x, ScorePoint_y);
	ScreenUpdate(screen);
	//movDown(staticLayer, &Short);
	movRight(staticLayer, &Short);
	placeFigure(Short, dynamicLayer);
	mixLayer(staticLayer, dynamicLayer, mixedLayer);
	drawGameField(screen, mixedLayer, primitive);
	//showScore(screen, 999999, ScorePoint_x, ScorePoint_y);
	ScreenUpdate(screen);
while(1);
	for(long i = 0; i < 100000; i++);
	

			movLeft(staticLayer, &Long);
			placeFigure(Long, dynamicLayer);
			mixLayer(staticLayer, dynamicLayer, mixedLayer);
			drawGameField(screen, mixedLayer, primitive);
			ScreenUpdate(screen);
	while(1);
}

void initFigure(struct figure *fig, char model[4][4], int xPos, int yPos){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			(*fig).model[i][j] = model[3 - i][j];
		}
	}
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
			array[i + fig.y][j + fig.x] = fig.model[i][j];
		}
	}
}

void mixLayer(char staticlevel[20][10], char dynamiclevel[20][10], char mixedlevel[20][10]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			mixedlevel[i][j] = dynamiclevel[i][j] + staticlevel[i][j];
		}
	}
}

char isCollision(char staticlevel[20][10], struct figure fig){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if((fig.model)[i][j]){
				if(staticlevel[StartPoint_y + fig.y + i][StartPoint_x + fig.x + j])
					return 0;
				else if((fig.y < 0) | (fig.x < 0) | (fig.x > 9))
					return 0;
			}
			
		}
	}
}

void movRotate(char staticlevel[20][10], struct figure *fig){
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
		movRotate(staticlevel, fig);
		movRotate(staticlevel, fig);
		movRotate(staticlevel, fig);
	}
}


	
void movLeft(char staticlevel[20][10], struct figure *fig){
	(*fig).x--;
	if(isCollision(staticlevel, (*fig)))
		movRight(staticlevel, fig);
	return;
}

void movRight(char staticlevel[20][10], struct figure *fig){
	(*fig).x++;
	if(isCollision(staticlevel, (*fig)))
		movLeft(staticlevel, (fig));
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
	for(int i = 0; i < primitivSize; i++){
		for(int j = 0; j < primitivSize; j++){
			staticlevel[StartPoint_y + yPos * primitivSize + i + 1][StartPoint_x + xPos * primitivSize + j + 1] = model[primitivSize - 1 - i][j];
		}
	}
}

void clearPrimitive(char staticlevel[ScreenHeight][ScreenWidth], char model[primitivSize][primitivSize], int xPos, int yPos){
	for(int i = 0; i < primitivSize; i++){
		for(int j = 0; j < primitivSize; j++){
			staticlevel[StartPoint_y + yPos * primitivSize + i + 1][StartPoint_x + xPos * primitivSize + j + 1] = 0;
		}
	}
}

void drawGameField(char staticlevel[ScreenHeight][ScreenWidth], char gamingfield[20][10], char model[primitivSize][primitivSize]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			if(gamingfield[i][j])
				drawPrimitive(staticlevel, primitive, j, i);
			else
				clearPrimitive(staticlevel, primitive, j, i);
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
