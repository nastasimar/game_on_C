#include <MDR32Fx.h>
#include <stdint.h>
#include "game.h"

#define RESET_LCD 10
#define CMD_E0 (int*)0x50100000
#define CMD_E1 (int*)0x50200000
#define Data_E0 (int*)0x58100000
#define Data_E1 (int*)0x58200000
#define LCD_ON 1
#define LCD_OFF 0
#define E0 4
#define E1 5
#define A0 11


void change_dir(int* x_dir, int* y_dir, int* x, int* y)
{
	if(*y > 61)
		*y_dir = (- *(y_dir));
	if(*y < 2)
		*y_dir = (- *(y_dir));
	
	if(*x < 4)
		*x_dir = (- *(x_dir));
	if(*x > 123)
		*x_dir = (- *(x_dir));
}

void move_ball(int* x, int* y, int* x_dir, int* y_dir)
{
	change_dir(x_dir, y_dir, x, y);
	*x += *x_dir;
	*y += *y_dir;
}

void clear_ball(int x, int y, uint8_t* pic)
{
	if(y < 8)
	{
		pic[x] &= ~(1 << y);
		pic[x+1] &= ~ (1 << y);
		pic[x] &= ~ (1 << (y-1));
		pic[x+1] &= ~ (1 << (y-1));
	}
	else if((y > 7) && (y < 16))
	{
		if(y == 8)
		{
			pic[x + 128*1] &= ~ (1 << (y - 8*1));
			pic[(x+1) + 128*1] &= ~ (1 << ((y) - 8*1));
			pic[x] &= ~ (1 << (y-1));
			pic[x+1] &= ~ (1 << (y-1));
		}
		else
		{	
			pic[x + 128*1] &= ~ (1 << (y - 8*1));
			pic[(x+1) + 128*1] &= ~ (1 << ((y) - 8*1));
			pic[(x) + 128*1] &= ~ (1 << ((y-1) - 8*1));
			pic[(x+1) + 128*1] &= ~ (1 << ((y-1) - 8*1));
		}
	}
	else if((y > 15) && (y < 24))
	{
		if(y == 16)
		{
			pic[x + 128*2] &= ~ (1 << (y-8*2));
			pic[(x+1) + 128*2] &= ~ (1 << (y-8*2));
			pic[x + 128*1] &= ~ (1 << ((y - 1) - 8*1));
			pic[(x+1) + 128*1] &= ~ (1 << ((y-1) - 8*1));
		}
		else 
		{
			pic[x + 128*2] &= ~ (1 << (y - 8*2));
			pic[(x+1) + 128*2] &= ~ (1 << ((y) - 8*2));
			pic[x + 128*2] &= ~ (1 << ((y-1) - 8*2));
			pic[(x+1) + 128*2] &= ~ (1 << ((y-1) - 8*2));
		}
	}
	else if((y > 23) && (y < 32))
	{
		if(y == 24)
		{
			pic[x + 128*3] &= ~ (1 << (y-8*3));
			pic[(x+1) + 128*3] &= ~ (1 << (y-8*3));
			pic[x + 128*2] &= ~ (1 << ((y - 1) - 8*2));
			pic[(x+1) + 128*2] &= ~ (1 << ((y-1) - 8*2));
		}
		else 
		{
			pic[x + 128*3] &= ~ (1 << (y - 8*3));
			pic[(x+1) + 128*3] &= ~ (1 << ((y) - 8*3));
			pic[x + 128*3] &= ~ (1 << ((y-1) - 8*3));
			pic[(x+1) + 128*3] &= ~ (1 << ((y-1) - 8*3));
		}
	}
	else if((y > 31) && (y < 40))
	{
		if(y == 32)
		{
			pic[x + 128*4] &= ~ (1 << (y-8*4));
			pic[(x+1) + 128*4] &= ~ (1 << (y-8*4));
			pic[x + 128*3] &= ~ (1 << ((y - 1) - 8*3));
			pic[(x+1) + 128*3] &= ~ (1 << ((y-1) - 8*3));
		}
		else 
		{
			pic[x + 128*4] &= ~ (1 << (y - 8*4));
			pic[(x+1) + 128*4] &= ~ (1 << ((y) - 8*4));
			pic[x + 128*4] &= ~ (1 << ((y-1) - 8*4));
			pic[(x+1) + 128*4] &= ~ (1 << ((y-1) - 8*4));
		}
	}
	else if((y > 39) && (y < 48))
	{
		if(y == 40)
		{
			pic[x + 128*5] &= ~ (1 << (y-8*5));
			pic[(x+1) + 128*5] &= ~ (1 << (y-8*5));
			pic[x + 128*4] &= ~ (1 << ((y - 1) - 8*4));
			pic[(x+1) + 128*4] &= ~ (1 << ((y-1) - 8*4));
		}
		else 
		{
			pic[x + 128*5] &= ~ (1 << (y - 8*5));
			pic[(x+1) + 128*5] &= ~ (1 << ((y) - 8*5));
			pic[x + 128*5] &= ~ (1 << ((y-1) - 8*5));
			pic[(x+1) + 128*5] &= ~ (1 << ((y-1) - 8*5));
		}
	}
	else if((y > 47) && (y < 56))
	{
		if(y == 48)
		{
			pic[x + 128*6] &= ~ (1 << (y-8*6));
			pic[(x+1) + 128*6] &= ~ (1 << (y-8*6));
			pic[x + 128*5] &= ~ (1 << ((y - 1) - 8*5));
			pic[(x+1) + 128*5] &= ~ (1 << ((y-1) - 8*5));
		}
		else 
		{
			pic[x + 128*6] &= ~ (1 << (y - 8*6));
			pic[(x+1) + 128*6] &= ~ (1 << ((y) - 8*6));
			pic[x + 128*6] &= ~ (1 << ((y-1) - 8*6));
			pic[(x+1) + 128*6] &= ~ (1 << ((y-1) - 8*6));
		}
	}
	else 
	{
		if(y == 56)
		{
			pic[x + 128*7] &= ~ (1 << (y-8*7));
			pic[(x+1) + 128*7] &= ~ (1 << (y-8*7));
			pic[x + 128*6] &= ~ (1 << ((y - 1) - 8*6));
			pic[(x+1) + 128*6] &= ~ (1 << ((y-1) - 8*6));
		}
		else 
		{
			pic[x + 128*7] &= ~ (1 << (y - 8*7));
			pic[(x+1) + 128*7] &= ~ (1 << ((y) - 8*7));
			pic[x + 128*7] &= ~ (1 << ((y-1) - 8*7));
			pic[(x+1) + 128*7] &= ~ (1 << ((y-1) - 8*7));
		}
	}
}


