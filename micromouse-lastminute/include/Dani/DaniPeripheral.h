/*
 * Dani.h
 *
 *  Created on: 13 Feb 2015
 *      Author: Daniel
 */
#include "Dani/plib/stm32f10x_usart.h"
#include "Dani/plib/stm32f10x_adc.h"
#include "Dani/plib/stm32f10x_tim.h"

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

//analog input PA2;PA3;PA4;PA5 adc1;2;3;4
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

uint32_t ADC1ConvertedValue[2] = {0,0};
uint32_t ADC2ConvertedValue[2] = {0,0};


void USART1_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;

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

void MotorInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitStructure.GPIO_Pin = balMotPWM_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(balMotPWM_Port,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = jobbMotPWM_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(jobbMotPWM_Port,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = balMotDIR_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(balMotDIR_Port,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = jobbMotDIR_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(jobbMotDIR_Port,&GPIO_InitStructure);

}
void ADCInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStruct;
	ADC_InitTypeDef ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1| RCC_APB2Periph_ADC2, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//
	//DMA
	//
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) & ADC1->DR; //ADC13's data register
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) & ADC1ConvertedValue;
	//UTÁNANÉZNI
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST; //KURVÁRAJÓKÉRDÉSHOGYJÓE!!!!!
	//UTÁNANÉZNI
	DMA_InitStruct.DMA_BufferSize = 2;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //Reads 16 bit values
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //Stores 16 bit values
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	//DMA_Init(DMA1_Channel1,	&DMA_InitStruct);

	DMA_Init(DMA1_Channel1, &DMA_InitStruct);
	//
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) & ADC2->DR; //ADC13's data register
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) & ADC2ConvertedValue;
	//UTÁNANÉZNI
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST; //KURVÁRAJÓKÉRDÉSHOGYJÓE!!!!!
	//UTÁNANÉZNI
	DMA_InitStruct.DMA_BufferSize = 2;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //Reads 16 bit values
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //Stores 16 bit values
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	//DMA_Init(DMA1_Channel2,	&DMA_InitStruct);
	DMA_Init(DMA1_Channel2, &DMA_InitStruct);
	//
	//ADC
	//
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ExternalTrigConv= 0;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1, &ADC_InitStructure );

	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ExternalTrigConv= 0;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC2,&ADC_InitStructure );

	ADC_RegularChannelConfig(ADC1, ADC_Channel_2,1,ADC_SampleTime_71Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3,2,ADC_SampleTime_71Cycles5);

	ADC_RegularChannelConfig(ADC2, ADC_Channel_4,1,ADC_SampleTime_71Cycles5);
	ADC_RegularChannelConfig(ADC2, ADC_Channel_5,2,ADC_SampleTime_71Cycles5);

	ADC_DMACmd(ADC1, ENABLE);
	ADC_DMACmd(ADC2, ENABLE);

	ADC_Cmd(ADC1, ENABLE);
	ADC_Cmd(ADC2, ENABLE);

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);
}

void PinInit(void) {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    USART1_Init();
    MotorInit();



}

void Dani_Init(void)
{
	PinInit();
	ADCInit();
	MotorInit();
	USART1_Init();
}



#endif /* DANI_DANI_H_ */
