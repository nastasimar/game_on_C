#include <MDR32Fx.h>
#include "lcd.h"

#define primitivSize	5

#define mapWidth		primitivSize*10
#define mapHeight		primitivSize*20
#define StartPoint_x	1
#define StartPoint_y	1


#define objWidth		5	
#define objHeight		1	

#define ScreenHeight	128
#define ScreenWidth		64

#define yes	0xFF
#define	no 0x00

uint8_t StaticFigures[mapHeight][mapWidth];
uint8_t MovingFigures[mapHeight][mapWidth];

int testObj[objWidth][objHeight] = {
	0x1f, 
  0x1f, 
  0x1f, 
  0x1d, 
  0x1f};

	
	
typedef struct{
	uint8_t x, y;
} Object;

Object cube;



void SetObjectPos(Object *obj, uint8_t x, uint8_t y){
	(*obj).x = x;
	(*obj).y = y;
}

void ShowObj(uint8_t xPos, uint8_t yPos, Object obj){
	uint8_t page;
	uint8_t crystal = 0;
	uint8_t byte = 0;
	uint8_t bitPos = 0;
	int y = (y > 63) ? (127 - y) : (63 - y);
	int x = xPos;
//	for(int y = yPos; y < (yPos + objHeight); y++){
//		for(int x = xPos; x < (xPos + (objWidth * 8)); x+=8){
			if(yPos < 63) crystal = 1;
			page = (7 - (x / 8));
			SetAddr(y, crystal);
			SetPage(page, crystal);	
			
			SetAddr(y, crystal);
			byte |= (testObj[y][x] >> (x % 8));
			Send_Data(byte, crystal);
			page++;
			SetPage(page, crystal);	
			byte = (testObj[y - yPos][x - xPos] << (7 - (x % 8)));
			x+=8;
			y++;
			SetAddr(y, crystal);
			byte |= (testObj[y][x] >> (x % 8));
			Send_Data(byte, crystal);
	
			SetAddr(y, crystal);
			byte |= (testObj[y][x] >> (x % 8));
			Send_Data(byte, crystal);
			page++;
						SetPage(page, crystal);
			byte = (testObj[y - yPos][x - xPos] << (7 - (x % 8)));
			x+=8;
			y++;
			SetAddr(y, crystal);
			byte |= (testObj[y][x] >> (x % 8));
			Send_Data(byte, crystal);
			
			SetAddr(y, crystal);
			byte |= (testObj[y][x] >> (x % 8));
			Send_Data(byte, crystal);
			page++;
						SetPage(page, crystal);
			byte = (testObj[y - yPos][x - xPos] << (7 - (x % 8)));
			x+=8;
			y++;
			SetAddr(y, crystal);
			byte |= (testObj[y][x] >> (x % 8));
			Send_Data(byte, crystal);
			

	
}

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
			if(((x == StartPoint_x) | (x == (StartPoint_x + mapWidth))) && ((y >= StartPoint_y) | (y <= (StartPoint_y + mapHeight))))
				array[y][x] = 1;
			else
				array[y][x] = 0;
}

int main(void)
{
	initPerefirial();
	InitLcd();
	SetPage(0, 0);
	SetAddr(0, 0);
	clear_lcd();
	for(int y = 0; y < 128; y++){
		for(int x = 0; x < 64; x++){
			if((x > 15) && (x <= 54) && (y < 120) && (y > 20))
				screen[y][x] = 1;
			else
				screen[y][x] = 0;
		}
	}
	ScreenUpdate(screen);

	while(1);
}