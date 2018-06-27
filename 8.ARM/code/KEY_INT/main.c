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
	printf("key2");
	//����ж�Դ
	EXT_INT41_PEND = (1 << 1);
	//����жϿ�����״̬
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3FF) | irq_number;
}

int main(void)
{
	/*
	 *Config
	 */
	//KEY2��ʼ��
	//KEY2 = GPX1_1 �ⲿ�ж�ģʽEXT_INT41[1]

	//GPX1CON[1]4λ��0��������Ϊ�ⲿ�ж�ģʽ
	GPX1.CON = (GPX1.CON & ~(0xF << 4)) | (0xF << 4);

	//����EXT_INT41[1]���ⲿ�ж�
	EXT_INT41_CON = (EXT_INT41_CON & ~(0xF << 4)) | (0x2 << 4);
	//�����˲�
	EXT_INT41_FLTCON0 |= 1 << 15;
	//��ʱ�˲�
	EXT_INT41_FLTCON0 &= ~(1 << 14);
	//ʹ���ж�
	EXT_INT41_MASK &= ~(1 << 1);

	//�����ж�ICD ICC ,�ж�ID 57
	//�ж�ʹ��
	ICDDCR = 1;
	//�жϰ�ȫ ICDISR1�ĵ�25λ
	ICDISR.ICDISR1 &= ~(1 << 25);
	ICDISER.ICDISER1 |= (1 << 25);
	//�ж����ȼ�
	ICDIPR.ICDIPR14 = (ICDIPR.ICDIPR14 & ~(0xFF << 8)) | (1 << 8);
	//ѡ���ж�CPU
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & ~(0xFF << 8)) | (0b00000001 << 8);
	//�ж�����

	//ʹ��ICC
	CPU0.ICCICR = 1;


	/****************************************************/
	while (1);
	return 0;
}
