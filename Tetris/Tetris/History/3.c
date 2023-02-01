#include <MDR32Fx.h>
#include "lcd.h"
#include "font.h"

#define primitivSize	5

#define mapWidth		primitivSize*10
#define mapHeight		primitivSize*20
#define StartPoint_x	1
#define StartPoint_y	20

#define	NumHeight	5
#define NumWidth	3

#define objWidth		5	
#define objHeight		1	

#define ScreenHeight	128
#define ScreenWidth		64

#define yes	0xFF
#define	no 0x00


char screen[ScreenHeight][ScreenWidth];

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



int main(void)
{
	initPerefirial();
	InitLcd();
	SetPage(0, 0);
	SetAddr(0, 0);
	clear_lcd();
	StartScreen(screen);
	int cnt = 0;
	fillArray(screen, num_1, (1 + (cnt * 4)), 1);
	cnt++;
	fillArray(screen, num_2, (1 + (cnt * 4)), 1);
	cnt++;
	fillArray(screen, num_3, (1 + (cnt * 4)), 1);
	cnt++;
	fillArray(screen, num_4, (1 + (cnt * 4)), 1);
	cnt++;
	fillArray(screen, num_5, (1 + (cnt * 4)), 1);
	cnt++;
	fillArray(screen, num_6, (1 + (cnt * 4)), 1);
	cnt++;
	fillArray(screen, num_7, (1 + (cnt * 4)), 1);
	cnt++;
	fillArray(screen, num_8, (1 + (cnt * 4)), 1);
	cnt++;
	fillArray(screen, num_9, (1 + (cnt * 4)), 1);
	cnt++;
	fillArray(screen, num_0, (1 + (cnt * 4)), 1);
	cnt++;
	
	ScreenUpdate(screen);

	while(1);
}