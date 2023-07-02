#include <stdio.h>
#include <stdlib.h>
#include "pds_telecom.h"
//#include "matrizes.c"


// Função para converter um caractere hexadecimal em um número decimal
int hex_to_dec(char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    } else if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10;
    }
    return -1;  // Caractere hexadecimal inválido
}

// Função para converter uma sequência hexadecimal em uma sequência de inteiros de 0 a 3
int *tx_data_read(const char *filename, int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Cada byte é representado por 2 caracteres hexadecimais
    *size = fileSize / 2;
    int *data = (int *)malloc(*size * sizeof(int));

    char hex[3];
    hex[2] = '\0';
    for (int i = 0; i < *size; i++) {
        if (fread(hex, 1, 2, file) != 2) {
            printf("Erro ao ler o arquivo.\n");
            free(data);
            fclose(file);
            return NULL;
        }
        int decimal = (hexToDecimal(hex[0]) << 4) | hexToDecimal(hex[1]);
        data[i] = decimal % 4;
    }

    fclose(file);
    return data;
}

// Função para converter uma sequência de inteiros de 0 a 3 em uma sequência hexadecimal
void rx_data_write(const char *filename, const int *data, int size) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    char hex[3];
    hex[2] = '\0';
    for (int i = 0; i < size; i++) {
        int decimal = data[i] % 4;
        hex[0] = (decimal >> 4) & 0xF;
        hex[1] = decimal & 0xF;
        if (fwrite(hex, 1, 2, file) != 2) {
            printf("Erro ao escrever no arquivo.\n");
            fclose(file);
            return;
        }
    }

    fclose(file);
}
