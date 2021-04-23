/*
 * configs.h
 *
 *  Created on: 21 de abr de 2021
 *      Author: Rosimar
 */

#ifndef CONFIGS_H_
#define CONFIGS_H_


typedef struct _dataDisplay
{
	uint8_t highByte;
	uint8_t lowByte;
	uint8_t ByteLeght;
	uint8_t function;
	uint8_t datavp1;
	uint8_t datavp2;
	uint8_t dataUnsolved;
	uint8_t dataKeyValue1;
	uint8_t dataKeyValue2;
	uint8_t dataSeven;

	uint8_t byteDisp;

	uint8_t  pontDisp;

}dataDisplay;




void leituraDisplay(const dataDisplay *data);
void executaFuncao(uint8_t data,uint8_t vp,uint8_t value);
void requisicao_f80(unsigned int valor, unsigned char registrador);
void go_tela(unsigned int t);
void requisicao_f80(unsigned int valor, unsigned char registrador);
void requisicao_f81(unsigned char adress);
void requisicao_f82(unsigned int value, unsigned int pont);
void requisicao_f83(unsigned int pont);

void telaUm(void);
void screen(void);
void telaCalendario(void);
void telaSenha(void);
void telaSistemInfo(void);
void telaMenu(void);
void ftm_init(void);
void init_timer_milisecond(void);
void set_dutycycle(uint8_t param);
void delay(void);
//uint8_t tela;

#endif /* CONFIGS_H_ */
