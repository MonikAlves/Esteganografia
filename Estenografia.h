#ifndef __ESTENOGRAFIA_H__
#define __ESTENOGRAFIA_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libbmp.h"

typedef unsigned char uchar;

uchar mudarBit(uchar byte,uchar menssage, uchar n);
uchar pegarBit(uchar byte,uchar menssage,uchar n);
void limparterminal();
uchar* alocarMemoria(uchar* mensagem, uchar caracter,int indice);
void cripMenssage(bmp_img *img, uchar mensagem[]);
uchar * descripMenssage(bmp_img *img);
uchar* criarMensagem();
void hiddeMenssage();
void showMenssage();
void exibirMenu();

#endif