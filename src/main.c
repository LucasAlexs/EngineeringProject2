#include <stdio.h>
#include <stdlib.h>
#include "matrizes/pds_telecom.h"

int main()
{
    const char *filename = "arquivo.txt";

    // Leitura do arquivo e conversão para sequência de inteiros
    int size;
    int *data = tx_data_read(filename, &size);
    if (data == NULL) {
        return 1;
    }

    // Impressão dos dados lidos
    printf("Sequência de inteiros: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    // Escrita dos dados convertidos de volta para o arquivo
    rx_data_write("arquivo_output.txt", data, size);

    // Liberação de memória
    free(data);
    return 0;
}
