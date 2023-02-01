#include <MDR32Fx.h>
#include "lcd.h"
#include "font.h"
#include "primitives.h"
#include "figures.h"
#include "buttons.h"
#include "cpu.h"
#include "timers.h"


#define button_UP			(!(MDR_PORTC->RXTX&(1<<13))) 	//12
#define button_DOWN		(!(MDR_PORTC->RXTX&(1<<14)))//11
#define button_RIGHT	(!(MDR_PORTC->RXTX&(1<<11)))
#define button_LEFT		(!(MDR_PORTC->RXTX&(1<<12)))
#define button_CENTER (!(MDR_PORTC->RXTX&(1<<10)))

#define StartPoint_x	6
#define StartPoint_y	21


#define ScreenHeight	128
#define ScreenWidth		64

#define primitivSize	5

#define mapWidth		primitivSize*10
#define mapHeight		primitivSize*20

#define	NumHeight	5
#define NumWidth	3

#define	ScorePoint_x	60
#define	ScorePoint_y	1

#define nextFigure_x 1
#define nextFigure_y -4








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




int max(int a, int b);
int min(int a, int b);
void ScreenUpdate(char array[ScreenHeight][ScreenWidth], int theme);
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
void rotateArray_CW(char arr[4][4], int width, int height);
void rotateArray_ACW(char arr[4][4], int width, int height);
void drawOneFig(struct figure fig, char staticlayer[ScreenHeight][ScreenWidth], char primivite[primitivSize][primitivSize]);
void generateFigure(struct figure *fig);
int checkTetris(char gamefield[20][10], int* score, int line_num[]);
void deleteLines(char gamefield[20][10], int line_amount, int line_num[]);
void saveFigure(char staticlevel[20][10], char dynamiclevel[20][10]);
int checkTSpin(char gamefield[20][10], struct figure fig);
void initTimer_1(int arr, int psg);
void initTimer_2(int arr, int psg);
void initTimer_3(int arr, int psg);

	char screen[ScreenHeight][ScreenWidth] = {0};
	char staticLayer[20][10] = {0};
	char dynamicLayer[20][10] = {0};
	char mixedLayer[20][10] = {0};
	
	
	
	struct figure Long;
	struct figure Short;
	struct figure TEST;
	
	char gameIsOn;
	int theme_WB = 1;
	int score123 = 999999;
	
int main(void)
{
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			if((i == 3) || (i == 4) || (i == 6))
				staticLayer[i][j] = 1;
			else if(i > 6){
				if(((j < 3) | (j > 7)))
					staticLayer[i][j] = 1;
				else
				staticLayer[i][j] = 0;
			}
			else if(i < 9){
				if(((j < 5) | (j > 6)))
					staticLayer[i][j] = 1;
				else
				staticLayer[i][j] = 0;
			}
			else
				staticLayer[i][j] = 0;
		}
	}
	//cpu_freq();
	initTimer_1(133, 1000);
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
	int n = (Short.bottompoint);
	showScore(screen, n, ScorePoint_x, ScorePoint_y);
	generateFigure(&TEST);
	drawOneFig(TEST, screen, primitive);
	mixLayer(staticLayer, dynamicLayer, mixedLayer);
	drawGameField(screen, mixedLayer, primitive);
	ScreenUpdate(screen, theme_WB);
	int score;
	int num[4] = {0};
	int tetris = checkTetris(staticLayer, &score, &num[0]);
	deleteLines(staticLayer, tetris, num);
	while(1){
		if(button_LEFT){
			movLeft(staticLayer, &Short);
			placeFigure(Short, dynamicLayer);
			
		while(button_LEFT);
		}
		if(button_RIGHT){
			movRight(staticLayer, &Short);
			placeFigure(Short, dynamicLayer);
		while(button_RIGHT);
		}
		if(button_DOWN){
			//while(movDown(staticLayer, &Short));
			if(!movDown(staticLayer, &Short)){
				saveFigure(staticLayer, dynamicLayer);
				tetris = checkTetris(staticLayer, &score, num);
				deleteLines(staticLayer, tetris, num);
				initFigure(&Short, fig_T, 4, 14);
			}
			placeFigure(Short, dynamicLayer);
		while(button_DOWN);
		}
		if(button_CENTER){
			movRotate(staticLayer, &Short);
			placeFigure(Short, dynamicLayer);
		while(button_CENTER);
		}
	}
}

/***********************ENGINE***********************************/

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

void mixLayer(char staticlevel[20][10], char dynamiclevel[20][10], char mixedlevel[20][10]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			mixedlevel[i][j] = dynamiclevel[i][j] + staticlevel[i][j];
		}
	}
}

void saveFigure(char staticlevel[20][10], char dynamiclevel[20][10]){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			staticlevel[i][j] += dynamiclevel[i][j];
		}
	}
}

