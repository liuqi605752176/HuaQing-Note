#include "exynos_4412.h"


void init_timer()
{

	PWM.TCFG0 = (PWM.TCFG0 & ~(0XFF << 0)) | (99 << 0); // 100M/(99 +1) = 1M
	PWM.TCFG1 = (PWM.TCFG1 & ~(0XF << 0)) | (0B0010 << 0); // timer0 �Ĺ���Ƶ�� 1M / 4 = 250Khz ÿ�����250000 ��


	PWM.TCON = (PWM.TCON & ~(0XF << 0)) | (0B0000 << 0);// RELOAD = 0 UPDATE = 0 START = 0

	PWM.TINT_CSTAT = (PWM.TINT_CSTAT & ~(0B11111 << 5)) | (1 << 0); //����timer4 �ж�

	//37 69  �C  TIMER0
	ICDISR .ICDISR2 &= ~(1 << 7);
	ICDISER .ICDISER2 = (1 << 7);
	ICDIPR .ICDIPR17 = (ICDIPR .ICDIPR17 & ~(0xff << 8)) | (1 << 8); //���ȼ�����Ϊ 1
	
	ICDIPTR .ICDIPTR17 = (ICDIPTR .ICDIPTR17 & ~(0xff << 8))
			| (0b00000001 << 8);	//���ý��ж��͵�icc0

	ICDDCR = 1;  //���� icd
	CPU0 .ICCICR = 1; //ʹ��icc

}

int  key_number;
void start_timer0(int fre)
{
	PWM.TCNTB0 = 250000 / fre - 1; //���������� �� ��1 / 250K�� * 250000 = 1S  ���� timer����1s�������ж�
	PWM.TCMPB0 = 250000 / fre / 2;

	PWM.TCON = (PWM.TCON & ~(0XF << 0)) | (0B0110 << 0);// RELOAD = 1 UPDATE = 1 START = 0
	PWM.TCON = (PWM.TCON & ~(0XF << 0)) | (0B0100 << 0);// RELOAD = 1 UPDATE = 0 START = 0
	PWM.TCON = (PWM.TCON & ~(0XF << 0)) | (0B0001 << 0);// RELOAD = 0 UPDATE = 0 START = 1


}
