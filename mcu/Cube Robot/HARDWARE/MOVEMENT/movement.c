/*  �ļ�����movement.c
 *�ļ�������
 *��    ע: �ڼ�������������ʱ,��ס�õ����Ǿ���λ�ã����������λ��
 */
#include "stm32f10x.h"
#include "movement.h"
#include "motor.h"
#include "usart.h"
#include "instruction.h"
static const u16 original_position[4]={1475,1445,1525,1440};          /*��ʼλ��1,2,3,4�Ŷ���ĽǶ�*/
static const u16 clockwise90_position[4]={695,650,730,600};           /*�ɳ�ʼλ��˳ʱ��ת��90��ʱ1,2,3,4�Ŷ���ĽǶ�*/
static const u16 anticlockwise90_position[4]={2350,2230,2310,2270};   /*�ɳ�ʼλ����ʱ��ת��90��ʱ1,2,3,4�Ŷ���ĽǶ�*/
static const u16 wrasp_position[4]={1995,1890,1990,1890};             /*��е��ץ��ħ��ʱ5,6,7,8�Ŷ���ĽǶ�*/
static const u16 loosen_position[4]={1480,1390,1450,1390};            /*��е���ɿ�ħ��ʱ5,6,7,8�Ŷ���ĽǶ�*/
 

u16 lines_num;
u16 initial_position[8];
u16 firpic_position[3][8];
u16 secpic_position[1][8];
u16 thirpic_position[3][8];
u16 fourpic_position[1][8];
u16 fifpic_position[4][8];
u16 sixpic_position[1][8];
u16 retuinit_position[5][8];

u16 u_clockwise90[16][8];/*�ϲ�˳ʱ��90��*/
u16 d_clockwise90[16][8];/*�²�˳ʱ��90��*/
u16 r_clockwise90[4][8]; /*�Ҳ�˳ʱ��90��*/
u16 l_clockwise90[4][8]; /*���˳ʱ��90��*/
u16 f_clockwise90[4][8]; /*ǰ��˳ʱ��90��*/
u16 b_clockwise90[4][8]; /*���˳ʱ��90��*/

u16 u_anticlockwise90[16][8];/*�ϲ���ʱ��90��*/
u16 d_anticlockwise90[16][8];/*�²���ʱ��90��*/
u16 r_anticlockwise90[4][8]; /*�Ҳ���ʱ��90��*/
u16 l_anticlockwise90[4][8]; /*�����ʱ��90��*/
u16 f_anticlockwise90[4][8]; /*ǰ����ʱ��90��*/
u16 b_anticlockwise90[4][8]; /*�����ʱ��90��*/


/*����ǰ����ת180��ʱ��ֻ��ִ��������ʱ��90�Ȼ�������˳ʱ��90������*/
u16 u_clock180[20][8];    /*�ϲ�180��*/
u16 d_clock180[20][8];    /*�²�180��*/


/*
 *  ��������Calcul_IniticalPosition()
 *��������: �������ĳ�ʼ�Ƕ�
 *��    ��: ��
 *��    ��: ��
 */
void Calcul_InitPosition(void)
{
	u8 i,j;
	for(i=0;i<4;i++)
	{
		initial_position[i]=original_position[i];
	}
	for(i=4,j=0;i<8;i++,j++)
	{
		initial_position[i]=wrasp_position[j];
	}
}

/*  ������:Calcul_FirPicPosition()
 *��������:�������յ�һ����Ķ����������
 *��    ע:������=�����-1 
 */
void Calcul_FirPicPosition(void)
{
	u8 i;
	Calcul_InitPosition();
	
	for(i=0;i<8;i++)                     /*��һ�зų�ʼλ��*/
	{
	  firpic_position[0][i]=initial_position[i];
	}
	
	for(i=0;i<8;i++)                     /*�ڶ�����ʱ���Ƶ�һ��*/
	{
		firpic_position[1][i]=firpic_position[0][i];
	}
	firpic_position[1][5]=loosen_position[1];            /*6����*/
	firpic_position[1][7]=loosen_position[3];            /*8����*/

 	for(i=0;i<8;i++)                     /*��������ʱ���Ƶڶ���*/
	{
		firpic_position[2][i]=firpic_position[1][i];
	}
	
	           /*��������*/                        
		firpic_position[2][0]=clockwise90_position[0];      /*1˳ʱ��90��,*/
		firpic_position[2][2]=anticlockwise90_position[2];  /*3��ʱ��90��*/                        	
}


