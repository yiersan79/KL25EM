//============================================================================
// �ļ����ƣ�lcd.c
// ���ܸ�Ҫ��lcd����Դ�ļ�
// ��Ȩ����: ���ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
// �汾����:     ʱ��                     �汾                                       �޸�
//           2012-11-17     V1.0       ��д��KL25��lcd����
//============================================================================
#include "lcd.h"
//���������������������ʾ��ʹ���ӵ�����
uint_8 LcdData[8]={PORTD,PORTD,PORTD,PORTD,PORTD,
		               PORTC ,PORTC ,PORTC };
//���ݿڷֱ��PTD,PTC��{4,3,2,1,0,17,16,13}��,�������Ӧ
uint_8 LCD_D[8]= {4,3,2,1,0,17,16,13};

//�ڲ�����ԭ��˵��
extern void LCDCommand(uint_8 cmd);

//============================================================================
//�������ƣ�LCDInit
//�������أ���
//����˵������
//���ܸ�Ҫ��LCD��ʼ����
//============================================================================
void LCDInit()
{
    uint_32 i = 0;
    //�������ݿ�Ϊ���
    for(i = 0;i < 8;i++)
    {
        gpio_init(LcdData[i], LCD_D[i], 1,0);
    }
    //������ƿ�Ϊ���
    gpio_init (LcdControl, LCDRS, 1,0);
    gpio_init (LcdControl, LCDRW, 1,0);
    gpio_init (LcdControl, LCDE, 1,0);

    //����ָ��,RS,R/W = 00, дָ�����
    gpio_set (LcdControl, LCDRS, 0);
    gpio_set (LcdControl, LCDRW, 0);

    //��������-
    //����ָ��
    LCDCommand(0x38);       //5*7����ģʽ,2����ʾ,8λ��������
    LCDCommand(0x08);       //����ʾ,�ع����ʾ,����˸
    LCDCommand(0x01);       //����
    for (i=0; i<40000; i++); //��ʱ>1.6ms
    LCDCommand(0x06);
    LCDCommand(0x14);       //�������һ���ַ�λ,AC�Զ���1
    LCDCommand(0x0C);       //����ʾ,�ع����ʾ,����˸
}

//============================================================================
//�������ƣ�LCDShow
//�������أ���
//����˵������Ҫ��ʾ������
//���ܸ�Ҫ��Һ����ʾdata�е����ݡ�
//============================================================================
void LCDShow(uint_8 data[32])
{
    uint_8 i;
    //LCD��ʼ��
    LCDInit();

    //��ʾ��1��16���ַ�
    gpio_set (LcdControl, LCDRS, 0);
    gpio_set (LcdControl, LCDRW, 0);
    //��7λΪDD RAM��ַ(0x00)
    LCDCommand(0x80);

    //2.2д16�����ݵ�DD RAM
    gpio_set (LcdControl, LCDRS, 1);
    gpio_set (LcdControl, LCDRW, 0);
    //��Ҫ��ʾ�ڵ�1���ϵ�16���������д��DD RAM��
    for (i = 0;i < 16;i++)
    {
    	LCDCommand(data[i]);
    }

    //��ʾ��2��16���ַ�
    gpio_set (LcdControl, LCDRS, 0);
    gpio_set (LcdControl, LCDRW, 0);
    //��7λΪDD RAM��ַ(0x40)
    LCDCommand(0xC0);

    gpio_set (LcdControl, LCDRS, 1);
    gpio_set (LcdControl, LCDRW, 0);

    //��Ҫ��ʾ�ڵ�2���ϵ�16���������д��DD RAM��
    for (i = 16;i < 32;i++)
    {
    	LCDCommand(data[i]);
    }

}

//----------------����LCDCommand���õ��ڲ��ӳ��ӳ���----------------------*
void Delay40us();
void Delay12NOP();

//============================================================================
//�������ƣ�LCDCommand
//�������أ���
//����˵����cmd:��ִ�е�����
//���ܸ�Ҫ��ִ�и�����cmd����,����ʱ��
//============================================================================
void LCDCommand(uint_8 cmd)
{
	uint_8 i = 0;
    //1.�ȴ� > 40us
    Delay40us();
    //2.�����͵�LCD����������
    for(i = 0;i < 8;i++)
    {
    	gpio_set (LcdData[i], LCD_D[i], 0);
    }

    for(i = 0;i < 8;i++)
    {
    	if(0x01 & (cmd>>i))
    	{
    		gpio_set (LcdData[i], LCD_D[i],1);
    	}
    	else
    	{
    		gpio_set (LcdData[i], LCD_D[i],0);
    	}
    }

    //3.����E�źŵ��½���(�ȸߺ��),ʹ����д��LCD
    gpio_set (LcdControl, LCDE, 1);
    Delay12NOP();
    gpio_set (LcdControl, LCDE, 0);
    //4.�ȴ� > 40us
    Delay40us();
}

//============================================================================
//�������ƣ�Delay40us
//�������أ���
//����˵����cmd:��ִ�е�����
//���ܸ�Ҫ����ʱ>40us ��
//============================================================================

void Delay40us()
{
    uint_16 i;
    for (i=0; i<1600; i++);
}

//============================================================================
//�������ƣ�Delay12NOP
//�������أ���
//����˵������
//���ܸ�Ҫ����ʱ ��
//============================================================================
void Delay12NOP()
{
    uint_8 i;
    for (i=0;i<25;i++) asm("NOP");
}