#include <stdio.h>
#include <stdlib.h>
//#include "matrizes.c"

void main()
{
    char texto_str[1024];
    FILE *pont_arq, *ptarq;
    pont_arq = fopen("arquivo.txt", "a");
    ptarq = fopen ("binario.bin", "wb");
    fclose(pont_arq);

    printf("Arquivo criado!\n");

    if (pont_arq == NULL){
    printf("ERRO! O arquivo não foi aberto!\n");
    }
    else{
    printf("O arquivo foi aberto com sucesso!\n");
    }

    pont_arq = fopen("arquivo.txt", "r");
    printf("---------- Conteudo do Arquivo: ----------\n\n");
    while(fgets(texto_str, 1024, pont_arq) != NULL){
    printf("%s", texto_str);
    fclose(pont_arq);
    }
    printf("\n\n------------------------------------------\n\n");

    if (ptarq!=NULL)
    printf ("\n\n Arquivo binario.bin foi aberto com sucesso \n");
    else {
    printf ("\n\n Erro: O arquivo binario.bin não foi aberto \n");
    system ("pause");
    exit (0);}

    fwrite (texto_str, sizeof (char), 1024, ptarq);
}
