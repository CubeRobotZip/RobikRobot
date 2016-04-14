/*  �ļ���: instruction.c
 *�ļ����ܣ��ַ�������
 *��    ע���ַ�����������:��ʼ��־λ:#,������־λ:!
 *          ������д��ĸ90����ת����д��ĸ���������2����180����ת,�����'��Ϊ��ʱ�룬����'��Ϊ˳ʱ��
 *          U:����,D:����
 *          L:����,R:����,
 *          F:ǰ��,B:����
 *          ʾ����#B'R2U2B2DU2F2UB2R2U'L2U'L'U'FRB2RD'!
 */

#include "stm32f10x.h"
#include "instruction.h"
#include "usart.h"
#include "movement.h"

u16 solvecube_data[500][8];/*ִ�����ս��������*/



/*  ������:Analy_UsartString()
 *�������ܣ��������ڴ������ַ���������ħ�����㲽�����solvecube_data������
 *��    �룺��
 *��    ����solvecube_data���������б��
 *�����������SolvecubeArray_ToBufferArray()����
 *��    ע��
 */
u16 Analy_UsartString(void)
{
	u8 i=1;
	u8 startline_num=0;        /*��ʼΪsolvecube_data���鸳ֵ��������*/
	while(rece_string[i]!='!')
	{
	
		
			if((0x41<=rece_string[i]&&rece_string[i]<=0x5a)&&((0x41<=rece_string[i+1]&&rece_string[i+1]<=0x5a)||(rece_string[i+1]=='!')))   /*��ǰ�ַ�Ϊ��д��ĸ����һ���ַ�Ϊ��д��ĸ*/
			{
				  switch(rece_string[i])
					{
								case 'U':
								{
									Initial_Data(u_clockwise90,startline_num,startline_num+15);
									startline_num+=16;
								}break;
								
								case 'D':
								{
									Initial_Data(d_clockwise90,startline_num,startline_num+15);
									startline_num+=16;					
								}break;
								
								case 'L':
								{
									Initial_Data(l_clockwise90,startline_num,startline_num+3);
									startline_num+=4;						
								}break;
								
								case 'R':
								{
									Initial_Data(r_clockwise90,startline_num,startline_num+3);
									startline_num+=4;
								}break;
								
								case 'F':
								{
									Initial_Data(f_clockwise90,startline_num,startline_num+3);
									startline_num+=4;
								}break;
								
								case 'B':
								{
									Initial_Data(b_clockwise90,startline_num,startline_num+3);
									startline_num+=4;
								}break;
								
								default:break;
					
					}
						
				    i++;
					
			}
			
			
			else if((0x41<=rece_string[i]&&rece_string[i]<=0x5a)&&(rece_string[i+1]==0x27))    /*��ǰ�ַ�Ϊ��д��ĸ����һ���ַ�Ϊ�ַ���*/
			{	
				
				switch(rece_string[i])
					 {
								case 'U':
								{
									Initial_Data(u_anticlockwise90,startline_num,startline_num+15);
									startline_num+=16;
								}break;
								
								case 'D':
								{
									Initial_Data(d_anticlockwise90,startline_num,startline_num+15);
									startline_num+=16;					
								}break;
								
								case 'L':
								{
									Initial_Data(l_anticlockwise90,startline_num,startline_num+3);
									startline_num+=4;						
								}break;
								
								case 'R':
								{
									Initial_Data(r_anticlockwise90,startline_num,startline_num+3);
									startline_num+=4;
								}break;
								
								case 'F':
								{
									Initial_Data(f_anticlockwise90,startline_num,startline_num+3);
									startline_num+=4;
								}break;
								
								case 'B':
								{
									Initial_Data(b_anticlockwise90,startline_num,startline_num+3);
									startline_num+=4;
								}break;
								
								default:break;
					
					   }
					 
					i+=2;
						 
			}
			
			
		 else if((0x41<=rece_string[i]&&rece_string[i]<=0x5a)&&(rece_string[i+1]==0x32))    /**��ǰ�ַ�Ϊ��д��ĸ����һ���ַ�Ϊ����2*/
			{
				
				switch(rece_string[i])
					{
								case 'U':
								{
									Initial_Data(u_clock180,startline_num,startline_num+19);
									startline_num+=20;
								}break;
								
								case 'D':
								{
									Initial_Data(d_clock180,startline_num,startline_num+19);
									startline_num+=20;					
								}break;
								
								case 'L':
								{
									Initial_Data(l_clockwise90,startline_num,startline_num+3);
									startline_num+=4;	
									Initial_Data(l_clockwise90,startline_num,startline_num+3);
									startline_num+=4;	
									
								}break;
								
								case 'R':
								{
									Initial_Data(r_clockwise90,startline_num,startline_num+3);
									startline_num+=4;
									Initial_Data(r_clockwise90,startline_num,startline_num+3);
									startline_num+=4;
									
								}break;
								
								case 'F':
								{
									Initial_Data(f_clockwise90,startline_num,startline_num+3);
									startline_num+=4;
									Initial_Data(f_clockwise90,startline_num,startline_num+3);
									startline_num+=4;
									
								}break;
								
								case 'B':
								{
									Initial_Data(b_clockwise90,startline_num,startline_num+3);
									startline_num+=4;
									Initial_Data(b_clockwise90,startline_num,startline_num+3);
									startline_num+=4;
									
								}break;
								
								default:break;
							
							}
					
					i+=2;
							
		  }
			
		else
			{
				i++;
			}
					
			
	  }
	
	startline_num--;
		
	return (startline_num);

}


/*  ��������Initial_Data(u16 *array,u8 start_num,u8 end_num)
 *�������ܣ�Ϊsolvecube_data��ֵ
 *��    ��: array:��ά����ָ��,start_num:���鿪ʼ���,end_num:����������
 *��    ��: ��
 *�������: ��Analy_UsartString()��������
 *��    ע�����������Ϊ8����ά����ָ����Ϊ��������ʱ����Ҫȷ��
 */
void Initial_Data(u16 (*array)[8],u8 start_line,u8 end_line)
{
	u8 i,j;
	
	for(j=start_line;j<=end_line;j++)
	{
		
		for(i=0;i<8;i++)
		{
			solvecube_data[j][i]=*(*(array+(j-start_line))+i);			
		}
	
	}
}