void shift1(uint8_t* pic, uint8_t* a, int n)
{
	int j = 0;
	for(int i = 0; i < n; i=i+2)
	{	pic[j] = a[i];
		pic[j+1] = a[i+1];
		j = j+128;
	}
}

void shift2(uint8_t* pic, uint8_t* a, int n)
{
	int j = 127;
	for(int i = 0; i < n; i=i+2)
	{	pic[j] = a[i];
		pic[j-1] = a[i+1];
		j = j+128;
	}
}
void load_pic(uint8_t* pic)
{
	int cnt = 0;
	for (int j=0; j<2;j++)
	{
		cnt = (j == 0) ? 0 : 64;
		for(int i =0; i<8;i++)
		{
			SetAddr(0, j);
			SetPage(i,j);
			for(int k=0;k<64;k++)
			{
				Send_Data(pic[cnt],j);
				cnt++;
			}
		cnt = cnt + 64;
		}
	}
	cnt = 0;
}	

void start_line(int startline)
{
	int	CMD;
	CMD = ((startline&0x3F) + 0xC0);
	WriteCMD(0, CMD);
}

//Subprograms
void InitLcd(void)
{
	int Status = 0;
	MDR_PORTE-> RXTX &= ~(1<<RESET_LCD);
	 for(int i=0;i<50;i++);
	MDR_PORTE-> RXTX |= (1<<RESET_LCD);
		for(int i=0;i<500;i++);
	Status = *((int*)0x50200000);
	while((ReadCMD(0))&((1<<7)|(1<<4)));
	while((ReadCMD(1))&((1<<7)|(1<<4)));
	LCDON(LCD_ON);	
}

