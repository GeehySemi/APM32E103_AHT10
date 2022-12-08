
#include "main.h"  //������Ҫ��ͷ�ļ�
#include "delay.h"      //������Ҫ��ͷ�ļ�
#include "iic.h"        //������Ҫ��ͷ�ļ�


void SDA_OUT(void)
{
	  GPIO_Config_T gpioConfig;
	  RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC);
	
	
		gpioConfig.pin = GPIO_PIN_0;				
		gpioConfig.mode=GPIO_MODE_OUT_PP ;
		gpioConfig.speed=GPIO_SPEED_50MHz;
		GPIO_Config(GPIOC, &gpioConfig);
}	

void SDA_IN(void)
{
	  GPIO_Config_T gpioConfig;
	  RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC);
	
	
		gpioConfig.pin = GPIO_PIN_0;				
		gpioConfig.mode=GPIO_MODE_IN_PU;
		gpioConfig.speed=GPIO_SPEED_50MHz;
		GPIO_Config(GPIOC, &gpioConfig);
}
/*-------------------------------------------------*/
/*����������ʼ��IIC�ӿ�                            */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void IIC_Init(void)
{			
	  GPIO_Config_T gpioConfig;
	  RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC);
	
	
		gpioConfig.pin = GPIO_PIN_0|GPIO_PIN_1;				
		gpioConfig.mode=GPIO_MODE_OUT_PP ;
		gpioConfig.speed=GPIO_SPEED_50MHz;
		GPIO_Config(GPIOC, &gpioConfig); 
	
	IIC_SCL_H;   //SCL����
	IIC_SDA_H;   //SDA����
}
/*-------------------------------------------------*/
/*��������IIC��ʼ�ź�                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void IIC_Start(void)
{
	SDA_OUT();     //SDA�����ģʽ
    IIC_SDA_H;	   //SDA����  
	IIC_SCL_H;     //SCL����	  
	delay_us(4);   //��ʱ
 	IIC_SDA_L;     //SCL�ߵ�ƽ��ʱ��SDA�ɸߵ��ͣ���ʼ�ź�
}
/*-------------------------------------------------*/
/*��������IICֹͣ�ź�                              */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void IIC_Stop(void)
{
	SDA_OUT();     //SDA�����ģʽ
	IIC_SDA_L;     //SDA����
	IIC_SCL_H;     //SCL����
 	delay_us(4);   //��ʱ
	IIC_SDA_H;     //SCL�ߵ�ƽ��ʱ��SDA�ɵ͵��ߣ�����ֹͣ�ź�					   	
}
/*-------------------------------------------------*/
/*���������ȴ�Ӧ��                                 */
/*��  ������                                       */
/*����ֵ��0���ɹ�  1��ʧ��                         */
/*-------------------------------------------------*/
char IIC_Wait_Ack(void)
{
	unsigned char timeout=0; //����һ�����������ڼ��㳬ʱʱ��
	
	IIC_SDA_H;	             //SDA����
	SDA_IN();                //SDA������ģʽ 
	IIC_SCL_H;	             //SCL����
	 
	while(READ_SDA){         //�ȴ�SDA��͵�ƽ����ʾӦ��������Ȼһֱwhileѭ����ֱ����ʱ	
		timeout++;           //��ʱ����+1
		if(timeout>250){     //�������250	
			IIC_Stop();      //����ֹͣ�ź�
			return 1;        //����1����ʾʧ��
		}
		delay_us(2);         //��ʱ
	}
	IIC_SCL_L;               //SCL����
	delay_us(20);            //��ʱ	
	return 0;                //����0����ʾ�ɹ�
} 	
/*-------------------------------------------------*/
/*������������һ���ֽ�                             */
/*��  ����txd�����͵��ֽ�                          */
/*����ֵ����                                       */
/*-------------------------------------------------*/ 			  
void IIC_Send_Byte(unsigned char txd)
{                        
    unsigned char t;                   //����һ����������forѭ�� 
	
	SDA_OUT(); 	                       //SDA�����ģʽ 
    IIC_SCL_L;                         //SCL���ͣ���ʼ���ݴ���
    for(t=0;t<8;t++){                  //forѭ����һλһλ�ķ��ͣ������λ λ7��ʼ                 
        IIC_SDA_OUT(((txd&0x80)>>7));  //��SDA������
        txd<<=1; 	                   //����һλ��׼����һ�η���
		delay_us(2);                   //��ʱ
		IIC_SCL_H;                     //SCL����
		delay_us(2);                   //��ʱ
		IIC_SCL_L;	                   //SCL����
    }	 
} 	    
/*-------------------------------------------------*/
/*����������ȡһ���ֽ�                             */
/*��  ����ack���Ƿ���Ӧ�� 1:�� 0������           */
/*����ֵ����ȡ������                               */
/*-------------------------------------------------*/   
unsigned char IIC_Read_Byte(unsigned char ack)
{
	unsigned char i;           //����һ����������forѭ�� 
	unsigned char receive;     //����һ���������ڱ�����յ�������
		
	receive = 0;               //���receive��׼����������
	SDA_IN();                  //SDA����Ϊ����
    IIC_SCL_L;                 //SCL����
    delay_us(20);               //��ʱ	
	for(i=0;i<8;i++){          //forѭ����һλһλ�Ķ�ȡ	 
		IIC_SCL_H;             //SCL���� 
		delay_us(20);           //��ʱ
        receive<<=1;           //����һλ��׼���´εĶ�ȡ
        if(READ_SDA)receive++; //��ȡ����
		delay_us(20);           //��ʱ
		IIC_SCL_L;             //SCL����  
		delay_us(20);           //��ʱ 		
    }					 
    if(!ack){        //����Ҫ����
		SDA_OUT();   //SDA�����ģʽ 
		IIC_SDA_H;   //ʱ������ĸߵ�ƽ�ڼ䱣���ȶ��ĸߵ�ƽ
		IIC_SCL_H;   //SCL����
		delay_us(2); //��ʱ
		IIC_SCL_L;   //SCL���� 
	}else{           //��Ҫ����
		SDA_OUT();   //SDA�����ģʽ 
		IIC_SDA_L;   //ʱ������ĸߵ�ƽ�ڼ䱣���ȶ��ĵ͵�ƽ
		IIC_SCL_H;   //SCL����
		delay_us(2); //��ʱ
		IIC_SCL_L;   //SCL����
		IIC_SDA_H;   //SDA����
	}
    return receive;
}