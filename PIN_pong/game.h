#include <MDR32Fx.h>
#include <stdint.h>

void clear_ball(int x, int y, uint8_t* pic);
void change_dir(int* x_dir, int* y_dir, int* x, int* y);
void move_ball(int* x, int* y, int* x_dir, int* y_dir);
void show_ball(int x, int y, uint8_t* pic);
void shift1(uint8_t* pic, uint8_t* a, int n);
void shift2(uint8_t* pic, uint8_t* a, int n);
void LCDON(int Status);
void InitLcd(void);
void SetPage(int Page, int crystal);
void SetAddr(int Addr, int crystal);
void Send_Data(int Data, int crystal);
void clear_lcd(void);
void load_pic(uint8_t* pic);
void WriteCMD(int crystal, int CMD);