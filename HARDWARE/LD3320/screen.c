#include "stm32f10x.h"
#include "oled_front.h"
#include "delay.h"
void screen_init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
	 I2C_InitTypeDef   I2C_InitStructure;
	
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE	);
   RCC_APB1PeriphClockCmd( RCC_APB1Periph_I2C2, ENABLE	);
	 
	 //PB10--SCL   PB11--SDL
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 I2C_DeInit(I2C2);
	 I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	 I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	 I2C_InitStructure.I2C_ClockSpeed = 400000;
	 I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	 I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	 I2C_InitStructure.I2C_OwnAddress1 = 0x30;
   I2C_Init(I2C2, &I2C_InitStructure);
	 I2C_Cmd(I2C2, ENABLE);
 }

void I2C_WriteByte(uint8_t addr,uint8_t data)
{
	while( I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY)); //??IIC??????
	
	I2C_GenerateSTART(I2C2, ENABLE);  //??IIC,??????
	while(!I2C_CheckEvent(I2C2,  I2C_EVENT_MASTER_MODE_SELECT)); //EV5???
	I2C_Send7bitAddress(I2C2, 0x78 ,  I2C_Direction_Transmitter);  //??OLED??
	while(!I2C_CheckEvent(I2C2,  I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)); //??EV6
	
	I2C_SendData(I2C2, addr); //???????
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
	
    I2C_SendData(I2C2, data); //????
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
 
    I2C_GenerateSTOP(I2C2, ENABLE);
}

void WriteCmd(unsigned char IIC_Command)  //???
{
	 I2C_WriteByte(0x00,IIC_Command);
}
 
void WriteDat(unsigned char IIC_Data)  //???
{
	 I2C_WriteByte(0x40,IIC_Data);
}


void OLED_Init(void) //OELD?????
{
  delay_ms(100);
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //ÁÁ¶Èµ÷½Ú 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
}

void SetPos(unsigned char x,unsigned char y)  //??????
{
	WriteCmd(0xb0+y);
	WriteCmd((x&0xf0)>>4|0x10); //???
	WriteCmd((x&0x0f)|0x01);    //???
}

void OLED_Fill(unsigned char Fill_Data)  //????
{
	unsigned char m,n;
	
	for(m=0;m<8;m++){
		WriteCmd(0xb0+m);
		WriteCmd(0x00);
		WriteCmd(0x10);
	
	  for(n=0;n<128;n++){
		WriteDat(Fill_Data);
		}
	}
}

void OLED_Clean(void)  //??
{
	OLED_Fill(0x00);
}

void OLED_ON(void)   //??OLED
{
	WriteCmd(0X8D);   //?????
	WriteCmd(0X14);   //?????
	WriteCmd(0XAF);   //OLED??
}
 
void OLED_OFF(void)  //??OLED
{
	WriteCmd(0X8D);   //?????
	WriteCmd(0X10);   //?????
	WriteCmd(0XAE);   //??OLED
}

//?????
void OLED_ShowStr(unsigned char x,unsigned char y,unsigned char ch[],unsigned TextSize)
{
    unsigned char c = 0,i = 0,j = 0;
	  switch(TextSize)
		{
			case 1:   //8*16??
			{
				while(ch[j] != '\0')
				{
				   c = ch[j] - 32;
					if(x>126)
					{
					    x= 0;
						  y++;					
					}
					SetPos(x,y);
					for(i=0;i<6;i++)
           WriteDat( F6x8[c][i] );
					x+=6 ;
					j++;				
				}
				
				}break;
			case 2:    //16*16??
			{
			   while(ch[j] !='\0')
				 {
						 c= ch[j] - 32;
					 if(x >120)
					 {
							 x = 0;
							 y++ ;
					 }
					 SetPos(x,y);
					 for(i = 0;i<8;i++)
					 WriteDat( F8X16[c*16+i] );
					 SetPos(x,y+1);
					 for(i = 0;i<8;i++)
					 WriteDat( F8X16[c*16+i+8] );
					 x+=8;
					 j++;
			 }	 
		}break;
			
	}
}	


//????
//x0:???;y0:???;x1:????;y1:????;BMP[]:????????
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1)
{
	unsigned int j=0;
	unsigned char x,y;
	
	if(y1%8 == 0)
		y = y1/8;
	else
		y = y1/8 +1;
	for(y=y0;y<y1;y++)
	{
				SetPos(x0,y);
       for(x=x0;x<x1;x++)
		{	
				WriteDat(img1[j++]);
		}		
	}
}