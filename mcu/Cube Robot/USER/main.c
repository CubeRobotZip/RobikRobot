/*����������ħ����������λ�����Ƴ���
 *����оƬ��STM32F103ZET6,flash:512kb, ram:64kb
 *��    ע��MG995�����������ķ���Ϊ��ʱ��
 *���ٶ�ֵΪ500ʱ������ʾ��Ϊ#B'R2U2B2DU2F2UB2R2U'L2U'L'U'FRB2RD'!������ʱ��Ϊ2��14�룬���ٶ�ֵΪ300ʱ������ʱ��Ϊ1��20��         
 */
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "motor.h"
#include "movement.h"
#include "instruction.h"
#include "exti.h"
	
 int main(void)
 {	
		delay_init();
		NVIC_Configuration();        /*����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�*/
		LED_Init();
		MotorPin_Init();             /*�����ʼ���ź�������*/		     
		USART1_Config();
		Init_TotalArray();           /*����ִ������*/
	  Exti2_Init();
    TIM3_Int_Init(10,71);	 
		TIM_Cmd(TIM3, DISABLE);     /*���յ�ָ��֮���ٴ�TIM3*/		
	  while(!rece_flag);
	 
		while(1)
		{                                        /*���棺�ⲿ�ж�ABCDEF��˳��Ҫ�ߵ�*/
						
				if(rece_flag==1)
					{
						
						  TIM_Cmd(TIM3, DISABLE);         /*�ȹر�TIM3������ȫ�ֱ������޸�*/	
						  switch(rece_string[0])
							{
									case 'Z':/*�ⲿ�жϵ�����ת����һ����Ҫ���յ���*/
									{
										PicArray_ToBufferArray(firpic_position,2);
									}break;
									case 'A':/*�����жϵ�����ת���ڶ������յ���*/
									{
										PicArray_ToBufferArray(secpic_position,0);
									}break;
									case 'B':/*�����жϵ�����ת�����������յ���*/
									{
										PicArray_ToBufferArray(thirpic_position,2);
										
									}break;
									
									case 'C':/*�����жϵ�����ת�����ĸ����յ���*/
									{
										PicArray_ToBufferArray(fourpic_position,0);
										
									}break;
									case 'D':/*�����жϵ�����ת����������յ���*/
									{
										PicArray_ToBufferArray(fifpic_position,3);
										
									}break;
									
									case 'E':/*�����жϵ�����ת�����������յ���*/
									{
										PicArray_ToBufferArray(sixpic_position,0);
										
									}break;
									case 'F':/*�����жϵ�����������֮��ص���ʼλ�ã��ȴ�����*/
									{
										PicArray_ToBufferArray(retuinit_position,4);
										
									}break;
									case'#':/*ִ�н���ħ��*/
									{
										SolvecubeArray_ToBufferArray();
									}break;
									default:
									{
									
							    }break;

							}
					
				    change();		
						TIM_Cmd(TIM3, ENABLE);     /*���յ�ָ��֮���ٴ�TIM3*/					 			
						rece_flag=0;
					
					}
					
				if (flag_vpwm==1)	  
					{
						vpwm();				             /*�岹�Ƕ�*/
						flag_vpwm=0;
					}	
					
		}
		
}		
		
		
		
		
		
		
	   
 
