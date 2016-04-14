#include "stm32f10x.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "delay.h"
#include "movement.h"
#include "usart.h"

u8 exti_flag=0;

/*�ⲿ�ж�2��ʼ��*/
void Exti2_Init(void)
{
	 	EXTI_InitTypeDef EXTI_InitStructure;
	  KEY_Init();   	                                            /*����GPIO��ʼ��*/
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	        /*ʹ�ܸ��ù���ʱ��*/
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);  /*���ⲿ�ж�*/
	
	  EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     /*�½��ش���*/
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 
	
    Exti2_NVIC_Config();                                        /*�ⲿ�ж�2���ȼ�����*/
}

/*�ⲿ�ж�2���ȼ�����*/
void Exti2_NVIC_Config(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	    /*��ռ���ȼ�2*/ 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					  /*�����ȼ�2*/
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								/*ʹ���ⲿ�ж�ͨ��*/
  	NVIC_Init(&NVIC_InitStructure);	
}

/*�ⲿ�ж�2�жϷ������*/
void EXTI2_IRQHandler(void)
{
	delay_ms(10);
	
	if(KEY2==0)
	{
		LED0=!LED0;		
    rece_string[0]='Z';		
		rece_flag=1;  	
	}
	
	EXTI_ClearITPendingBit(EXTI_Line2);  /*���LINE2�ϵ��жϱ�־λ,�������Է��֣������д������if�������ִ�бȽ��ȶ�*/ 
}


