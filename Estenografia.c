#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libbmp.h"

typedef unsigned char uchar;
const char acabou = '$';

uchar mudarBit(uchar byte,uchar menssage, uchar n){
	return (byte & ~1u) | ((menssage >> n) & 1);
}

uchar pegarBit(uchar byte,uchar menssage,uchar n){
	return menssage | ((byte & 1) << n);
}

void limparterminal(){
	#ifdef _WIN32
        system("cls");  // Comando para Windows
    #else
        system("clear");  // Comando para Linux e macOS
    #endif
}

uchar* alocarMemoria(uchar* mensagem, uchar caracter,int indice){
	    uchar *new = realloc(mensagem, (indice + 1) * sizeof(char));
		if(new == NULL) {
			printf("Erro ao alocar memória.\n"); 
            return NULL;
		}
        mensagem = new;
        mensagem[indice] = caracter; 
		return mensagem;
}

void cripMenssage(bmp_img *img, uchar mensagem[]){
	int width = img->img_header.biWidth;
    int height = img->img_header.biHeight;
	int indice = 0 ;
	uchar caracter = mensagem[indice];
	int n =0;
	for (size_t y = 0; y < height; y++){
		for (size_t x = 0; x < width; x++){
			for(int rgb = 0;rgb<3;rgb++){

				if(n==8){
					n=0;
					indice++;

					if(indice < strlen(mensagem)){
						caracter = mensagem[indice];	
						
					}else if((indice == strlen(mensagem))){
						caracter = acabou;
					}else{
						return;
					}
				}

				if(rgb == 0) img->img_pixels[y][x].red = mudarBit(img->img_pixels[y][x].red,caracter,n); 
				if(rgb == 1) img->img_pixels[y][x].green = mudarBit(img->img_pixels[y][x].green,caracter,n);
				if(rgb == 2) img->img_pixels[y][x].blue = mudarBit(img->img_pixels[y][x].blue,caracter,n);
				n++;
			}
		}
	}
}

uchar * descripMenssage(bmp_img *img){
	int width = img->img_header.biWidth;
    int height = img->img_header.biHeight;
	uchar caracter;
	uchar *mensagem = NULL;
	int indice = 0 ;
	int n =0;
	for (size_t y = 0; y < height; y++){
		for (size_t x = 0; x < width; x++){
			for(int rgb = 0;rgb<3;rgb++){

				if(n==8){
					n=0;

					if(caracter == acabou){
						return alocarMemoria(mensagem,'\0',indice);
						
					}else{
						mensagem = alocarMemoria(mensagem,caracter,indice);
						caracter = 0;
						indice++;
					}
				}

				if(rgb == 0) caracter = pegarBit(img->img_pixels[y][x].red,caracter,n); 
				if(rgb == 1) caracter = pegarBit(img->img_pixels[y][x].green,caracter,n);
				if(rgb == 2) caracter = pegarBit(img->img_pixels[y][x].blue,caracter,n);
				n++;
			}
		}
	}
}


uchar* criarMensagem() {
    uchar *str = NULL;
    uchar caracter = 'a';
    int tamanho = 0;

    printf("\nDigite uma mensagem: \n");

     while ((caracter = getchar()) != '\n') {
        str = alocarMemoria(str,caracter,tamanho);
        tamanho++;
    }

    return alocarMemoria(str,'\0',tamanho);
}

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