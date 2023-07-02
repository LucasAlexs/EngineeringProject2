#include <stdio.h>
#include <stdlib.h>
//#include "matrizes.c"

void tx_data_read()
{
    char texto_str[128];
    FILE *pont_arq, *ptarq;
    printf("Digite o Nome do Arquivo: ");
    gets(texto_str);
    pont_arq = fopen(texto_str, "a");
    ptarq = fopen ("src/matrizes/binario.bin", "wb");
    fclose(pont_arq);

    if (pont_arq == NULL)
    {
        printf("ERRO! O arquivo não foi aberto!\n");
    }
    else
    {
        printf("O arquivo foi aberto com sucesso!\n");
    }

    pont_arq = fopen(texto_str, "r");

    printf("---------- Conteudo do Arquivo: ----------\n\n");
    while(fgets(texto_str, 128, pont_arq) != NULL)
    {
        printf("%s", texto_str);
        fclose(pont_arq);
    }
    printf("\n------------------------------------------\n\n");

}
