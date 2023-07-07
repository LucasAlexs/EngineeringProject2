#include <stdio.h>
#include <stdlib.h>
#include "pds_telecom.h"
#include "matrizes.h"
#include <time.h>


int main()
{
    const char* arquivo = "src/matrizes/arquivo.txt";
    long tamanho;
    int* vet_int = tx_data_read(arquivo, &tamanho);
    struct Complex *vetor_c;
    if (vet_int == NULL) {
        printf("Erro ao ler o arquivo.\n");
        return 1;
    }


    printf("\nValores retornados:\n");
    for (long i = 0; i < tamanho; i++) {
        printf("%d", vet_int[i]);
    }


    vetor_c = tx_qam_mapper(vet_int, tamanho);

    printf("\nComplexos retornados:\n");
    for (long i = 0; i < tamanho; i++) {
        printf("%.2f\t %.2f\n ", vetor_c[i].real, vetor_c[i].img);
    }

    printf("\n");

    free(vet_int);

    return 0;
}

void print_binario(unsigned char byte, int* vet_int, long int* index) {
    for (int i = 6; i >= 0; i -= 2) {
        int num = ((byte >> i) & 1) + ((byte >> (i + 1)) & 1) * 2;
        vet_int[(*index)++] = num;
    }
}

int* tx_data_read(const char* texto_str, long* tamanho_retornado) {
    FILE* file = fopen(texto_str, "rb");
    if (file == NULL) {
        printf("Erro! O arquivo não pode ser aberto.\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long tamanho = ftell(file);
    rewind(file);
    unsigned char* buffer = (unsigned char*)malloc(tamanho);
    if (buffer == NULL) {
        printf("Erro! Memória não pode ser alocada.\n");
        fclose(file);
        return NULL;
    }

    size_t leitura_bytes = fread(buffer, 1, tamanho, file);
    if (leitura_bytes != tamanho) {
        printf("Erro ao ler o arquivo.\n");
        free(buffer);struct Complex *tx_layer_mapper(int a, struct Complex *s, struct Complex **s_mapped, int Nstreams) {
    // Aloca memória para s_mapped
    *s_mapped = (struct Complex *)malloc(Nstreams * sizeof(struct Complex));
    if (*s_mapped == NULL) {
        printf("Erro ao alocar memória para s_mapped\n");
    }

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        (*s_mapped)[i].real = s[a * Nstreams + i].real;
        (*s_mapped)[i].img = s[a * Nstreams + i].img;
    }
    return *s_mapped;
}

struct Complex *rx_layer_demapper(int a, struct Complex **s_mapped, int Nstreams) {
    // Aloca memória para s_mapped
    struct Complex *s;
    s = (struct Complex *)malloc(Nstreams * sizeof(struct Complex));
    if (*s_mapped == NULL) {
        printf("Erro ao alocar memória para s_mapped\n");
    }

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        s[a * Nstreams + i].real = (*s_mapped)[i].real;
        s[a * Nstreams + i].img = (*s_mapped)[i].img ;
    }
    return s;
}
        fclose(file);
        return NULL;
    }

    int* vet_int = (int*)malloc((tamanho * 4) * sizeof(int)); // Cada byte gera 4 dígitos de 2 bits
    if (vet_int == NULL) {
        printf("Erro! Memória não pode ser alocada.\n");
        free(buffer);
        fclose(file);
        return NULL;
    }

    long int index = 0;
    for (long i = 0; i < tamanho; i++) {
        print_binario(buffer[i - 1], vet_int, &index);
    }

    free(buffer);
    fclose(file);

    *tamanho_retornado = tamanho * 4;
    return vet_int;
}
struct Complex *tx_qam_mapper(int* indice, int size) {
    struct Complex *symbol;

    symbol = (struct Complex*)malloc(size * sizeof( struct Complex ));

    for (int i = 0; i < size; i++) {
        if (indice[i] == 0){
            symbol[i].real = -1;
            symbol[i].img = 1;
        }
        else if (indice[i] == 1){
            symbol[i].real = -1;
            symbol[i].img = -1;
        }
        else if (indice[i] == 2){
            symbol[i].real = 1;
            symbol[i].img = 1;
        }
        else if (indice[i] == 2){
            symbol[i].real = 1;
            symbol[i].img = -1;
        }
    }

    return symbol;
}

int *rx_qam_demapper(struct Complex * symbol,int size){

    int *indice;

    indice = (int*)malloc(size * sizeof( int ));

    for (int i = 0; i < size; i++) {
        if (symbol[i].real == -1 && symbol[i].img == 1){
            indice[i] = 0;
        }
        else if (symbol[i].real == -1 && symbol[i].img == -1){
            indice[i] = 1;
        }
        else if (symbol[i].real == 1 && symbol[i].img == 1){
            indice[i] = 2;
        }
        else if (symbol[i].real == 1 && symbol[i].img == -1){
            indice[i] = 3;
        }
    }

    return indice;
}

//rx_data_write(int* entrada_vet_int){
//}

struct Complex *tx_layer_mapper(int a, struct Complex *s, struct Complex **s_mapped, int Nstreams) {
    // Aloca memória para s_mapped
    *s_mapped = (struct Complex *)malloc(Nstreams * sizeof(struct Complex));
    if (*s_mapped == NULL) {
        printf("Erro ao alocar memória para s_mapped\n");
    }

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        (*s_mapped)[i].real = s[a * Nstreams + i].real;
        (*s_mapped)[i].img = s[a * Nstreams + i].img;
    }
    return *s_mapped;
}

struct Complex *rx_layer_demapper(int a, struct Complex **s_mapped, int Nstreams) {
    // Aloca memória para s_mapped
    struct Complex *s;
    s = (struct Complex *)malloc(Nstreams * sizeof(struct Complex));
    if (*s_mapped == NULL) {
        printf("Erro ao alocar memória para s_mapped\n");
    }

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        s[a * Nstreams + i].real = (*s_mapped)[i].real;
        s[a * Nstreams + i].img = (*s_mapped)[i].img ;
    }
    return s;
}
struct Complex **channel_gen(int Nr, int Nt) {
    //Lembrete: não esquecer de desalocar mémoria, um dos três falou pra tomar cuidado.
    // Aloca memória para a matriz de ponteiros
    struct Complex **H = (struct Complex **)malloc(Nr * sizeof(struct Complex *));

    // Aloca memória para as linhas da matriz
    for (int i = 0; i < Nr; i++) {
        H[i] = (struct Complex *)malloc(Nt * sizeof(struct Complex));
    }

    // Gera os valores aleatórios para a matriz H
    srand(time(NULL));  // Inicializa a semente do gerador de números aleatórios

    for (int i = 0; i < Nr; i++) {
        for (int j = 0; j < Nt; j++) {
            H[i][j].real = ((double)rand() / RAND_MAX) * 2 - 1;  // Números aleatórios entre -1 e 1
            H[i][j].img = ((double)rand() / RAND_MAX) * 2 - 1;
        }
    }
     
    return H;
}