/*  ������:Calcul_SecPicPosition()
 *��������:�������յڶ�����Ķ����������
 *��    ע:������=�����-1,������Calcul_FirPicPosition()����
 */
void Calcul_SecPicPosition(void)
{
	u8 i;
	
 	for(i=0;i<8;i++)                     
	{
		secpic_position[0][i]=firpic_position[2][i];
	}
                      /*��������*/   
 secpic_position[0][0]=anticlockwise90_position[0];       /*1��ʱ��90��,*/ 
 secpic_position[0][2]=clockwise90_position[2];	          /*3˳ʱ��90��*/  

}


/*  ������:Calcul_ThirPicPosition()
 *��������:�������յ�������Ķ����������
 *��    ע:������=�����-1 
 */
void Calcul_ThirPicPosition(void)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		thirpic_position[0][i]=secpic_position[0][i];
	}
	
	thirpic_position[0][5]=wrasp_position[1];  /*6ǰ��*/
	thirpic_position[0][7]=wrasp_position[3];  /*8ǰ��*/
	
	for(i=0;i<8;i++)
	{
		thirpic_position[1][i]=thirpic_position[0][i];  /*���Ƶ�һ�е��ڶ���*/
	}
	
	thirpic_position[1][4]=loosen_position[0];   /*5����*/
	thirpic_position[1][6]=loosen_position[2];   /*7����*/
	
		/*����ǰ��*/
	for(i=0;i<8;i++)
	{
	  thirpic_position[2][i]=thirpic_position[1][i];  /*���Ƶ�һ�е��ڶ���*/
	}
	
	thirpic_position[2][1]=clockwise90_position[1];                 /*2˳ʱ��*/
	thirpic_position[2][3]=anticlockwise90_position[3];             /*4��ʱ��*/
	
}


/*  ������:Calcul_FourPicPosition()
 *��������:�������յ��ĸ���Ķ����������
 *��    ע:������=�����-1 
 */
void Calcul_FourPicPosition(void)
{
	 u8 i;
	for(i=0;i<8;i++)
		{
			fourpic_position[0][i]=thirpic_position[2][i];   
		}
		
		/*���պ���*/
		fourpic_position[0][1]=anticlockwise90_position[1];  /*2��ʱ��*/
		fourpic_position[0][3]=clockwise90_position[3];      /*4˳ʱ��*/
}

/*  ������:Calcul_FifPicPosition()
 *��������:�������յ������Ķ����������
 *��    ע:������=�����-1,����
 */
void Calcul_FifPicPosition(void)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		fifpic_position[0][i]=fourpic_position[0][i];
	}
	
	fourpic_position[0][0]=original_position[0];	         /*1�ص���ʼλ��*/
	fourpic_position[0][2]=original_position[2];	         /*3�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		fifpic_position[1][i]=fifpic_position[0][i];
	}
	
  fifpic_position[1][4]=wrasp_position[0];		/*5ǰ��*/
  fifpic_position[1][6]=wrasp_position[2];		/*7ǰ��*/	

	for(i=0;i<8;i++)
	{
		fifpic_position[2][i]=fifpic_position[1][i];
	}
	
	fifpic_position[2][5]=loosen_position[1];   /*6����*/
	fifpic_position[2][7]=loosen_position[3];   /*8����*/
	
	
	/*��������*/
	for(i=0;i<8;i++)
	{
		fifpic_position[3][i]=fifpic_position[2][i];
	}
	
	fifpic_position[3][0]=clockwise90_position[0];      /*1˳ʱ��*/
	fifpic_position[3][2]=anticlockwise90_position[2];  /*3��ʱ��*/
	
}


/*  ������:Calcul_SixPicPosition()
 *��������:�������յ�������Ķ����������
 *��    ע:������=�����-1 
 */
void Calcul_SixPicPosition(void)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		sixpic_position[0][i]=fifpic_position[3][i];
	}
		/*��������*/
	sixpic_position[0][0]=anticlockwise90_position[0];/*1��ʱ��*/
	sixpic_position[0][2]=clockwise90_position[2];    /*3˳ʱ��*/
}


/*  ������: RetuIni_AftPic()
 *��������: ��������6����֮��ص���ʼλ��
 *��    ע������ԭ·����·�����أ����Һ�ԭ���İڷ�λ����ͬ
 */
