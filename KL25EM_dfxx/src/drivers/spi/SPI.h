//==============================================================================
//�ļ�����SPI.h
//˵����SPI����ͷ�ļ���
//==============================================================================
#ifndef SPI_H_
#define SPI_H_

#include "common.h"

//�궨�壺����SPI�ںš�
#define SPI_0  0     //SPI0�ڡ�
#define SPI_1  1     //SPI1�ڡ�

#define SPI_baseadd(SPI_nub)  (SPI_MemMapPtr)(0x40076000u+SPI_nub*0x00001000u)
//�������ӻ�ģʽ��

enum spimode
{
	master,
	slave
};

//==============================================================================
//�������ƣ�SPI_init��
//����˵����SPI��ʼ����ͨ�Ų�����BaudRate = BusClock /16.����BusClock��ϵͳʱ�ӡ�
//����������SPI_mode��SPIģʽ��
//       ��SPI_No��Ҫ��ʼ����SPI�ںš�	 
//�������أ�0:��ʼ��ʧ�ܣ�1����ʼ���ɹ���
//==============================================================================
uint_8 SPI_init(uint_8 SPI_No,uint_8 SPI_mode);	

//==============================================================================
//�������ƣ�SPI_sendonebyte.
//����˵����SPI����һ�ֽ����ݡ�
//����������SPI_No�����ںš�
//       ��ch����Ҫ���͵�һ�ֽ����ݡ�
//�������أ�0������ʧ�ܣ�1�����ͳɹ���
//==============================================================================
uint_8 SPI_sendonebyte(uint_8 SPI_No,uint_8 ch);

//==============================================================================
//�������ƣ�SPI_sendstring.
//����˵����SPI�������ݡ�
//����������SPI_No�����ںš�
//       ��*p:�������ݵ��׵�ַ��
//�������أ��ޡ�
//==============================================================================
void SPI_sendstring(uint_8 SPI_No,uint_8 *p);

//==============================================================================
//�������ƣ�SPI_reonebyte.
//����˵����SPI����һ���ֽڵ�����
//����������SPI_No��SPI�ںš�
//�������أ����յ������ݡ�
//==============================================================================
uint_8 SPI_reonebyte(uint_8 SPI_No);

//==============================================================================
//�������ƣ�SPI_receiveN.
//����˵����SPI�������ݡ���n=1ʱ�����ǽ���һ���ֽڵ����ݡ���
//����������SPI_No��SPI�ںš�
//		 : n:Ҫ���յ��ֽڸ�����
//       ��data[]:���յ������ݡ�
// �������أ�1�����ճɹ���
//==============================================================================
uint_8 SPI_receiveN(uint_8 SPI_No,uint_32 n,uint_8 data[]);

//==============================================================================
//�������ƣ�SPI_re_enable_int.
//����˵������SPI�����жϡ�
//����������SPI_No��SPI�ںš�
//�������أ��ޡ�
//==============================================================================
void SPI_re_enable_int(uint_8 SPI_No);

//==============================================================================
//�������ƣ�SPI_re_disable_int.
//����˵�����ر�SPI�����жϡ�
//����������SPI_No��SPI�ںš�
//�������أ��ޡ�
//==============================================================================
void SPI_re_disable_int(uint_8 SPI_No);

#endif