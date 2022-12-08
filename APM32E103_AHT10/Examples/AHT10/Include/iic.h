/*-------------------------------------------------*/
/*            ��γ����STM32ϵ�п�����              */
/*-------------------------------------------------*/
/*                                                 */
/*            ʵ��IIc���߹��ܵ�Դ�ļ�              */
/*                                                 */
/*-------------------------------------------------*/

#ifndef __IIC_H
#define __IIC_H
  		   
    
#define READ_SDA        GPIO_ReadInputBit(GPIOC,GPIO_PIN_0)       //��ȡSDA 
#define IIC_SDA_OUT(x)  GPIO_WriteBitValue(GPIOC,GPIO_PIN_0,x) //����SDA��ƽ 

#define	IIC_SCL_H    GPIO_SetBit(GPIOC,GPIO_PIN_1)    //SCL����
#define	IIC_SDA_H    GPIO_SetBit(GPIOC,GPIO_PIN_0)    //SDA����

#define	IIC_SCL_L    GPIO_ResetBit(GPIOC,GPIO_PIN_1)  //SCL����
#define	IIC_SDA_L    GPIO_ResetBit(GPIOC,GPIO_PIN_0)  //SDA����

void SDA_IN(void);       
void SDA_OUT(void);  
void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
char IIC_Wait_Ack(void);
void IIC_Send_Byte(unsigned char);
unsigned char IIC_Read_Byte(unsigned char);

#endif
