void RetuIni_AftPic(void)
{
		u8 i;
	
	for(i=0;i<8;i++)
	{
		retuinit_position[0][i]=sixpic_position[0][i];
	}	
		
	retuinit_position[0][1]=original_position[1];  /*2�ص���ʼλ��*/
	retuinit_position[0][3]=original_position[3];  /*4�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		retuinit_position[1][i]=retuinit_position[0][i];
	}
	retuinit_position[1][5]=wrasp_position[1];  /*6ǰ��*/
	retuinit_position[1][7]=wrasp_position[3];  /*8ǰ��*/
	
	for(i=0;i<8;i++)
	{
		retuinit_position[2][i]=retuinit_position[1][i];
	}
	retuinit_position[2][4]=loosen_position[0];  /*5����*/
	retuinit_position[2][6]=loosen_position[2];  /*7����*/
	
	for(i=0;i<8;i++)
	{
		retuinit_position[3][i]=retuinit_position[2][i];
	}
	
	retuinit_position[3][0]=original_position[0]; /*1�ص���ʼλ��*/ 
	retuinit_position[3][2]=original_position[2]; /*3�ص���ʼλ��*/ 
		
	for(i=0;i<8;i++)
	{
		retuinit_position[4][i]=retuinit_position[3][i];
	}
	
	retuinit_position[4][4]=wrasp_position[0];    /*5ǰ��*/
	retuinit_position[4][6]=wrasp_position[2];    /*7ǰ��*/	

}




/*  ������: Calcul_Uclockwise90()
 *�������ܣ�����ħ���ϲ�˳ʱ����ת90�Ķ���Ƕ�����
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע����ʼ����˳��Ҫע��
 */
void Calcul_Uclockwise90(void)
{
	u8 i,j,k;
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[0][i]=initial_position[i];
	}
	
	u_clockwise90[0][5]=loosen_position[1]; /*6����*/
	u_clockwise90[0][7]=loosen_position[3]; /*8����*/
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[1][i]=u_clockwise90[0][i];
	}
	
	u_clockwise90[1][0]=clockwise90_position[0];       /*1˳ʱ��*/
	u_clockwise90[1][2]=anticlockwise90_position[2];   /*3��ʱ��*/
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[2][i]=u_clockwise90[1][i];
	}
	
	u_clockwise90[2][5]=wrasp_position[1]; /*6ǰ��*/
	u_clockwise90[2][7]=wrasp_position[3]; /*8ǰ��*/
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[3][i]=u_clockwise90[2][i];
	}
	u_clockwise90[3][4]=loosen_position[0]; /*5����*/
	u_clockwise90[3][6]=loosen_position[2]; /*7����*/


	for(i=0;i<8;i++)
	{
		u_clockwise90[4][i]=u_clockwise90[3][i];
	}
	
	 u_clockwise90[4][0]=original_position[0];/*1�ص���ʼλ��*/
	 u_clockwise90[4][2]=original_position[2];/*3�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[5][i]=u_clockwise90[4][i];
	}
	
	u_clockwise90[5][4]=wrasp_position[0]; /*5ǰ��*/
	u_clockwise90[5][6]=wrasp_position[2]; /*7ǰ������ʱ�����ʼλ��*/
	
   
/*ǰ��������ʱ����ת�Ĵ�����ͬ��ǰ�����ɵ�������ͬ��������ħ������˳ʱ����ת90��*/	
	
//	for(i=0;i<8;i++)
//	{
//		u_clockwise90[6][i]=u_clockwise90[5][i];
//	}
//	
//	u_clockwise90[6][3]=anticlockwise90_position[3];/*4��ʱ��*/
//	
//	 
//	for(i=0;i<8;i++)
//	{
//		u_clockwise90[7][i]=u_clockwise90[6][i];
//	}
//	
//	u_clockwise90[7][7]=loosen_position[3]; /*8����*/
//	
//	for(i=0;i<8;i++)
//	{
//		u_clockwise90[8][i]=u_clockwise90[7][i];
//	}
//	
//	u_clockwise90[8][3]=original_position[3];/*4�ص���ʼλ��*/
//	
//	for(i=0;i<8;i++)
//	{
//		u_clockwise90[9][i]=u_clockwise90[8][i];
//	}
//	
//	u_clockwise90[9][7]=wrasp_position[3];   /*8ǰ��,�˿̵��ﴦ��һ�ε����ʼλ��*/

	
	/*ħ������˳ʱ����ת90��*/
	
	for(j=6,k=0;j<=9;j++,k++)
	{
		for(i=0;i<8;i++)
		{
			u_clockwise90[j][i]=r_clockwise90[k][i];				
		}
	
	}
		
 /*�����Ǵӷŵ���ֱ������*/
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[10][i]=u_clockwise90[9][i];
	}

	u_clockwise90[10][5]=loosen_position[1];	  /*6����*/
	u_clockwise90[10][7]=loosen_position[3];    /*8����*/
	
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[11][i]=u_clockwise90[10][i];
	}
	
	u_clockwise90[11][0]=anticlockwise90_position[0];	  /*1��ʱ��*/
	u_clockwise90[11][2]=clockwise90_position[2];       /*3˳ʱ��*/
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[12][i]=u_clockwise90[11][i];
	}
	
	u_clockwise90[12][5]=wrasp_position[1];	 /*6ǰ��*/
	u_clockwise90[12][7]=wrasp_position[3];  /*8ǰ��*/
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[13][i]=u_clockwise90[12][i];
	}
	
	u_clockwise90[13][4]=loosen_position[0];	   /*5����*/
	u_clockwise90[13][6]=loosen_position[2];     /*7����*/
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[14][i]=u_clockwise90[13][i];
	}
	u_clockwise90[14][0]=original_position[0];	/*1�ص���ʼλ��*/
	u_clockwise90[14][2]=original_position[2];  /*3�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		u_clockwise90[15][i]=u_clockwise90[14][i];
	}
	u_clockwise90[15][4]=wrasp_position[0];   /*5ǰ��*/
	u_clockwise90[15][6]=wrasp_position[2];	  /*7ǰ��*/  
	
}

