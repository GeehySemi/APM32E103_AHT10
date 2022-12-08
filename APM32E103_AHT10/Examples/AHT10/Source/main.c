/*!
 * @file        main.c
 *
 * @brief       Main program body
 *
 * @version     V1.0.1
 *
 * @date        2022-07-29
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "main.h"
#include "delay.h"
#include "usart.h"
#include "aht10.h"
#include "iic.h"

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 */
int main(void)
{
    double temp,humi;
	  delay_init();
    USART_Init(9600);
	  IIC_Init();
    if(AHT10_Init()){	              
		while(1){
			printf("AHT10 init failure \r\n");    
			delay_ms(500);                             
		}
	}else printf("AHT10 init success\r\n\r\n");    
		
	while(1)                                           
	{
	    AHT10_Data(&temp,&humi);                       
		printf("temp:%.2f ",temp);           
		printf("humi:%.2f %%\r\n",humi);           
		
		delay_ms(500);                                
	}
}



/**@} end of group GPIO_Toggle_Functions */
/**@} end of group GPIO_Toggle */
/**@} end of group Examples */
