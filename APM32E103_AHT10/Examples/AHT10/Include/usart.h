#ifndef __USART_H
#define __USART_H
#include "main.h"

/** printf function configs to USART1*/
#define DEBUG_USART  USART1

void USART_Init(uint32_t baud);
void USART_Write(uint8_t *dat, uint8_t len);




#endif