/*  ������: Calcul_Uanticlockwise90()
 *�������ܣ�����ħ���ϲ���ʱ����ת90�Ķ���Ƕ�����
 *��    �룺��
 *��    ������
 *��    ע�����ұ߷�ת�����泯��,����˳ʱ�����ɵ�����
 */
void Calcul_Uanticlockwise90(void)
{
		u8 i,j,k;
	
	/*�ӳ�ʼλ�õ��ұߵ��Ĺ���*/
	for(i=0;i<=5;i++)
	{
		for(j=0;j<8;j++)
		
			{
				u_anticlockwise90[i][j]=u_clockwise90[i][j];	
			}
	}
	
	
	/*ħ��������ʱ����ת90��*/
	for(j=6,k=0;j<=9;j++,k++)
	{
		for(i=0;i<8;i++)
		{
			u_anticlockwise90[j][i]=r_anticlockwise90[k][i];				
		}
	
	}

	
	/*�����Ǵӷŵ���ֱ������*/
	for(j=10;j<=15;j++)
	{
		
		for(i=0;i<8;i++)
		{
			u_anticlockwise90[j][i]=u_clockwise90[j][i];				
		}
	
	}
	
	
}


/*  ������: Calcul_Dclockwise90()
 *�������ܣ�����ħ���²�˳ʱ����ת90�Ķ���Ƕ�����
 *��    �룺��
 *��    ������
 *�������������ʼ����������
 *��    ע������ת�����泯�ң�����ע���ʼ���������õ�˳����ʱ����˳ʱ��֮�����
 */
void Calcul_Dclockwise90(void)
{
	u8 i,j,k;
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[0][i]=initial_position[i];
	}
	
	d_clockwise90[0][5]=loosen_position[1];/*6����*/
	d_clockwise90[0][7]=loosen_position[3];/*8����*/
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[1][i]=d_clockwise90[0][i];
	}
	
	d_clockwise90[1][0]=anticlockwise90_position[0];       /*1��ʱ��*/
	d_clockwise90[1][2]=clockwise90_position[2];           /*3˳ʱ�룬�������ת�Ķ���*/
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[2][i]=d_clockwise90[1][i];
	}
	
	d_clockwise90[2][5]=wrasp_position[1]; /*6ǰ��*/
	d_clockwise90[2][7]=wrasp_position[3]; /*8ǰ��*/
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[3][i]=d_clockwise90[2][i];
	}
	d_clockwise90[3][4]=loosen_position[0]; /*5����*/
	d_clockwise90[3][6]=loosen_position[2]; /*7����*/


	for(i=0;i<8;i++)
	{
		d_clockwise90[4][i]=d_clockwise90[3][i];
	}
	
	 d_clockwise90[4][0]=original_position[0];/*1�ص���ʼλ��*/
	 d_clockwise90[4][2]=original_position[2];/*3�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[5][i]=d_clockwise90[4][i];
	}
	
	d_clockwise90[5][4]=wrasp_position[0]; /*5ǰ��*/
	d_clockwise90[5][6]=wrasp_position[2]; /*7ǰ������ʱ�����ʼλ��*/
   
	
	/*ǰ��������ʱ����ת�Ĵ�����ͬ��ǰ�����ɵ�������ͬ*/
	