char isCollision(char staticlevel[20][10], struct figure fig){
	if(((fig.y + fig.bottompoint) < 0) || ((fig.x + fig.leftpoint) < 0) || ((fig.x + fig.rightpoint) > 9))
				return 1;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if((fig.model)[i][j]){ // && (staticlevel[fig.y + i][fig.x + j]
				if(staticlevel[fig.y + i][fig.x + j])
					return 1;
			}
		}
	}
	return 0;
}

void movRotate(char staticlevel[20][10], struct figure *fig){
	int yPos = (*fig).y;
	int xPos = (*fig).x;
	if((*fig).height == 2){
		if((*fig).width == 2)
			return;
		}
	rotateArray_CW((*fig).model, (*fig).width, (*fig).height);
	(*fig).rightpoint = maxRight((*fig).model);
	(*fig).leftpoint = minLeft((*fig).model);
	(*fig).bottompoint = minBottom((*fig).model);
	(*fig).toppoint = maxTop((*fig).model);
	if(isCollision(staticlevel, *fig)){
			rotateArray_ACW((*fig).model, (*fig).width, (*fig).height);
		(*fig).x = xPos;
		(*fig).y = yPos;
		(*fig).rightpoint = maxRight((*fig).model);
		(*fig).leftpoint = minLeft((*fig).model);
		(*fig).bottompoint = minBottom((*fig).model);
		(*fig).toppoint = maxTop((*fig).model);
	}
}

int max(int a, int b){
	if(a > b) return a;
	else return b;
}

int min(int a, int b){
	if(a < b) return a;
	else return b;
}

void rotateArray_ACW(char arr[4][4], int width, int height){
	int n = max(height, width);
	for (int i = 0; i < n / 2; i++) 
  	{ 
	    for (int j = i; j < n - i - 1; j++) 
	    { 
            int temp=arr[i][j]; 
            arr[i][j]=arr[n-1-j][i]; 
            arr[n-1-j][i]=arr[n-1-i][n-1-j]; 
            arr[n-1-i][n-1-j]=arr[j][n-1-i]; 
            arr[j][n-1-i]=temp; 
	    } 
  }
}

void rotateArray_CW(char arr[4][4], int width, int height){
	int n = max(height, width);
	for (int i = 0; i < n / 2; i++){ 
	    for (int j = i; j < n - i - 1;j++) 
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

void generateFigure(struct figure *fig){
	int n = 1; //kakoyto timer po osnovaniu 6
	switch (n) {
		case 0 : initFigure(fig, fig_I, nextFigure_x, nextFigure_y - minBottom(fig_I)); break;
		case 1 : initFigure(fig, fig_J, nextFigure_x, nextFigure_y); break;
		case 2 : initFigure(fig, fig_L, nextFigure_x, nextFigure_y); break;
		case 3 : initFigure(fig, fig_O, nextFigure_x, nextFigure_y); break;
		case 4 : initFigure(fig, fig_S, nextFigure_x, nextFigure_y); break;
		case 5 : initFigure(fig, fig_T, nextFigure_x, nextFigure_y); break;
		case 6 : initFigure(fig, fig_Z, nextFigure_x, nextFigure_y); break;	
	}
}

void deleteLines(char gamefield[20][10], int line_amount, int line_num[]){
	gameIsOn = 0;
	for(int k = 0; k < 5; k++){ //for animation
		for(int i = 0; i < line_amount; i++){
			gamefield[line_num[i]][4 - k] = 0;
			gamefield[line_num[i]][5 + k] = 0;
		}
		for(long int i = 0; i < 100000; i++);
	}
	for(int i = 0; i < line_amount; i++){
		for(int k = (line_num[line_amount - 1 - i] + 1); k < 20; k++){
			for(int j = 0; j < 10; j++){
				gamefield[k - 1][j] = gamefield[k][j];
			}
		}
	}
	for(int i = 16; i < 20; i++){
		for(int j = 0; j < 10; j++){
			gamefield[i][j] = 0; 
		}
	}
	gameIsOn = 1;
}

int checkTSpin(char gamefield[20][10], struct figure fig){
	int cnt = 0;
	for(int i = 0; i < max(fig.height,fig.width); i++){
		for(int j = 0; j < max(fig.height,fig.width); j++){
			if(fig.model[i][j]){
				if(fig.y + i - 1 >= 0){
					if(gamefield[fig.y + i - 1][fig.x + j])
						cnt ++;
				}
				else cnt++;
				if(fig.x + j - 1 >= 0){
					if(gamefield[fig.y + i][fig.x + j - 1])
						cnt ++;
				}
				if(gamefield[fig.y + i + 1][fig.x + j])
					cnt ++;
				else cnt++;
				if(fig.y + j + 1 <= 9){
					if(gamefield[fig.y + i][fig.x + j + 1])
						cnt ++;
				}
				else cnt++;
			}
			if(cnt == 3) return 1;
			cnt = 0;
		}
	}
	return 0;
}

int checkTetris(char gamefield[20][10], int* score, int line_num[]){
	int cnt = 0;
	int lines = 0;
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 10; j++){
			if(gamefield[i][j] == 1) cnt++;
		}
		if(cnt == 10){
			line_num[lines] = i;
			lines++;
		}
		cnt = 0;
	}
	return lines;
}



