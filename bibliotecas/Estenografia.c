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


uchar* scan(){
	uchar *str = NULL;
    uchar caracter = 'a';
    int tamanho = 0;

    printf(">> ");

    while ((caracter = getchar()) != '\n') {
        str = alocarMemoria(str,caracter,tamanho);
        tamanho++;
    }

    return alocarMemoria(str,'\0',tamanho);
}

uchar* criarMensagem() {
	int aux = 1;
	uchar *mensagem = NULL;
    while (aux){
		mensagem = scan();
		printf("\nA string digitada foi: %s\n\n", mensagem);
		printf("Digite 0 se deseja continuar e 1 se deseja reescrever a mensagem\n>>");
		scanf("%d%*c",&aux);
		
		if(aux) {
			free(mensagem);
			limparterminal();
		}
	}

	return mensagem;
}

uchar* dotBmp(uchar* str1,uchar* str2) {
	size_t len0 = 6;
    size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
    size_t len3 = 4;
    char* resultado = (char*)malloc(len0 + len1 + len2 + len3 + 1);
    
    if (resultado == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    strcpy(resultado, "image/");

	strcat(resultado,str2);

    strcat(resultado, str1);

    strcat(resultado, ".bmp");

    return resultado;
}

void hiddeMenssage(){
	bmp_img img;
	int aux;
	enum bmp_error status;

	printf("Digite o nome da foto original:\n");

	uchar* nome = dotBmp(criarMensagem(),"original/");

	status = bmp_img_read (&img, nome);

		if(status != BMP_OK){
			limparterminal();
			printf("%s não foi encontrado\n\n",nome);
			free(nome);
			return;
		}

	limparterminal();
	printf("Digite a mensagem a ser escondida:\n");

	uchar *mensagem = criarMensagem();
	limparterminal();
	
	cripMenssage(&img,mensagem);

	printf("Escolha o nome da foto com a mensagem escondida:\n");

	nome = dotBmp(criarMensagem(),"modificada/");
	limparterminal();

	bmp_img_write (&img, nome);

	printf("\nA mensagem ''%s'' foi escondida na foto %s\n",mensagem,nome);

	free(nome);
    free(mensagem); 
	bmp_img_free (&img);
}

void showMenssage(){
	bmp_img img;
	enum bmp_error status;
	int aux;

	while(1){
		limparterminal();
		printf("Digite o nome da foto com a mensagem escondida:\n");

	uchar* nome = dotBmp(criarMensagem(),"modificada/");
	limparterminal();
	status = bmp_img_read (&img, nome);

		if(status != BMP_OK){
			printf("%s não foi encontrado\n\nEscolha 1 para tentar novamente, e 0 para voltar ao menu\n>>",nome);
			scanf("%d%*c",&aux);
			free(nome);
			if(aux == 0) return;
		}else{
			break;
		}
	}
	uchar *mensagem = NULL;

	mensagem = descripMenssage(&img);
	printf("\n\nMensagem recuperada: %s\n\n", mensagem);

	free(mensagem); 
	bmp_img_free (&img);
}

void exibirMenu() {
    limparterminal();

    printf("=====================================\n");
    printf("|           MENU PRINCIPAL          |\n");
    printf("=====================================\n");
    printf("| 1. Criptografar Mensagem          |\n");
    printf("| 2. Descriptografar Mensagem       |\n");
    printf("| 3. Sair                           |\n");
    printf("=====================================\n");
    printf("| Escolha uma opcao:                |\n");
    printf("=====================================\n");
    printf(">> ");
}