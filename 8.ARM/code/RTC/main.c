/*
 *@brief	This example describes how to use GPIO to drive LEDs
 *@date:	02. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"


/**********************************************************************
 * @brief		mydelay_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int ms)
{
	int i, j;
	while(ms--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}

void do_irq()
{
	//��ȡ�жϺţ�֪ͨCPU�����жϺ���
	int irq_number;
	irq_number = CPU0.ICCIAR & 0x3FF;
	printf("%d\n",irq_number);

	//����ж�Դ
	RTCINTP = 1 << 1;
	//����жϿ�����״̬
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3FF) | irq_number;

}


/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	/*
	 *Config
	 */

	//ʹ��RTC����
	RTCCON = 1 << 0;

	//ʹ��RTCALARM һ��������
	RTCALM.ALM = 1 << 0 | 1 << 6;

	//��ʼ��ʱ��������

	RTCALM.SEC = 0X30;
;

	//�ж�ԴID  76
	//-----------------------�����жϿ�����
	ICDDCR = 1;							//�ж�ʹ��
	ICDISR.ICDISR2 &= ~(1 << 12);		//��ȫģʽ
	ICDISER.ICDISER2 |= (1 << 12);
	ICDIPR.ICDIPR19 = (ICDIPR.ICDIPR19 & ~(0XFF)) | (1 << 0);	//�ж����ȼ�
	ICDIPTR.ICDIPTR19 = (ICDIPTR.ICDIPTR19 & ~(0XFF)) | (0B00000001 << 0);
	CPU0.ICCICR = 1;	//ʹ��ICC


	while(1)
	{


	}
	return 0;
}
