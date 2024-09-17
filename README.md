# Esteganografia em Imagens BMP

Este projeto implementa um programa de esteganografia em imagens BMP. A esteganografia é a técnica de ocultar uma mensagem dentro de outro conteúdo, neste caso, uma imagem. O programa permite criptografar (esconder) e descriptografar (revelar) mensagens dentro de imagens no formato `.bmp` utilizando a manipulação de bits da imagem.

## Funcionalidades

- **Criptografar uma mensagem**: O programa permite que uma mensagem seja inserida de maneira oculta dentro de uma imagem BMP.
- **Descriptografar uma mensagem**: O programa pode revelar a mensagem oculta de uma imagem BMP.

## Requisitos

- Para compilar o projeto, é necessário ter o GCC (GNU Compiler Collection) instalado.
- As bibliotecas utilizadas no projeto estão localizadas na pasta `bibliotecas`, incluindo a biblioteca `libbmp` que facilita a manipulação de arquivos BMP.

## Estrutura do Projeto

- **main.c**: Arquivo principal do programa que realiza a criptografia e descriptografia das mensagens.
- **bibliotecas/**: Diretório contendo a biblioteca `libbmp` e outros arquivos de suporte.
- **Estenografia.h**: Cabeçalho que define as funções usadas no programa, incluindo a manipulação de bits e funções de criptografia e descriptografia.

## Como Compilar

Para compilar o programa, utilize o comando abaixo. Ele irá compilar o arquivo principal `main.c` e os arquivos necessários na pasta `bibliotecas/`, especificando o caminho das bibliotecas com `-I`.

```bash
gcc main.c bibliotecas/*.c -I"bibliotecas" -o Estenografia
```

## Como Executar
Após a compilação, o arquivo executável será gerado com o nome `Estenografia`. Para rodar o programa, execute o comando abaixo:

```bash
./Estenografia
```

## Observações

- O programa trabalha com imagens no formato `.bmp` e a mensagem a ser escondida pode ser qualquer texto.
- Certifique-se de que a imagem de origem está no formato correto e que o caminho da imagem está sendo fornecido corretamente ao programa.
- Toda string digitada terá uma mensagem de confirmação, se atente a isso.
