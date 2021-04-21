/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    Brasil.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKE15Z4.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */

/* LPUART0_IRQn interrupt handler */

/* LPUART0_IRQn interrupt handler */
uint8_t brasil[10];
uint8_t i,pont = 0,finally;
uint8_t rec,j;

typedef struct _dataDisplay
{
	uint8_t highByte;
	uint8_t lowByte;
	uint8_t ByteLeght;
	uint8_t dataOne;
	uint8_t dataTwo;
	uint8_t dataThree;
	uint8_t dataFour;
	uint8_t dataFive;
	uint8_t dataSix;
	uint8_t dataSeven;

	uint8_t byteDisp;

}dataDisplay;

uint8_t  pontDisp;

void LPUART0_SERIAL_RX_TX_IRQHANDLER(void) {
  /*  Place your code here */
	dataDisplay data;

    if ((kLPUART_RxDataRegFullFlag)&LPUART_GetStatusFlags(LPUART0))
    {

    	switch(pontDisp)
    	{
    		case 0: data.highByte = LPUART_ReadByte(LPUART0); break;

    		case 1: data.lowByte = LPUART_ReadByte(LPUART0);break;

    		case 2: {data.ByteLeght = LPUART_ReadByte(LPUART0); data.byteDisp = data.ByteLeght + 3;}break;

    		case 3: data.dataOne = LPUART_ReadByte(LPUART0);break;

    		case 4: data.dataTwo = LPUART_ReadByte(LPUART0);break;

    		case 5: data.dataThree = LPUART_ReadByte(LPUART0);break;

    		case 6: data.dataFour = LPUART_ReadByte(LPUART0);break;

    		case 7: data.dataFive = LPUART_ReadByte(LPUART0);break;

    		case 8: data.dataSix = LPUART_ReadByte(LPUART0);break;

    		case 9: data.dataSeven = LPUART_ReadByte(LPUART0);break;

    	}

    	pontDisp++;

    	if(pontDisp > 3)
    	{
    		if(pontDisp == data.byteDisp)
    		{
    			pontDisp = 0;

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

int main(void) {
  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    printf("Hello World\n");

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}


