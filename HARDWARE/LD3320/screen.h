#ifndef FOOT_H
#define FOOT_H

void screen_init(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char IIC_Command);
void WriteDat(unsigned char IIC_Data);
void OLED_Init(void);
void SetPos(unsigned char x,unsigned char y);
void OLED_Fill(unsigned char Fill_Data);
void OLED_Clean(void);
void OLED_ON(void) ;
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x,unsigned char y,unsigned char ch[],unsigned TextSize);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1);

#endif