#ifndef __ESTENOGRAFIA_H__
#define __ESTENOGRAFIA_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libbmp.h"

typedef unsigned char uchar;
const char acabou = '$';

uchar mudarBit(uchar byte,uchar menssage, uchar n);

uchar pegarBit(uchar byte,uchar menssage,uchar n);

void limparterminal();

uchar* alocarMemoria(uchar* mensagem, uchar caracter,int indice);

void cripMenssage(bmp_img *img, uchar mensagem[]);

uchar * descripMenssage(bmp_img *img);

uchar* criarMensagem();

int main (int argc, char *argv[]) {
	int aux = 1;
	bmp_img img;
	bmp_img_read (&img, "bob.bmp");
	uchar *mensagem = NULL;

    while (aux){

		mensagem = criarMensagem();
		printf("\nA string digitada foi: %s\n", mensagem);
		printf("Digite 0 se deseja continuar e 1 se deseja reescrever a mensagem\n");
		scanf("%d%*c",&aux);

		if(aux) {
			free(mensagem);
			limparterminal();
		}
	}
	
	cripMenssage(&img,mensagem);
    
	bmp_img_write (&img, "test.bmp");
	printf("\nA mensagem ''%s'' foi escondida\n",mensagem);
    free(mensagem); 
	
	bmp_img_read (&img, "test.bmp");

	mensagem = descripMenssage(&img);
	printf("\n\nMensagem recuperada: %s\n", mensagem);
	// printf("%s",teste);

	free(mensagem); 
	bmp_img_free (&img);
	return 0;
}







#endif