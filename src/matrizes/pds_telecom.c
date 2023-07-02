#include <stdio.h>
#include <stdlib.h>

int* tx_data_read(const char texto_str[32], long* tamanho_retornado)
{
    void print_binario(unsigned char byte, int* vetor, long* index)
    {
        for (int i = 6; i >= 0; i -= 2)
        {
            int num = ((byte >> i) & 1) + ((byte >> (i + 1)) & 1) * 2;
            vetor[(*index)++] = num;
        }
    }

    FILE* file = fopen(texto_str, "rb");
    if (file == NULL) {
        printf("Erro! O arquivo nao pode ser aberto.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long tamanho = ftell(file);
    rewind(file);
    unsigned char* buffer = (unsigned char*)malloc(tamanho);
    if (buffer == NULL) {
        printf("Erro! Memoria nao pode ser alocada.\n");
        fclose(file);
        return NULL;
    }

    size_t leitura_bytes = fread(buffer, 1, tamanho, file);
    if (leitura_bytes != tamanho) {
        printf("Erro ao ler o arquivo.\n");
        free(buffer);
        fclose(file);
        return NULL;
    }

    int* vetor = (int*)malloc((tamanho * 4) * sizeof(int)); // Cada byte gera 4 dígitos de 2 bits
    if (vetor == NULL) {
        printf("Erro! Memoria nao pode ser alocada.\n");
        free(buffer);
        fclose(file);
        return NULL;
    }

    long index = 0;
    for (long i = 0; i < tamanho; i++) {
        print_binario(buffer[i - 1], vetor, &index);
    }

    free(buffer);
    fclose(file);

    *tamanho_retornado = tamanho * 4;
    return vetor;
}

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