//	for(i=0;i<8;i++)
//	{
//		d_clockwise90[6][i]=d_clockwise90[5][i];
//	}
//	
//	d_clockwise90[6][3]=anticlockwise90_position[3];/*4��ʱ��*/
//	
//	 
//	for(i=0;i<8;i++)
//	{
//		d_clockwise90[7][i]=d_clockwise90[6][i];
//	}
//	
//	d_clockwise90[7][7]=loosen_position[3]; /*8����*/
//	
//	for(i=0;i<8;i++)
//	{
//		d_clockwise90[8][i]=d_clockwise90[7][i];
//	}
//	
//	d_clockwise90[8][3]=original_position[3];/*4�ص���ʼλ��*/
//	
//	for(i=0;i<8;i++)
//	{
//		d_clockwise90[9][i]=d_clockwise90[8][i];
//	}
//
//	d_clockwise90[9][7]=wrasp_position[3];   /*8ǰ��,�˿̵��ﴦ��һ�ε����ʼλ��*/


	/*ħ������˳ʱ����ת90��*/
	for(j=6,k=0;j<=9;j++,k++)
	{
		for(i=0;i<8;i++)
		{
			d_clockwise90[j][i]=r_clockwise90[k][i];				
		}
	
	}

	
	/*�����Ǵӷŵ���ֱ������*/
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[10][i]=d_clockwise90[9][i];
	}

	d_clockwise90[10][5]=loosen_position[1];	  /*6����*/
	d_clockwise90[10][7]=loosen_position[3];    /*8����*/
	
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[11][i]=d_clockwise90[10][i];
	}
	
	d_clockwise90[11][0]=clockwise90_position[0];	        /*1˳ʱ��*/
	d_clockwise90[11][2]=anticlockwise90_position[2];     /*3��ʱ��*/
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[12][i]=d_clockwise90[11][i];
	}
	
	d_clockwise90[12][5]=wrasp_position[1];	 /*6ǰ��*/
	d_clockwise90[12][7]=wrasp_position[3];  /*8ǰ��*/
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[13][i]=d_clockwise90[12][i];
	}
	
	d_clockwise90[13][4]=loosen_position[0];	   /*5����*/
	d_clockwise90[13][6]=loosen_position[2];     /*7����*/
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[14][i]=d_clockwise90[13][i];
	}
	d_clockwise90[14][0]=original_position[0];	/*1�ص���ʼλ��*/
	d_clockwise90[14][2]=original_position[2];  /*3�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		d_clockwise90[15][i]=d_clockwise90[14][i];
	}
	d_clockwise90[15][4]=wrasp_position[0];      /*5ǰ��*/
	d_clockwise90[15][6]=wrasp_position[2];	     /*7ǰ��*/  

}


/*  ������: Calcul_Danticlockwise90()
 *�������ܣ�����ħ���²���ʱ����ת90�Ķ���Ƕ�����
 *��    �룺��
 *��    ������
 *��    ע������ת�����泯��
 */
void Calcul_Danticlockwise90(void)
{
	
    u8 i,j,k;
	
	/*�ӳ�ʼλ������ת*/
	for(i=0;i<=5;i++)
	{
		for(j=0;j<8;j++)
		
			{
				d_anticlockwise90[i][j]=d_clockwise90[i][j];	
			}
	}
	
	
	/*ħ��������ʱ����ת90��,*/
	for(j=6,k=0;j<=9;j++,k++)
	{
		for(i=0;i<8;i++)
		{
			d_anticlockwise90[j][i]=r_anticlockwise90[k][i];				
		}
	
	}

	
	/*�����Ǵӷŵ���ֱ������*/
	for(j=10;j<=15;j++)
	{
		
		for(i=0;i<8;i++)
		{
			d_anticlockwise90[j][i]=d_clockwise90[j][i];				
		}
	
	}	
	
	
}


/*  ��������Calcul_Lclockwise90()
 *�������ܣ�����ħ������˳ʱ����ת90�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע���ȵ���initial_position()����
 */
void Calcul_Lclockwise90(void)
{
	
	u8 i;
	
	for(i=0;i<8;i++)
	{
		l_clockwise90[0][i]=initial_position[i];
	}
	
	l_clockwise90[0][1]=anticlockwise90_position[1];/*2��ʱ��*/
	
	for(i=0;i<8;i++)
	{
		l_clockwise90[1][i]=l_clockwise90[0][i];
	}
	
	l_clockwise90[1][5]=loosen_position[1]; /*6����*/
	
	for(i=0;i<8;i++)
	{
		l_clockwise90[2][i]=l_clockwise90[1][i];
	}
	
	l_clockwise90[2][1]=original_position[1];/*2�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		l_clockwise90[3][i]=l_clockwise90[2][i];
	}
	
	l_clockwise90[3][5]=wrasp_position[1]; /*6ǰ��*/
	
	
}


