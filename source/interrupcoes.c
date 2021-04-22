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
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

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
