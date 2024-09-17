#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libbmp.h"
#include "Estenografia.h"

int main (int argc, char *argv[]) {
    int opcao;
    char aux;

    while (1) {
        exibirMenu();
        
        scanf("%d%*c", &opcao);

        switch (opcao) {
            case 1:
                limparterminal();
                printf("\nVoce escolheu criptografar uma mensagem.\n\n");
                hiddeMenssage();
                printf("De enter para volar ao menu");
                scanf("%*c",&aux);
                break;
            case 2:
                limparterminal();
                printf("\nVoce escolheu descriptografar uma mensagem.\n\n");
                showMenssage();
                printf("De enter para volar ao menu");
                scanf("%*c",&aux);
                break;
            case 3:
                limparterminal();
                printf("\nSaindo do programa...\n\n");
                exit(0);
            default:
                printf("\nOpcao invalida! Tente novamente.\n\n");
        }
    }

	return 0;
}