/*  ��������Calcul_Lanticlockwise90()
 *�������ܣ�����ħ��������ʱ����ת90�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע���ȵ���initial_position()����
 */
void Calcul_Lanticlockwise90(void)
{
	u8 i;
	
	for(i=0;i<8;i++)
	{
		l_anticlockwise90[0][i]=initial_position[i];
	}
	
	l_anticlockwise90[0][1]=clockwise90_position[1];/*2˳ʱ��*/
	
	for(i=0;i<8;i++)
	{
		l_anticlockwise90[1][i]=l_anticlockwise90[0][i];
	}
	
	l_anticlockwise90[1][5]=loosen_position[1]; /*6����*/
	
	for(i=0;i<8;i++)
	{
		l_anticlockwise90[2][i]=l_anticlockwise90[1][i];
	}
	
	l_anticlockwise90[2][1]=original_position[1];/*2�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		l_anticlockwise90[3][i]=l_anticlockwise90[2][i];
	}
	
	l_anticlockwise90[3][5]=wrasp_position[1]; /*6ǰ��*/
	

}



/*  ��������Calcul_Rclockwise90()
 *�������ܣ�����ħ������˳ʱ����ת90�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע���ȵ���initial_position()����
 */
void Calcul_Rclockwise90(void)
{
	u8 i;
	
	for(i=0;i<8;i++)
	{
		r_clockwise90[0][i]=initial_position[i];
	}
	
	r_clockwise90[0][3]=anticlockwise90_position[3];/*4��ʱ��*/
	
	for(i=0;i<8;i++)
	{
		r_clockwise90[1][i]=r_clockwise90[0][i];
	}
	
	r_clockwise90[1][7]=loosen_position[3]; /*8����*/
	
	for(i=0;i<8;i++)
	{
		r_clockwise90[2][i]=r_clockwise90[1][i];
	}
	
	r_clockwise90[2][3]=original_position[3];/*4�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		r_clockwise90[3][i]=r_clockwise90[2][i];
	}
	
	r_clockwise90[3][7]=wrasp_position[3]; /*8ǰ��*/
	
}



/*  ��������Calcul_Ranticlockwise90()
 *�������ܣ�����ħ��������ʱ����ת90�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע���ȵ���initial_position()����
 */
void Calcul_Ranticlockwise90(void)
{
	u8 i;
	
	for(i=0;i<8;i++)
	{
		r_anticlockwise90[0][i]=initial_position[i];
	}
	
    r_anticlockwise90[0][3]=clockwise90_position[3];/*4˳ʱ��*/
	
	for(i=0;i<8;i++)
	{
		r_anticlockwise90[1][i]=r_anticlockwise90[0][i];
	}
	
	r_anticlockwise90[1][7]=loosen_position[3]; /*8����*/
	
	for(i=0;i<8;i++)
	{
		r_anticlockwise90[2][i]=r_anticlockwise90[1][i];
	}
	
	r_anticlockwise90[2][3]=original_position[3];/*4�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		r_anticlockwise90[3][i]=r_anticlockwise90[2][i];
	}
	
	r_anticlockwise90[3][7]=wrasp_position[3]; /*8ǰ��*/
	
}



/*  ��������Calcul_Fclockwise90()
 *�������ܣ�����ħ��ǰ��˳ʱ����ת90�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע��
 */
void Calcul_Fclockwise90(void)
{
    u8 i;
	
	for(i=0;i<8;i++)
	{
		f_clockwise90[0][i]=initial_position[i];
	}
	
	f_clockwise90[0][2]=anticlockwise90_position[2];/*3��ʱ��*/
	
	for(i=0;i<8;i++)
	{
		f_clockwise90[1][i]=f_clockwise90[0][i];
	}
	
	f_clockwise90[1][6]=loosen_position[2]; /*7����*/
	
	for(i=0;i<8;i++)
	{
		f_clockwise90[2][i]=f_clockwise90[1][i];
	}
	
	f_clockwise90[2][2]=original_position[2];/*3�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		f_clockwise90[3][i]=f_clockwise90[2][i];
	}
	
	f_clockwise90[3][6]=wrasp_position[2]; /*7ǰ��*/
	
}


/*  ��������Calcul_Fanticlockwise90()
 *�������ܣ�����ħ��ǰ����ʱ����ת90�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע��
 */
