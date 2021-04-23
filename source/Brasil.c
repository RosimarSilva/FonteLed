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
#include "configs.h"
#include "fsl_lpuart.h"
#include "fsl_ftm.h"
/* TODO: insert other include files here. */

struct{
	uint8_t tela;
	uint8_t intensidade;
}var;

/* TODO: insert other definitions and declarations here. */

//extern uint8_t tela;
uint8_t m_tela;
bool chu;
int main(void) {

  	/* Init board hardware. */

	//

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    var.tela = 19;
    requisicao_f82(0, 0x0C);

    go_tela(var.tela);

    ftm_init();



    while(1) {

    	screen();
    }
    return 0 ;
}

void screen(void)
{
	switch(var.tela)
	{
		case 19:telaUm();break;
		case 12:telaMenu();break;
		case 25:telaCalendario();break;
		case 14:
		case 15:telaSenha();break;
		case 61:telaSistemInfo();break;
	}
}

void telaUm(void)
{
	go_tela(var.tela);
	while(var.tela == 19)
	{
		if(chu)
		{
			set_dutycycle(var.intensidade);
			chu = 0;
		}

	}
}

void telaMenu(void)
{
	go_tela(var.tela);
	while(var.tela == 12)
	{

	}
}

void telaCalendario(void)
{
	go_tela(var.tela);
	while(var.tela == 25)
	{

	}
}

void telaSenha(void)
{
	go_tela(var.tela);
	while((var.tela == 15)||(var.tela == 14))
	{

	}
}

void telaSistemInfo(void)
{
	go_tela(var.tela);
	while(var.tela == 61)
	{

	}
}


