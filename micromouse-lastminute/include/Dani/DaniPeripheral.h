/*
 * Dani.h
 *
 *  Created on: 13 Feb 2015
 *      Author: Daniel
 */
#include "Dani/plib/stm32f10x_usart.h"

#ifndef DANI_DANI_H_
#define DANI_DANI_H_

//balpwm PB1 TIM3_CH4
#define balMotPWM_Pin GPIO_Pin_1
#define balMotPWM_Port GPIOB

//baldir PB0
#define balMotDIR_Pin GPIO_Pin_0
#define balMotDIR_Port GPIOB

//jobbpwm A7 TIM3_CH2
#define jobbMotPWM_Pin GPIO_Pin_7
#define jobbMotPWM_Port GPIOA

//jobbdir A6
#define jobbMotDIR_Pin GPIO_Pin_6
#define jobbMotDIR_Port GPIOA

//jobb LEDek PB13
#define jobbLED_Pin GPIO_Pin_13
#define jobbLED_Port GPIOB

//bal LEDek PD1
#define balLED_Pin GPIO_Pin_1
#define balLED_Port GPIOD

//USART tx PA9
#define USARTtx_Pin GPIO_Pin_9
#define USARTtx_Port GPIOA

//USART rx PA10
#define USARTrx_Pin GPIO_Pin_10
#define USARTrx_Port GPIOA

//buzzer PB15
#define buzzer_Pin GPIO_Pin_15
#define buzzer_Port GPIOB

//analog input PA2;PA3;PA4;PA5
#define AN1_Pin GPIO_Pin_2
#define AN2_Pin GPIO_Pin_3
#define AN3_Pin GPIO_Pin_4
#define AN4_Pin GPIO_Pin_5

#define AN1_Port GPIOA
#define AN2_Port GPIOA
#define AN3_Port GPIOA
#define AN4_Port GPIOA

//I2C SDA PB11
#define I2CSDA_Pin GPIO_Pin_11
#define I2CSDA_Port GPIOB

//I2C SCL PB10
#define I2CSCL_Pin GPIO_Pin_10
#define I2CSCL_Port GPIOB

//I2C INT PB12
#define I2CINT_Pin GPIO_Pin_12
#define I2CINT_Port GPIOB

//USBDM PA11
#define UDBDM_Pin GPIO_Pin_11
#define UDBDM_Port GPIOA

//USBDP PA12
#define UDBDP_Pin GPIO_Pin_12
#define UDBDP_Port GPIOA

void USART1_Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;


        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);

        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pin =  USARTtx_Pin;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(USARTtx_Port, &GPIO_InitStructure);


        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Pin = USARTrx_Pin ;
        GPIO_Init(USARTrx_Port, &GPIO_InitStructure);


        /*
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        */
        USART_InitStructure.USART_BaudRate = 9600;
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

        /* Configure the USART1 */
        USART_Init(USART1, &USART_InitStructure);

        /* Enable USART1 interrupt */
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        //USART_ITConfig(USART1,USART_IT_TXE,ENABLE);

        /* Enable the USART1 */
        USART_Cmd(USART1, ENABLE);
}

void PWMInit(void)
{

}

void Dani_Init(void)
{
	USART1_Init();

}



#endif /* DANI_DANI_H_ */