void Calcul_Fanticlockwise90(void)
{
	u8 i;
	
	for(i=0;i<8;i++)
	{
		f_anticlockwise90[0][i]=initial_position[i];
	}
	
	f_anticlockwise90[0][2]=clockwise90_position[2];/*3˳ʱ��*/
	
	for(i=0;i<8;i++)
	{
		f_anticlockwise90[1][i]=f_anticlockwise90[0][i];
	}
	
	f_anticlockwise90[1][6]=loosen_position[2]; /*7����*/
	
	for(i=0;i<8;i++)
	{
		f_anticlockwise90[2][i]=f_anticlockwise90[1][i];
	}
	
	f_anticlockwise90[2][2]=original_position[2];/*3�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		f_anticlockwise90[3][i]=f_anticlockwise90[2][i];
	}
	
	f_anticlockwise90[3][6]=wrasp_position[2]; /*7ǰ��*/
	
}

/*  ��������Calcul_	Bclockwise90()
 *�������ܣ�����ħ������˳ʱ����ת90�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע��
 */
void Calcul_Bclockwise90(void)
{
	u8 i;
	
	for(i=0;i<8;i++)
	{
		b_clockwise90[0][i]=initial_position[i];
	}
	
	b_clockwise90[0][0]=anticlockwise90_position[0];/*1��ʱ��*/
	
	for(i=0;i<8;i++)
	{
		b_clockwise90[1][i]=b_clockwise90[0][i];
	}
	
	b_clockwise90[1][4]=loosen_position[0]; /*5����*/
	
	for(i=0;i<8;i++)
	{
		b_clockwise90[2][i]=b_clockwise90[1][i];
	}
	
	b_clockwise90[2][0]=original_position[0];/*1�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		b_clockwise90[3][i]=b_clockwise90[2][i];
	}
	
	b_clockwise90[3][4]=wrasp_position[0]; /*5ǰ��*/
	

}

/*  ��������Calcul_	Bantianticlockwise90()
 *�������ܣ�����ħ��������ʱ����ת90�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע��
 */
void Calcul_Banticlockwise90(void)
{
	u8 i;
	
	for(i=0;i<8;i++)
	{
		b_anticlockwise90[0][i]=initial_position[i];
	}
	
	b_anticlockwise90[0][0]=clockwise90_position[0];    /*1˳ʱ��*/
	
	for(i=0;i<8;i++)
	{
		b_anticlockwise90[1][i]=b_anticlockwise90[0][i];
	}
	
	b_anticlockwise90[1][4]=loosen_position[0];         /*5����*/
	
	for(i=0;i<8;i++)
	{
		b_anticlockwise90[2][i]=b_anticlockwise90[1][i];
	}
	
	b_anticlockwise90[2][0]=original_position[0];      /*1�ص���ʼλ��*/
	
	for(i=0;i<8;i++)
	{
		b_anticlockwise90[3][i]=b_anticlockwise90[2][i];
	}
	
	b_anticlockwise90[3][4]=wrasp_position[0];         /*5ǰ��*/
	
}




/*  ��������Calcul_Uclock180()
 *�������ܣ�����ħ��������ת180�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע�����������19
 */
void Calcul_Uclock180(void)
{
   u8 i,j,k;
	
   /*�ӳ�ʼλ�õ����ҵ����Ĺ���*/
	
	for(j=0;j<=5;j++)
	{
		for(i=0;i<8;i++)
		{
			u_clock180[j][i]=u_clockwise90[j][i];
		}
		
	}
	
	/*ִ����������˳ʱ����ת*/
	
	for(j=6,k=0;j<=9;j++,k++)
	{
		for(i=0;i<8;i++)
		{
			u_clock180[j][i]=r_clockwise90[k][i];				
		}
	
	}
	
	for(k=0,j=10;j<=13;j++,k++)
	{
		for(i=0;i<8;i++)
		{
			u_clock180[j][i]=r_clockwise90[k][i];				
		}
	
	}
	
	/*�ӷŵ���ֱ���Ĺ���*/   
	
	for(j=10;j<=15;j++)
	{
		for(i=0;i<8;i++)
		{
			u_clock180[j+4][i]=u_clockwise90[j][i];				
		}
	
	}	

}


/*  ��������Calcul_Dclock180()
 *�������ܣ�����ħ��������ת180�ȵĶ��ִ������
 *��    �룺��
 *��    ������
 *�����������ʼ������
 *��    ע�����������19
 */
