/*
 * Batman.h
 *
 *  Created on: 13 Feb 2015
 *      Author: Daniel
 */

#ifndef BATMAN_BATMAN_H_
#define BATMAN_BATMAN_H_

void Motorproba(void)
{
	TIM_OCInitTypeDef outputChannelInit = {0,};
	    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	    outputChannelInit.TIM_Pulse = 400;
	    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

	    TIM_OC1Init(TIM4, &outputChannelInit);
	    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);


}

#endif /* BATMAN_BATMAN_H_ */
