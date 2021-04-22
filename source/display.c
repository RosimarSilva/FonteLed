/*
 * display.c
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

uint8_t tela;

/****************************************************************************
 * Faz a leitura dos comandos da serial*********************************
 */
void leituraDisplay(const dataDisplay *data)
{
	uint8_t funcao = 0;
	uint8_t vpointer = 0;
	uint8_t valor = 0;
	if((data->highByte == 0xA5)&&(data->lowByte == 0x5A))
	{
		funcao = data->function;
		vpointer = data->datavp1*256 + data->datavp2;
		valor = data->dataKeyValue1;
		executaFuncao(funcao,vpointer,valor);
	}
}
/****************************************************************************
 ********Verifica qual o comando pedido pelo display*********************************
 */
void executaFuncao(uint8_t data,uint8_t vp,uint8_t value)
{
	dataDisplay dado;
	//uint8_t tela = 0;

	switch(data)
	{
		case 0x83:
		{
			switch(vp)
			{
				case 0x0A: tela = value;break;
			}


		}break;
	}
	 printf("Hello World %d\n", tela);
}

/**************************************************************/
// rotina que manda o display ir para a tela t
/***********************************************************************/
void go_tela(unsigned int t)
{
   unsigned int tent;

   requisicao_f80(t, 0x03);            // vai para tela t
   requisicao_f82(t, 0x0000);         // requisicao de escrita de valor na variavel no endereco vp

   // verificacao da tela no display
   requisicao_f81(0x03);

   tent = 2;
   while ((tela != t) && (tent > 0))
   {

      requisicao_f80(t, 0x03);            // vai para tela t
      requisicao_f82(t, 0x0000);         // requisicao de escrita de valor na variavel no endereco vp

      // verificacao da tela no display
      requisicao_f81(0x03);

      tent--;
   }

}
/****************************************************************************/
// rotina que coloca um valor em um registrador do display
/*********************************************/
void requisicao_f80(unsigned int valor, unsigned char registrador)
{
   unsigned int contbytes;
   unsigned char quociente, resto;      // auxiliares para mandar endereco de 16 bits em dois caracteres de 8 bits
   unsigned int i;       // indice de vetor
   uint8_t frameenv[10];

   uint8_t ch;

   contbytes = 0;

   frameenv[0] = 0xA5;     contbytes++;    // cabecalho
   frameenv[1] = 0x5A;     contbytes++;    // cabecalho
   frameenv[3] = 0x80;     contbytes++;    // funcao
   frameenv[4] = registrador;     contbytes++;    // numero do registrador de tela (0x03)
                                                                       // numero do registrador de brilho (0x01)

   // passagem do valor a ser colocado no display
   if (registrador == 0x03)            // 2 bytes para numero da tela:  0xKKKK
   {
      quociente = valor/256;
      resto = valor%256;

      frameenv[5] = quociente;     contbytes++;
      frameenv[6] = resto;            contbytes++;
   }

   // passagem do valor a ser colocado no display
   if (registrador == 0x01)            // 1 byte para brilho:  0xKK
   {
      quociente = valor/256;
      resto = valor%256;

      frameenv[5] = valor;     contbytes++;
   }


   // envio do numero de bytes subsequentes
   contbytes++;     // byte do frameenv[2]
   frameenv[2] = contbytes - 3;


   i = 0;
   LPUART_WriteBlocking(LPUART0, frameenv, sizeof(frameenv) - 1);
 //  while (contbytes > 0)      // transmite o frame, byte a byte, desde o endereco até o crc
	// while((kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(LPUART0)) &&(contbytes > 0))
   {
	//   LPUART_WriteByte(LPUART0, frameenv[i]);
    //  i++;   contbytes--;

      LPUART_ReadBlocking(LPUART0, &ch, 1);
      LPUART_WriteBlocking(LPUART0, &ch, 1);
   }
}
/****************************************************************************/
// rotina que vai ler um registrador do display
/*********************************************/
void requisicao_f81(unsigned char adress)
{
   unsigned int tentativas;            // tentativas da serial dar certo
   unsigned int contbytes;
   unsigned int i;       // indice de vetor
   uint8_t frameenv[10];

   tentativas = 3;
  // errodisp = 200;
   uint8_t ch;

   while ((tentativas > 0))
   {
     contbytes = 0;        // contador de bytes para calcular crc

     frameenv[0] = 0xA5;     contbytes++;    // cabecalho
     frameenv[1] = 0x5A;     contbytes++;    // cabecalho
     frameenv[3] = 0x81;     contbytes++;    // funcao

     // passagem do endereco a ser lido no display 0xKKKK
     frameenv[4] = adress;     contbytes++;

     // variavel a ser lida está em 8 (1) ou 16 (2) bits
     if (adress == 0x03)  // numero da tela
     {
        frameenv[5] = 0x02;            contbytes++;
     }

     if (adress == 0x01)     // brilho do display
     {
        frameenv[5] = 0x01;            contbytes++;
     }

     // envio do numero de bytes subsequentes
     contbytes++;     // byte do frameenv[2]
     frameenv[2] = contbytes - 3;


     i = 0;
   //  while (contbytes > 0)  // transmite o frame, byte a byte, desde o endereco até o crc
 //   	 while((kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(LPUART0)) &&(contbytes > 0))
     {
  //  	 LPUART_WriteByte(LPUART0, frameenv[i]);
 //       i++;   contbytes--;
     }

    	   LPUART_WriteBlocking(LPUART0, frameenv, sizeof(frameenv) - 1);
    	 //  while (contbytes > 0)      // transmite o frame, byte a byte, desde o endereco até o crc
    		// while((kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(LPUART0)) &&(contbytes > 0))
    	   {
    		//   LPUART_WriteByte(LPUART0, frameenv[i]);
    	    //  i++;   contbytes--;

    	      LPUART_ReadBlocking(LPUART0, &ch, 1);
    	      LPUART_WriteBlocking(LPUART0, &ch, 1);
    	   }


     tentativas--;

   }  //   while ((errodisp != 0) && (tentativas > 0))

}