void Calcul_Dclock180(void)
{
	 u8 i,j,k;
	
	/*�ӳ�ʹλ�õ��������Ĺ���*/
		for(j=0;j<=5;j++)
	{
		for(i=0;i<8;i++)
		{
			d_clock180[j][i]=d_clockwise90[j][i];
		}
	}
	
	
  /*ִ����������˳ʱ����ת*/
	for(j=6,k=0;j<=9;j++,k++)
	{
		for(i=0;i<8;i++)
		{
			d_clock180[j][i]=r_clockwise90[k][i];				
		}
	
	}
	
	for(j=10,k=0;j<=13;j++,k++)
	{
		for(i=0;i<8;i++)
		{
			d_clock180[j][i]=r_clockwise90[k][i];				
		}
	
	}
	
	/*�ӷŵ���ֱ���Ĺ���*/   

	for(j=10;j<=15;j++)
	{
		for(i=0;i<8;i++)
		{
			d_clock180[j+4][i]=d_clockwise90[j][i];				
		}
	
	}	

}

/*  ��������Init_TotalArray()
 *�������ܣ���������Ҫ�ڳ�����һ��ʼ����ĺ������ڴ˺����У��Գ�ʼ������
 *��    �룺��
 *��    ������
 *��    ע��ע����ú�����˳��,��������Ҫ530us
 */
void Init_TotalArray(void)
{
	Calcul_InitPosition(); /*�˺������ȱ���ʼ������Ϊ���ɵ�����ᱻ�Ժ�ܶຯ���õ�*/
	
	Calcul_FirPicPosition();
  Calcul_SecPicPosition();
  Calcul_ThirPicPosition();
  Calcul_FourPicPosition();
  Calcul_FifPicPosition();
  Calcul_SixPicPosition();
  RetuIni_AftPic();
	
	Calcul_Lclockwise90();
	Calcul_Rclockwise90();
	Calcul_Fclockwise90();
	Calcul_Bclockwise90();
	Calcul_Lanticlockwise90();
	Calcul_Ranticlockwise90();
	Calcul_Fanticlockwise90();
	Calcul_Banticlockwise90();

	
  Calcul_Uclockwise90();
  Calcul_Uanticlockwise90();
  Calcul_Dclockwise90();
  Calcul_Danticlockwise90();

  Calcul_Uclock180();
  Calcul_Dclock180(); /*������������˳��Ҫ��*/
}

/*  ��������Init_PWM()
 *�������ܣ�
 *��    ע��
 */
void Init_PWM(void)
{
	u8 i,j;
	
	for(i=0;i<4;i++)
	{
		pwm[i]=original_position[i];
	}
	for(i=4,j=0;i<8;i++,j++)
	{
		pwm[i]=wrasp_position[j];
	}

}


/*  �������� SolvecubeArray_ToBufferArray()
 *�������ܣ� �ѽ���ħ���ľ޴�����Ž���������u16 pos[500][8]��
 *��    �룺 ��
 *��    ���� �����б�
 *��    ע�� �ڰ����������뻺������ʱ��Ҫ�ص���ʱ������ֹ�岹�����иı�ȫ�ֱ���lines_num
 */
void  SolvecubeArray_ToBufferArray(void)
{
	 u16 i,j; 
	
  lines_num=Analy_UsartString()+1;

	for(i=0;i<8;i++)
		{
		
			pos[0][i]=initial_position[i];
		}

	for(j=1;j<=lines_num;j++)
	{
		for(i=0;i<8;i++)
		{
		
			pos[j][i]=solvecube_data[j-1][i];
		}
	
	}	
		
}	

/*  ��������PicArray_ToBufferArray(u(*array)[8],line_num)
 *�������ܣ���������Ҫִ�е�������뻺�����飬��������Ҫִ��������б�
 *��    �룺��ά����ָ��(*array)[8]�������б�line_num
 *��    ���������б�
 *��    ע���ڰ����������뻺������ʱ��Ҫ�ص���ʱ������ֹ�岹�����иı�ȫ�ֱ���lines_num
 */
void PicArray_ToBufferArray(u16 (*array)[8],u16 arrayline_num)
{
		u8 i,j;
	
	  lines_num=arrayline_num+1;
	
		for(i=0;i<8;i++)
		{
		
			pos[0][i]=initial_position[i];
		}

		for(j=1;j<=lines_num;j++)
		{
			
			for(i=0;i<8;i++)
			{
				pos[j][i]=*(*(array+j-1)+i);			
			}
		
		}
	
}

/*
 *
 */
void Init_Pwm(void)
{

	
}	
