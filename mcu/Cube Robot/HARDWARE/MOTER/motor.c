/*  �ļ�����motor.c
 *�ļ���������Ҫ��Ŷ������������GPIO�ĳ�ʼ���Ͷ���ٶȿ��Ʋ岹�㷨
 *
 *��    ע��change����nΪ�ٶ�ֵ������ʵ�ʲ��ԣ����ֵ�nΪ50���߸�Сʱ����������ִ���
 *		      ��Ϊ���ת����һ���Ļ�е�ͺ��ԣ�ת����Ҫһ����ʱ�䣬����nֵ����̫С������
 *			    �з��ֵ�nֵΪ500����1000ʱ�����ת������
 */
#include "stm32f10x.h"
#include "motor.h"
#include "sys.h"
#include "instruction.h"
#include "movement.h"
#include "usart.h"


int point_now=-1;    /*����ִ�е�����*/
u8 point_aim=0;	    /*����ִ���������һ������*/

u16 n=500;		  /*�趨�Ĳ岹����*/
u16 m;		      /*��ǰ�Ĳ岹����*/
double dp;
double dp0[8];	  /*�岹����*/

u16 pwm[8]={1490,1455,1530,1480,1950,1890,1910,830};

u16 pos[500][8];


/*
 *�� �� ��:change()  
 *��������:��λ��ĩβ�ø���
 *		   ��Ч�������ǲ岹�������Ͳ岹������֪�������������͵�ǰ��λ�ü���
 *��    �룺��
 *��    ������
 *��    �ã��� vpwm()����		 
 *��    ע��Ҫʵ���Ƚ��ٶȣ�����ÿһ�ν���˺���ʱ��8��������費ͬ�Ĳ岹����
 */	
 void change(void)
{	
	 u8 s;                    /*����ĸ���*/
	 n=500;     		          /*�ٶ�ֵ*/
	 m=0;				  

   
   if(point_aim==lines_num)	 /*��pos[][]������-1��*/
   {
		 
				TIM_Cmd(TIM3, DISABLE);  /*�ص�TIMx*/					 
				point_aim=0;
				point_now=-1;
				switch(rece_string[0])
				 {
							 case 'Z':
							 {
									USART_SendChar('A');/*֪ͨ��λ���ĵ�һ����Ƭ*/
							 }break;
							 
							 case 'A':
							 {
									USART_SendChar('B');/*֪ͨ��λ���ĵڶ�����Ƭ*/
							 }break;
						 
							 case 'B':
							 {
									USART_SendChar('C');/*֪ͨ��λ���ĵ�������Ƭ*/
							 }break;
						 
							 case 'C':
							 {
									USART_SendChar('D');/*֪ͨ��λ���ĵ�������Ƭ*/
							 }break;
						 
							 case 'D':
							 {
									USART_SendChar('E');/*֪ͨ��λ���ĵ�������Ƭ*/
							 }break;
						 
							 case 'E':
							 {
									USART_SendChar('F');/*֪ͨ��λ���ĵ�������Ƭ*/
							 }break;
							 
							 default:
							 {
								 
							 }break;
				 
				 }			 
   }
	 
   else
   {
			point_aim++;
			point_now++;	
			for(s=0;s<8;s++)			   /*������һ������Ĳ岹����*/
			{

					if(pos[point_aim][s]>pos[point_now][s])
						{
								dp=pos[point_aim][s]-pos[point_now][s];
								dp0[s]=dp/n;
						}
					if(pos[point_aim][s]<=pos[point_now][s])
						{
							dp=pos[point_now][s]-pos[point_aim][s];
							dp0[s]=dp/n;
							dp0[s]=-dp0[s];
						}
			 }		 
		 
   }
	 
}


/*
 *�� �� ����pwm[]������º���  
 *�������������ݲ岹���岹ʱ����Ϊ20ms/16����Timer1���ƣ�ʹ���ƽ��ʵ���ٶȿ���
 *		  ��һ��������ִ����һ�к�ȥ������һ�����ݣ�������change()
 *��    �룺�� 
 *��    ������
 *��    �ã���main.c����
 *��    ע��
 */	
void vpwm(void)		 
{				                                                                                                                                                                                                                                                                                                                                                                                                 
			u8 j=0;
			u8 how=0;
			static u8 flag_how;
			static u8 flag_Tover;

			m++;							      /*�����ۼӲ岹���Ĵ���*/
			if(m==n)						    /*n�Ǳ�����ҵҪ�岹���ܴε�ִ����*/
					flag_Tover=1;				/*һ������ʱ���Ѿ����*/
			
			for(j=0;j<8;j++)
			{
					if(((pwm[j]-pos[point_aim][j])<5)||((pos[point_aim][j]-pwm[j])<5))	
					{						   	    /*��⿿���յ�λ��*/
						 how++;				   	/*�ǣ����ۼ�һ��*/
						 pwm[j]=pos[point_aim][j];/*����ֱ�ӹ��ȵ��յ�λ��*/
					}	
					else						    /*�������յ㣬�����岹*/
						pwm[j]=pos[point_now][j]+m*dp0[j];

			} 
			if(how==8)
				flag_how=1;	  				/*����������յ�*/
			 how=0; 

			if((flag_Tover==1)&&(flag_how==1))
			{								       /*�Ӳ岹�������������������涼�����յ㣬����ҵ�����*/
				 flag_Tover=0;
				 flag_how=0;
				 change();			 	   /*����ɱ�־��*/
			}
			return;
			
}


/* ������������ʼ�����ź������ӵ�GPIO����
 * ��    ע��PA.0--------PA.7
 */
void MotorPin_Init(void)
{
	 GPIO_InitTypeDef  GPIO_InitStructure;
	 	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   /*ʹ��PinA�˿�ʱ��*/
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;	//PA.0---PA.7 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		   /*�������*/
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		   /*IO���ٶ�Ϊ50MHz*/
	
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					         /*�����趨������ʼ��GPIOA*/
	 GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);						 //PB.5 �����
	
	
}

