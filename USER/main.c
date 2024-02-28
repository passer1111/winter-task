/*
1.��Ŀ���ƣ������콢��LD3320����ʶ��ģ��STM32F103C8T6���Գ���
2.��ʾģ�飺�������
3.����APP����
4.������λ������
5.��Ŀ��ɣ�LD3320����ʶ��ģ��
6.��Ŀ���ܣ�ʶ�����úõĿ����ͨ�����ڷ���ʶ����Ϣ��
7.��Ҫԭ������ο�LD3320�����ֲ�
8.�����ַ��https://lssz.tmall.com ���Ա��������������콢�ꡱ
10.��Ȩ�����������콢�����г��������������Ȩ�����뱾���Ʒ���׳��ۣ��벻Ҫ����������׷���䷨�����Σ�
���߶���:                                                                        
	VCC��5V�ν���һ                                                     
	VCC��3.3V���磬5V��5V����
	GND--GND
	SCK--PB7
	MI--PB6
	MO--PB5
	CS--PB4
	RST--PB3
	IRQ--PB8
	WR---GND
*/
#include "stm32f10x.h"
#include "delay.h"
#include "Reg_RW.h"
#include "LDChip.h"
#include "usart.h"
#include "screen.h"
#include "foot.h"

void User_Modification(u8 dat);

u8 nAsrStatus=0;
u8 nAsrRes=0;
u8 flag=0;

uint8_t a;

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	LD3320_Init();
	EXTIX_Init();
	LD_Reset();
	
	pwm_init();
	
	screen_init();
	OLED_Init();
	OLED_ON();
	uart_init(9600);
	nAsrStatus = LD_ASR_NONE;		//	��ʼ״̬��û������ASR
	SCS=0;
	printf("���г���\r\n");
  OLED_ShowStr(20,3,"hello world",2);
	
	while(1)
	{
		switch(nAsrStatus) 
		{
			case LD_ASR_RUNING:
			case LD_ASR_ERROR:
          			
					 break;
			case LD_ASR_NONE:
			{
				nAsrStatus=LD_ASR_RUNING;
				if (RunASR()==0)	/*	����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����*/
				{
					nAsrStatus = LD_ASR_ERROR;
				}
				break;
			}

			case LD_ASR_FOUNDOK: /*	һ��ASRʶ�����̽�����ȥȡASRʶ����*/
			{
				nAsrRes = LD_GetResult();		/*��ȡ���*/												
				User_Modification(nAsrRes);
				nAsrStatus = LD_ASR_NONE;
				break;
			}
			case LD_ASR_FOUNDZERO:
			default:
			{
				nAsrStatus = LD_ASR_NONE;
				break;
			}
		} 
	}
}

/***********************************************************
* ��    �ƣ��û�ִ�к��� 
* ��    �ܣ�ʶ��ɹ���ִ�ж������ڴ˽����޸� 
* ��ڲ����� �� 
* ���ڲ�������
* ˵    ���� 					 
**********************************************************/
void User_Modification(u8 dat)
{
	if(dat ==0)
	{
		flag=1;
		printf("�յ�\r\n");
	}
	else if(flag)
	{
		flag=0;
		switch(nAsrRes)		   /*�Խ��ִ����ز���,�ͻ��޸�*/
		{
			case CODE_DMCS:			/*���������ԡ�*/
				  a=1;
					printf("\"�������\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			case CODE_CSWB:			/*���������ϡ�*/
					printf("\"�������\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			
			case CODE_1KL1:	 /*���������*/
				  a=2;
					printf("\"����\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			case CODE_1KL2:		/*����Ϻ���*/
		
					printf("\"�Ϻ�\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			case CODE_1KL3:	 /*������ơ�*/
					printf("\"����\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			case CODE_1KL4:		/*����صơ�*/				
					printf("\"�ص�\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			
			case CODE_2KL1:	 /*���....��*/
					printf("\"����\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			case CODE_2KL2:	 /*���....��*/
					printf("\"����\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			case CODE_2KL3:	 /*���....��*/
					printf("\"����ת\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			case CODE_2KL4:	 /*���....��*/
					printf("\"����ת\"ʶ��ɹ�\r\n"); /*text.....*/
															break;
						
			case CODE_3KL1:	 /*���....��*/
					printf("\"�򿪿յ�\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			case CODE_3KL2:	 /*���....��*/
					printf("\"�رտյ�\"ʶ��ɹ�\r\n"); /*text.....*/
												break;
			case CODE_5KL1:	 /*���....��*/
					printf("\"����\"ʶ��ɹ�"); /*text.....*/
												break;
//		case CODE_3KL4:	 /*���....��*/
//				printf("\"�������\"ʶ��ɹ�"); /*text.....*/
//											break;
//					
//					case CODE_4KL1:	 /*���....��*/
//							printf("O"); /*text.....*/
//														break;
//					case CODE_4KL2:	 /*���....��*/
//							printf("P"); /*text.....*/
//														break;
//					case CODE_4KL3:	 /*���....��*/
//							printf("Q"); /*text.....*/
//														break;
//					case CODE_4KL4:	 /*���....��*/
//							printf("R"); /*text.....*/
//														break;
			
			default:break;
		}
	}
	else 	
	{
		printf("��˵��һ������\r\n"); /*text.....*/	
	}
	
}
