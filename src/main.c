#include <stdio.h>
#include <stdlib.h>
#include "matrizes/matrizes.h"
#include "matrizes/pds_telecom.h"

int main()
{
    const char* arquivo = "arquivo.txt";
    long tamanho;
    int* vetor = tx_data_read(arquivo, &tamanho);
    if (vetor == NULL) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    printf("Valores retornados:\n");
    for (long i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }

    printf("\n");

    free(vetor);

    return 0;
}