/****************************************************************************/
// rotina que coloca um valor (value) num endereco pont (vp) do display
/*********************************************/
void requisicao_f82(unsigned int value, unsigned int pont)
{
   unsigned int contbytes;
   unsigned char quociente, resto;      // auxiliares para mandar 16 bits em dois caracteres de 8 bits
   unsigned int i;       // indice de vetor
   uint8_t frameenv[10];
   contbytes = 0;
   uint8_t ch;

   frameenv[0] = 0xA5;     contbytes++;    // cabecalho
   frameenv[1] = 0x5A;     contbytes++;    // cabecalho
   frameenv[3] = 0x82;     contbytes++;    // funcao

   // passagem do endereco a ser escrito no display 0xKKKK
   quociente = pont/256;
   resto = pont%256;

   frameenv[4] = quociente;     contbytes++;
   frameenv[5] = resto;            contbytes++;

   // passagem do valor a ser escrito no display 0xKKKK
   quociente = value/256;
   resto = value%256;

   frameenv[6] = quociente;     contbytes++;
   frameenv[7] = resto;            contbytes++;

   // envio do numero de bytes subsequentes
   contbytes++;     // byte do frameenv[2]
   frameenv[2] = contbytes - 3;



   i = 0;
  // while (contbytes > 0)  // transmite o frame, byte a byte, desde o endereco até o crc
//	   while((kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(LPUART0)) &&(contbytes > 0))
   {
	//  LPUART_WriteByte(LPUART0, frameenv[i]);
  //    i++;   contbytes--;
   }

	   LPUART_WriteBlocking(LPUART0, frameenv, sizeof(frameenv) - 1);
	 //  while (contbytes > 0)      // transmite o frame, byte a byte, desde o endereco até o crc
		// while((kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(LPUART0)) &&(contbytes > 0))
	   {
		//   LPUART_WriteByte(LPUART0, frameenv[i]);
	    //  i++;   contbytes--;

	      LPUART_ReadBlocking(LPUART0, &ch, 1);
	      LPUART_WriteBlocking(LPUART0, &ch, 1);
	   }


}

/****************************************************************************/
// rotina que pede a leitura de uma veriavel no endereco pont do display
/****************************************************************************/
void requisicao_f83(unsigned int pont)
{
   unsigned int tentativas;            // tentativas da serial dar certo
   unsigned int contbytes;
   unsigned char quociente, resto;      // auxiliares para mandar endereco de 16 bits em dois caracteres de 8 bits
   unsigned int i;       // indice de vetor
   uint8_t frameenv[10];
   tentativas = 3;
  // errodisp = 200;
   uint8_t ch;

   while ((tentativas > 0))
   {
     contbytes = 0;        // contador de bytes para calcular crc

     frameenv[0] = 0xA5;     contbytes++;    // cabecalho
     frameenv[1] = 0x5A;     contbytes++;    // cabecalho
     frameenv[3] = 0x83;     contbytes++;    // funcao

     // passagem do endereco a ser lido no display 0xKKKK
     quociente = pont/256;
     resto = pont%256;

     frameenv[4] = quociente;     contbytes++;
     frameenv[5] = resto;            contbytes++;

     // variavel a ser lida está em 16 bits
     frameenv[6] = 0x01;            contbytes++;

     // envio do numero de bytes subsequentes
     contbytes++;     // byte do frameenv[2]
     frameenv[2] = contbytes - 3;

     ///// transmissao do frame


     i = 0;
 //    while (contbytes > 0)  // transmite o frame, byte a byte, desde o endereco até o crc
 //   	 while((kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(LPUART0)) &&(contbytes > 0))
     {
   // 	 LPUART_WriteByte(LPUART0, frameenv[i]);
 //       i++;   contbytes--;
     }

    	   LPUART_WriteBlocking(LPUART0, frameenv, sizeof(frameenv) - 1);
    	 //  while (contbytes > 0)      // transmite o frame, byte a byte, desde o endereco até o crc
    		// while((kLPUART_TxDataRegEmptyFlag & LPUART_GetStatusFlags(LPUART0)) &&(contbytes > 0))
    	   {
    		//   LPUART_WriteByte(LPUART0, frameenv[i]);
    	    //  i++;   contbytes--;

    	      LPUART_ReadBlocking(LPUART0, &ch, 1);
    	      LPUART_WriteBlocking(LPUART0, &ch, 1);
    	   }


      tentativas--;
   }    //   while ((errodisp != 0) && (tentativas > 0))

}


