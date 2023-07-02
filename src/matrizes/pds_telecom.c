#include <stdio.h>
#include <stdlib.h>

int main()
{
    tx_data_read("arquivo2.txt");
}

int tx_data_read(const char texto_str[32])
{
    void print_binario(unsigned char byte)
    {
        for (int i = 6; i >= 0; i -= 2)
        {
            int num = ((byte >> i) & 1) + ((byte >> (i + 1)) & 1) * 2;
            printf("%d", num);
        }
    }

    FILE *file = fopen(texto_str, "rb");
    if (file == NULL) {
        printf("Erro! O arquivo nao pode ser aberto.\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long tamanho = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(tamanho);
    if (buffer == NULL) {
        printf("Erro! Memoria nao pode ser alocada.\n");
        return 1;
    }

    size_t leitura_bytes = fread(buffer, 1, tamanho, file);
    if (leitura_bytes != tamanho) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }

    printf("\n");

    for (long i = 0; i < tamanho - 1; i++) {
        print_binario(buffer[i]);
        printf("");
    }

    printf("\n");

    free(buffer);
    fclose(file);
}
