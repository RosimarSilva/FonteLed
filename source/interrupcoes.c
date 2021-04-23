/*
 * interrupcoes.c
 *
 *  Created on: 21 de abr de 2021
 *      Author: Rosimar
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKE15Z4.h"
#include "configs.h"
#include "fsl_lpuart.h"
#include "fsl_ftm.h"
/* TODO: insert other include files here. */


/*******************************************************************************************************************
 * ****************Interrupções da serial do display****************************************************************/

void LPUART0_SERIAL_RX_TX_IRQHANDLER(void){
  /*  Place your code here */
	dataDisplay data;

    if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(LPUART0))
    {

    	switch(data.pontDisp)
    	{
    		case 0: data.highByte = LPUART_ReadByte(LPUART0); break;

    		case 1: data.lowByte = LPUART_ReadByte(LPUART0);break;

    		case 2: {data.ByteLeght = LPUART_ReadByte(LPUART0); data.byteDisp = data.ByteLeght + 3;}break;

    		case 3: data.function = LPUART_ReadByte(LPUART0);break;

    		case 4: data.datavp1 = LPUART_ReadByte(LPUART0);break;

    		case 5: data.datavp2 = LPUART_ReadByte(LPUART0);break;

    		case 6: data.dataUnsolved = LPUART_ReadByte(LPUART0);break;

    		case 7: data.dataKeyValue1 = LPUART_ReadByte(LPUART0);break;

    		case 8: data.dataKeyValue1 = LPUART_ReadByte(LPUART0);break;

    		case 9: data.dataSeven = LPUART_ReadByte(LPUART0);break;

    	}

    	data.pontDisp++;

    	if(data.pontDisp > 3)
    	{
    		if(data.pontDisp == data.byteDisp)
    		{
    			leituraDisplay(&data);
    			data.pontDisp = 0;

    			data.byteDisp = 0;
    		}
    	}


    }

  /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F
     Store immediate overlapping exception return operation might vector to incorrect interrupt. */
  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}
/* FTM1_IRQn interrupt handler */
void FTM0_IRQHANDLER(void) {
  /*  Place your code here */
	int timer;

	if(--timer <= 0)timer = 0;

  #if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
  #endif
}

ftm_config_t ftmInfo;
ftm_chnl_pwm_signal_param_t ftmParam;
uint8_t Dutycycle = 50;
ftm_pwm_level_select_t pwmLevel = kFTM_LowTrue;
void ftm_init(void)
{
    ftmParam.chnlNumber =  kFTM_Chnl_0;
    ftmParam.level = pwmLevel;
    ftmParam.dutyCyclePercent = Dutycycle;
    ftmParam.firstEdgeDelayPercent = 0U;

    FTM_GetDefaultConfig(&ftmInfo);
     /* Initialize FTM module */
     FTM_Init(FTM1, &ftmInfo);

     FTM_SetupPwm(FTM1, &ftmParam, 1U, kFTM_CenterAlignedPwm, 400U, CLOCK_GetFreq(kCLOCK_CoreSysClk));//1U

    FTM_StartTimer(FTM1, kFTM_SystemClock);

}

void init_timer_milisecond(void)// inicializa a interrupção de 1 milissegundo
{
	ftm_config_t  ftmInfo;

	FTM_GetDefaultConfig(&ftmInfo);

	    /* Divide FTM clock by 4 */
	    ftmInfo.prescale = kFTM_Prescale_Divide_4;

	    /* Initialize FTM module */
	    FTM_Init(FTM0, &ftmInfo);

	    /*
	     * Set timer period.
	    */
	    FTM_SetTimerPeriod(FTM0, USEC_TO_COUNT(1000U,CLOCK_GetFreq(kCLOCK_ScgSircClk)/4));

	    FTM_EnableInterrupts(FTM0, kFTM_TimeOverflowInterruptEnable);

	    EnableIRQ(FTM0_IRQn);

	    FTM_StartTimer(FTM0, kFTM_FixedClock);
}

/****************************************************************************/
void set_dutycycle(uint8_t param )
{
	Dutycycle = param;

	  /* Disable channel output before updating the dutycycle */
	FTM_UpdateChnlEdgeLevelSelect(FTM1, kFTM_Chnl_0, 0U);

	            /* Update PWM duty cycle */
	FTM_UpdatePwmDutycycle(FTM1, kFTM_Chnl_0, kFTM_CenterAlignedPwm, Dutycycle);

	            /* Software trigger to update registers */
	FTM_SetSoftwareTrigger(FTM1, true);

	            /* Start channel output with updated dutycycle */
	FTM_UpdateChnlEdgeLevelSelect(FTM1, kFTM_Chnl_0, pwmLevel);

    /* Disable interrupt to retain current dutycycle for a few seconds */
   //  FTM_DisableInterrupts(FTM1, kFTM_Chnl0InterruptEnable);

     /* Disable channel output before updating the dutycycle */
  //   FTM_UpdateChnlEdgeLevelSelect(FTM1, kFTM_Chnl_0, 0U);

     /* Update PWM duty cycle */
  //   FTM_UpdatePwmDutycycle(FTM1, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, Dutycycle);

     /* Software trigger to update registers */
 //    FTM_SetSoftwareTrigger(FTM1, true);

     /* Start channel output with updated dutycycle */
 //    FTM_UpdateChnlEdgeLevelSelect(FTM1, kFTM_Chnl_0, pwmLevel);

     /* Delay to view the updated PWM dutycycle */
     delay();
     delay();
     delay();
     delay();

     /* Enable interrupt flag to update PWM dutycycle */
  //   FTM_EnableInterrupts(FTM1, kFTM_Chnl0InterruptEnable);
	//delay();
}

void delay(void)
{
    volatile uint32_t i = 0U;
    for (i = 0U; i < 80000U; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