int ReadCMD(int crystal)
{

	if(crystal)
	{
		MDR_PORTE->RXTX |= 1<<E1;
		MDR_PORTE->RXTX &= ~(1<<E0);
	}
	else
	{
		MDR_PORTE->RXTX |= 1<<E0;
		MDR_PORTE->RXTX &= ~(1<<E1);
	}

	return *CMD_E0;
}

void WriteCMD(int crystal, int CMD)
{

	if(crystal)
	{
		MDR_PORTE->RXTX |= 1<<E1;
		MDR_PORTE->RXTX &= ~(1<<E0);
	}
	else
	{
		MDR_PORTE->RXTX |= 1<<E0;
		MDR_PORTE->RXTX &= ~(1<<E1);
	}

  *CMD_E0 = CMD;
}

void WriteData(int crystal, int Data)
{
	if(crystal)
	{
		MDR_PORTE->RXTX |= 1<<E1;
		MDR_PORTE->RXTX &= ~(1<<E0);
	}
	else
	{
		MDR_PORTE->RXTX |= 1<<E0;
		MDR_PORTE->RXTX &= ~(1<<E1);
	}

  *Data_E0 = Data;
}

void clear_lcd(void)
{	for (int j=0; j<2;j++){
		for(int i =0; i<8;i++){
			SetPage(i,j);
			for(int k=0;k<64;k++){
				Send_Data(0x00,j);
			}
		}
	}
}

void LCDON(int Status)
{
	if(Status)
	{	
		WriteCMD(0, 0x3F);
		WriteCMD(1, 0x3F);
	}
	else
	{
		WriteCMD(0, 0x3E);
		WriteCMD(1, 0x3E);
	
	}
		
}

void SetPage(int Page, int crystal)
{
	int CMD;
	CMD =((Page&0x7) + 0xB8);
	
	if(crystal)
			WriteCMD(1, CMD);
	else
			WriteCMD(0, CMD);
}

void SetAddr(int Addr, int crystal)
{
	if(crystal)
		WriteCMD(1, 0x40 + (Addr&0x3F));
	else
		WriteCMD(0, 0x40 + (Addr&0x3F));
}

void Send_Data(int Data, int crystal)
{
		MDR_PORTE->RXTX |= (1<<A0);

	if(crystal)
	{
		MDR_PORTE->RXTX |= 1<<E1;
		MDR_PORTE->RXTX &= ~(1<<E0);
	}
	else
	{
		MDR_PORTE->RXTX |= 1<<E0;
		MDR_PORTE->RXTX &= ~(1<<E1);
	}

  *Data_E0 = Data;
}