/***********************************LCD******************************/
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



void ScreenUpdate(char array[ScreenHeight][ScreenWidth], int theme){
	int byte = 0;
	int x = (ScreenWidth - 1);
	int y = (ScreenHeight - 1);
	for(int crystal = 0; crystal < 2; crystal++){
		for(int page = 0; page < 8; page++){
			SetAddr(0, crystal);
			SetPage(page, crystal);
			for(int height = 0; height < 64; height++){
				for(int bit = 0; bit < 8; bit++) {
					if(array[y - (crystal * 64) - height][x - (page * 8) - bit]){
						if(theme)
							byte |= (1 << bit);
						else
							byte &= ~(1 << bit);
					}
					else{
						if(theme)
							byte &= ~(1 << bit);
						else
							byte |= (1 << bit);
					}
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

void drawOneFig(struct figure fig, char staticlayer[ScreenHeight][ScreenWidth], char primivite[primitivSize][primitivSize]){
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 4; j++){
			if((nextFigure_x + j * primitivSize > 0) && (nextFigure_y + i * primitivSize > 0)){
				if(fig.model[i][j])
					drawPrimitive(staticlayer, primitive, nextFigure_x + j * primitivSize, nextFigure_y + i * primitivSize);
				else
					clearPrimitive(staticlayer, primitive, nextFigure_x + j * primitivSize, nextFigure_y + i * primitivSize);	
			}
		}
	}
}

/****************************************FIGURE*******************************************/

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
	int cnt = 3;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(model[3 - i][j]){
				return cnt;
			}
		}
		cnt--;
	}
	return cnt;
}

void initTimer_1(int arr, int psg){
	MDR_RST_CLK -> TIM_CLOCK |= (RST_CLK_TIM_CLOCK_TIM1_CLK_EN);	
	MDR_TIMER1 -> CNTRL |= (1 << TIMER_CNTRL_ARRB_EN_Pos)| TIMER_CNTRL_CNT_EN;	
	//MDR_TIMER1 -> CH2_CNTRL1|= (2 << TIMER_CH_CNTRL1_SELO_Pos);
	//MDR_TIMER1 -> CH2_CNTRL1|= (1 << TIMER_CH_CNTRL1_SELOE_Pos);	
	MDR_TIMER1 -> CH2_CNTRL |= (6 << TIMER_CH_CNTRL_OCCM_Pos);	
	MDR_TIMER1 -> ARR = arr;
	MDR_TIMER1 -> PSG = psg;
	MDR_TIMER1 -> IE |= (1 << 0);
}

void initTimer_2(int arr, int psg){
	MDR_RST_CLK -> TIM_CLOCK |= (RST_CLK_TIM_CLOCK_TIM2_CLK_EN);	
	MDR_TIMER2 -> CNTRL |= (1 << TIMER_CNTRL_ARRB_EN_Pos)| TIMER_CNTRL_CNT_EN;	
	//MDR_TIMER1 -> CH2_CNTRL1|= (2 << TIMER_CH_CNTRL1_SELO_Pos);
	//MDR_TIMER1 -> CH2_CNTRL1|= (1 << TIMER_CH_CNTRL1_SELOE_Pos);	
	MDR_TIMER2 -> CH2_CNTRL |= (6 << TIMER_CH_CNTRL_OCCM_Pos);	
	MDR_TIMER2 -> ARR = arr;
	MDR_TIMER2 -> PSG = psg;
	MDR_TIMER2 -> IE |= (1 << 0);
}

void initTimer_3(int arr, int psg){
	MDR_RST_CLK -> TIM_CLOCK |= (RST_CLK_TIM_CLOCK_TIM3_CLK_EN);	
	MDR_TIMER3 -> CNTRL |= (1 << TIMER_CNTRL_ARRB_EN_Pos)| TIMER_CNTRL_CNT_EN;	
	//MDR_TIMER1 -> CH2_CNTRL1|= (2 << TIMER_CH_CNTRL1_SELO_Pos);
	//MDR_TIMER1 -> CH2_CNTRL1|= (1 << TIMER_CH_CNTRL1_SELOE_Pos);	
	MDR_TIMER3 -> CH2_CNTRL |= (6 << TIMER_CH_CNTRL_OCCM_Pos);	
	MDR_TIMER3 -> ARR = arr;
	MDR_TIMER3 -> PSG = psg;
	MDR_TIMER3 -> IE |= (1 << 0);
}


void Timer1_IRQHandler (void)
	{
		mixLayer(staticLayer, dynamicLayer, mixedLayer);
		drawGameField(screen, mixedLayer, primitive);
		showScore(screen, score123, ScorePoint_x, ScorePoint_y);
		ScreenUpdate(screen, theme_WB);
		if(score123 == 0) score123 = 999999;
			score123--;
	}


