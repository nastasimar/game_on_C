#include <MDR32Fx.h>
#include "lcd.h"

#define primitivSize	5

#define mapWidth		primitivSize*10
#define mapHeight		primitivSize*20

#define objWidth		5	
#define objHeight		1	

#define ScreenHeight	128
#define ScreenWidth		64

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

void ScreenUpdate(char ** array){
	char byte = 0;
	char x = ScreenWidth;
	char y = ScreenHeight;
	for(char crystal = 0; crystal < 2; crystal++){
		for(char page = 0; page < 8; page++){
			for(char height = 0; height < 64; height++){
				for(char bit = 0; bit < 8; bit++){
					byte |= (array[y - (crystal * 64) - bit][x - (page * 8) - bit] << bit);	
}

int main(void)
{
	initPerefirial();
	InitLcd();
	SetPage(0, 0);
	SetAddr(0, 0);

		uint8_t pic[] = {  0x1f, 
  0x1f, 
  0x1f, 
  0x1d, 
  0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xC0, 0xB8, 0x4A, 0xB5, 0xD5, 0x7A, 0xAD, 0xFA, 0xCF, 0xFD, 0xEE, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0xBE, 0xF5, 0xAB, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x6F, 0xFF, 0xBD, 0xF7, 0xEF, 0xBB, 0xEF, 0xDB,
0xBF, 0xEE, 0x7F, 0xDD, 0x7A, 0xF5, 0xE9, 0xD6, 0xEC, 0xA8, 0x50, 0xB0, 0x40, 0xC0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0xBA, 0xE5, 0xFA, 0xDF, 0xF5, 0x7A, 0xDF, 0xF6, 0x5B, 0xEF, 0xBD, 0xEF, 0x7F, 0xFF, 0xFF,
0xDF, 0xFF, 0xFF, 0x7F, 0x5F, 0x1F, 0x57, 0x07, 0x15, 0x07, 0x01, 0x07, 0x01, 0x06, 0x0B, 0x07,
0x0F, 0x17, 0x0F, 0x2F, 0x5F, 0x3F, 0xDF, 0xBF, 0xFD, 0xB7, 0xFD, 0xEE, 0xFF, 0xBD, 0xF6, 0xFB,
0xEF, 0xFE, 0xBB, 0xFF, 0xF5, 0xDF, 0xAE, 0xFF, 0xBB, 0xEF, 0xFB, 0xDE, 0x75, 0xDE, 0x75, 0xDB,
0xB4, 0xEC, 0x50, 0xA8, 0x50, 0xA0, 0x40, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0xBE, 0xFF, 0xFE, 0xFF, 0xDB, 0xFF, 0xFA, 0xFF, 0xFF, 0x7F, 0xD7, 0x3D, 0xEB, 0x5E, 0xE3,
0x3C, 0x17, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x02, 0x00, 0x0B, 0x05, 0x2A, 0x9F, 0x37, 0xAE, 0x7B,
0xDF, 0xFF, 0xFF, 0xFE, 0xFB, 0xDF, 0xFF, 0xFE, 0xFB, 0xFE, 0xFB, 0xEF, 0xFF, 0xBD, 0xFB, 0xFF,
0xFE, 0xDF, 0xF5, 0xFF, 0xF5, 0xEE, 0xFD, 0xD6, 0xFA, 0xF5, 0xF5, 0xEA, 0xE8, 0xD4, 0xD4, 0xA8,
0xD0, 0xA8, 0x50, 0xE0, 0x50, 0xA0, 0xA0, 0xE0, 0xA0, 0xA0, 0xC0, 0x60, 0x80, 0xC0, 0x00, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x02, 0xBF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD5, 0xAA, 0xFF, 0x85, 0xDA,
0xC5, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x08,
0xAC, 0x26, 0x52, 0x09, 0x14, 0x08, 0x3E, 0x94, 0x86, 0x64, 0x0C, 0x0C, 0x0A, 0x14, 0x03, 0x0C,
0x12, 0x43, 0x0F, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFB,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0x7F, 0xFF, 0x7F, 0xBF, 0xBE, 0x5F, 0x3E, 0x1F, 0x5E, 0x1F, 0x1D, 0x3E, 0x17, 0x1E,
0x16, 0x1B, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xFF, 0xAE, 0x5C, 0x1E,
0x36, 0x27, 0x46, 0x4B, 0x2F, 0x02, 0x25, 0x10, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00,
0xA2, 0x09, 0x54, 0x00, 0xAB, 0x2F, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDB, 0xEF, 0xFF, 0xFF, 0x7F, 0xDF, 0x5F,
0xBF, 0x5F, 0x3F, 0x57, 0x4F, 0x5F, 0x0E, 0x1F, 0x1F, 0x2D, 0x1E, 0x56, 0x1C, 0x2C, 0x54, 0x08,
0x28, 0x08, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x2F, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFD,
0xF0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x80, 0x00, 0x00, 0x00, 0x24, 0x00, 0x2A, 0x00, 0x00, 0x08, 0x01, 0x00, 0x00, 0x02, 0x40,
0x0A, 0x80, 0x55, 0x00, 0xAA, 0xA0, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x5F, 0x97, 0xF5, 0x6F, 0xBF, 0x57, 0x3F, 0xAF, 0x1D, 0x75,
0x16, 0xA8, 0x42, 0x14, 0x40, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x00, 0x20, 0x20,
0xA0, 0x32, 0xA0, 0x39, 0xA8, 0x98, 0x5C, 0xD8, 0x4C, 0xA0, 0x56, 0x00, 0x2A, 0x01, 0xA8, 0x02,
0xA8, 0xE4, 0x69, 0xB4, 0x2E, 0xAF, 0x5F, 0xBF, 0xBF, 0x7F, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xAF, 0x7B, 0x0F, 0xAF, 0x1A, 0xB5, 0x62, 0xC9, 0x84, 0x21, 0x04, 0x11, 0x00,
0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC,
0xFC, 0xF8, 0xF8, 0xF1, 0xE0, 0xF2, 0xE1, 0xE8, 0x62, 0x68, 0x31, 0xA8, 0xE8, 0xBA, 0xEC, 0xD6,
0x6F, 0xAB, 0xB5, 0xAA, 0xF5, 0xAA, 0x55, 0xAA, 0x6A, 0xDA, 0xA5, 0x5A, 0xED, 0xF6, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0x5C, 0x01, 0xAA, 0x04, 0x40, 0x12, 0x00, 0x04, 0x80, 0x11, 0x02, 0x01, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		
		//load_pic(pic);
	SetPage(0, 0);
	SetAddr(0, 0);
	clear_lcd();
	SetPage(0, 0);
	SetAddr(1, 0);
	//Send_Data(0xFF,0);
	ShowObj(1, 1, cube);
	while(1);
}