void show_ball(int x, int y, uint8_t* pic)
{
	if(y < 8)
	{
		pic[x] |= (1 << y);
		pic[x+1] |= (1 << y);
		pic[x] |= (1 << (y-1));
		pic[x+1] |= (1 << (y-1));
	}
	else if((y > 7) && (y < 16))
	{
		if(y == 8)
		{
			pic[x + 128*1] |= (1 << (y - 8*1));
			pic[(x+1) + 128*1] |= (1 << ((y) - 8*1));
			pic[x] |= (1 << (y-1));
			pic[x+1] |= (1 << (y-1));
		}
		else
		{	
			pic[x + 128*1] |= (1 << (y - 8*1));
			pic[(x+1) + 128*1] |= (1 << ((y) - 8*1));
			pic[(x) + 128*1] |= (1 << ((y-1) - 8*1));
			pic[(x+1) + 128*1] |= (1 << ((y-1) - 8*1));
		}
	}
	else if((y > 15) && (y < 24))
	{
		if(y == 16)
		{
			pic[x + 128*2] |= (1 << (y-8*2));
			pic[(x+1) + 128*2] |= (1 << (y-8*2));
			pic[x + 128*1] |= (1 << ((y - 1) - 8*1));
			pic[(x+1) + 128*1] |= (1 << ((y-1) - 8*1));
		}
		else 
		{
			pic[x + 128*2] |= (1 << (y - 8*2));
			pic[(x+1) + 128*2] |= (1 << ((y) - 8*2));
			pic[x + 128*2] |= (1 << ((y-1) - 8*2));
			pic[(x+1) + 128*2] |= (1 << ((y-1) - 8*2));
		}
	}
	else if((y > 23) && (y < 32))
	{
		if(y == 24)
		{
			pic[x + 128*3] |= (1 << (y-8*3));
			pic[(x+1) + 128*3] |= (1 << (y-8*3));
			pic[x + 128*2] |= (1 << ((y - 1) - 8*2));
			pic[(x+1) + 128*2] |= (1 << ((y-1) - 8*2));
		}
		else 
		{
			pic[x + 128*3] |= (1 << (y - 8*3));
			pic[(x+1) + 128*3] |= (1 << ((y) - 8*3));
			pic[x + 128*3] |= (1 << ((y-1) - 8*3));
			pic[(x+1) + 128*3] |= (1 << ((y-1) - 8*3));
		}
	}
	else if((y > 31) && (y < 40))
	{
		if(y == 32)
		{
			pic[x + 128*4] |= (1 << (y-8*4));
			pic[(x+1) + 128*4] |= (1 << (y-8*4));
			pic[x + 128*3] |= (1 << ((y - 1) - 8*3));
			pic[(x+1) + 128*3] |= (1 << ((y-1) - 8*3));
		}
		else 
		{
			pic[x + 128*4] |= (1 << (y - 8*4));
			pic[(x+1) + 128*4] |= (1 << ((y) - 8*4));
			pic[x + 128*4] |= (1 << ((y-1) - 8*4));
			pic[(x+1) + 128*4] |= (1 << ((y-1) - 8*4));
		}
	}
	else if((y > 39) && (y < 48))
	{
		if(y == 40)
		{
			pic[x + 128*5] |= (1 << (y-8*5));
			pic[(x+1) + 128*5] |= (1 << (y-8*5));
			pic[x + 128*4] |= (1 << ((y - 1) - 8*4));
			pic[(x+1) + 128*4] |= (1 << ((y-1) - 8*4));
		}
		else 
		{
			pic[x + 128*5] |= (1 << (y - 8*5));
			pic[(x+1) + 128*5] |= (1 << ((y) - 8*5));
			pic[x + 128*5] |= (1 << ((y-1) - 8*5));
			pic[(x+1) + 128*5] |= (1 << ((y-1) - 8*5));
		}
	}
	else if((y > 47) && (y < 56))
	{
		if(y == 48)
		{
			pic[x + 128*6] |= (1 << (y-8*6));
			pic[(x+1) + 128*6] |= (1 << (y-8*6));
			pic[x + 128*5] |= (1 << ((y - 1) - 8*5));
			pic[(x+1) + 128*5] |= (1 << ((y-1) - 8*5));
		}
		else 
		{
			pic[x + 128*6] |= (1 << (y - 8*6));
			pic[(x+1) + 128*6] |= (1 << ((y) - 8*6));
			pic[x + 128*6] |= (1 << ((y-1) - 8*6));
			pic[(x+1) + 128*6] |= (1 << ((y-1) - 8*6));
		}
	}
	else 
	{
		if(y == 56)
		{
			pic[x + 128*7] |= (1 << (y-8*7));
			pic[(x+1) + 128*7] |= (1 << (y-8*7));
			pic[x + 128*6] |= (1 << ((y - 1) - 8*6));
			pic[(x+1) + 128*6] |= (1 << ((y-1) - 8*6));
		}
		else 
		{
			pic[x + 128*7] |= (1 << (y - 8*7));
			pic[(x+1) + 128*7] |= (1 << ((y) - 8*7));
			pic[x + 128*7] |= (1 << ((y-1) - 8*7));
			pic[(x+1) + 128*7] |= (1 << ((y-1) - 8*7));
		}
	}
}