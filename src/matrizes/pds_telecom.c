#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrizes.h"
#include "pds_telecom.h"

int main()
{
   //tx_data_read();

   int Nr = 4, Nt = 4 ,size = 8188, Nstreams,Nqam = 4,est;
    struct Complex *s,*s_mapped, *o;

   if (Nr < Nt) {
        Nstreams = Nr;
    } else {
        Nstreams = Nt;
    }

    int *vector;
    vector = (int *)malloc(size * sizeof(int));

    if (vector == NULL) {
        printf("Erro ao alocar memória para o vetor.\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        vector[i] = i % Nqam;
    }

    printf("Elementos do vetor Etapa1:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");


    s_mapped = (struct Complex *)malloc(Nstreams * sizeof(struct Complex ));
    o = (struct Complex *)malloc(Nt * sizeof(struct Complex ));

    s = tx_qam_mapper(vector,size);

    for (int a = 0; a < size; a+= Nstreams)
    {
        s_mapped = tx_layer_mapper(a,s,s_mapped,Nstreams);

        o = rx_layer_demapper(a,s_mapped,o,Nstreams);
    }

    vector = rx_qam_demapper(o,size);

    printf("Elementos do vetor Etapa2:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");

    est = gera_estatisticas(s,o,size);

    printf(" Número de símbolos QAM transmitidos: %d \n",size);
    printf(" Número de símbolos QAM recebidos com erro: %d \n",est);
    printf(" Porcentagem de símbolos QAM recebidos com erro: %d% \n",est/size);

    free(vector);
    free(s_mapped);

    return 0;
}

int * tx_data_read(FILE* entrada_arquivo, long int q_bytes){

    int * vet_int = (int *)malloc(q_bytes * 4 * sizeof(int));
    if (vet_int == NULL) {
        printf("Erro na alocação de memória\n");
        fclose(entrada_arquivo);
        return (int *)1;
    }

    for (int i = 0; i < q_bytes; i++) {
        char byte;
        fread(&byte, sizeof(byte), 1, entrada_arquivo);

        for (int j = 0; j <= 7; j=j+2) {
            int bit = (byte >> j) & 3;
            vet_int[(i*4) + (j/2)]= bit;
        }

    }

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
        else if (indice[i] == 3){
            symbol[i].real = 1;
            symbol[i].img = -1;
        }
    }

    return symbol;
}

void rx_data_write(int* entrada_vet_int, long int tamanho) {

    tamanho -= 1;

    FILE* binario = fopen("src/matrizes/arquivo.bin", "wb");

    if (binario == NULL) {
        printf("Erro! Arquivo.bin nao pode ser aberto!\n");
        return;

    } else {
        printf("Arquivo.bin gerado com sucesso.\n");
    }

    for (int i = 0; i < tamanho; i++) {

        unsigned char byte = 0;
        for (int j = 0; j < 4; j++)
        {
            unsigned int bit = entrada_vet_int[(i * 4) + j];
            byte |= (bit << (2 * j));
        }
        fwrite(&byte, sizeof(byte), 1, binario);
        }

    fclose(binario);
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

struct Complex *rx_layer_demapper(int a, struct Complex *s_mapped,struct Complex *s, int Nstreams){

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        s[(a) + i ].real = s_mapped[i].real;
        s[(a) + i ].img = s_mapped[i].img ;
    }
    return s;
}

struct Complex *tx_layer_mapper(int a, struct Complex *s,struct Complex *s_mapped, int Nstreams) {

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        s_mapped[i].real = s[(a ) + i ].real;
        s_mapped[i].img = s[(a) + i ].img;
    }
    return s_mapped;
}

struct Complex **channel_gen(int Nr,struct Complex **H, int Nt) {

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

struct Complex **channel_transmission(double rmax, double rmin, struct Complex **mtx_cod, struct Complex **H, int Nr, int Nt){
    struct Complex **rmtx;

    rmtx = produto_matricial( mtx_cod, H, Nr, Nt);

    for (int i = 0; i < Nr; i++) {
        for (int j = 0; j < Nt; j++) {
            rmtx[i][j].real = rmtx[i][j].real + ((double)rand() / RAND_MAX) * (rmax - rmin) + rmin;
            rmtx[i][j].img = rmtx[i][j].img + ((double)rand() / RAND_MAX) * (rmax - rmin) + rmin;
        }
    }

    return rmtx;

}

int gera_estatisticas(struct Complex *s,struct Complex *o, int size){
    int result = 0;

    for (int i = 0; i < size ; i++) {
        if (s[i].real == o[i].real && s[i].img == o[i].img)
            result ++;
    }
    
    return result;
}
