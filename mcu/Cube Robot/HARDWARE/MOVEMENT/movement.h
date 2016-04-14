#ifndef ____MOVEMENT____H____
#define ____MOVEMENT____H____

#include "stm32f10x.h"

extern u16 initial_position[8];

extern u16 firpic_position[3][8];
extern u16 secpic_position[1][8];
extern u16 thirpic_position[3][8];
extern u16 fourpic_position[1][8];
extern u16 fifpic_position[4][8];
extern u16 sixpic_position[1][8];
extern u16 retuinit_position[5][8];


extern u16 u_clockwise90[16][8];/*�ϲ�˳ʱ��90��*/
extern u16 d_clockwise90[16][8];/*�²�˳ʱ��90��*/
extern u16 r_clockwise90[4][8];/*�Ҳ�˳ʱ��90��*/
extern u16 l_clockwise90[4][8];/*���˳ʱ��90��*/
extern u16 f_clockwise90[4][8];/*ǰ��˳ʱ��90��*/
extern u16 b_clockwise90[4][8];/*���˳ʱ��90��*/

extern u16 u_anticlockwise90[16][8];/*�ϲ���ʱ��90��*/
extern u16 d_anticlockwise90[16][8];/*�²���ʱ��90��*/
extern u16 r_anticlockwise90[4][8];/*�Ҳ���ʱ��90��*/
extern u16 l_anticlockwise90[4][8];/*�����ʱ��90��*/
extern u16 f_anticlockwise90[4][8];/*ǰ����ʱ��90��*/
extern u16 b_anticlockwise90[4][8];/*�����ʱ��90��*/

extern u16 u_clock180[20][8];    /*�ϲ�180��*/
extern u16 d_clock180[20][8];    /*�²�180��*/


void Calcul_InitPosition(void);

void Calcul_FirPicPosition(void);
void Calcul_SecPicPosition(void);
void Calcul_ThirPicPosition(void);
void Calcul_FourPicPosition(void);
void Calcul_FifPicPosition(void);
void Calcul_SixPicPosition(void);
void RetuIni_AftPic(void);

void Calcul_Uclockwise90(void);
void Calcul_Dclockwise90(void);
void Calcul_Lclockwise90(void);
void Calcul_Rclockwise90(void);
void Calcul_Fclockwise90(void);
void Calcul_Bclockwise90(void);

void Calcul_Uanticlockwise90(void);
void Calcul_Danticlockwise90(void);
void Calcul_Lanticlockwise90(void);
void Calcul_Ranticlockwise90(void);
void Calcul_Fanticlockwise90(void);
void Calcul_Banticlockwise90(void);


void Calcul_Uclock180(void);
void Calcul_Dclock180(void);

void Init_TotalArray(void);
void Init_PWM(void);
void SolvecubeArray_ToBufferArray(void);
void PicArray_ToBufferArray(u16 (*array)[8],u16 line_num);


#endif
