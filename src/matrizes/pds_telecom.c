#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include "pds_telecom.h"
#include <time.h>

int main(){

    FILE *arquivo_txt;
    arquivo_txt = fopen("src/matrizes/arquivo.txt", "rb");

    fseek(arquivo_txt, 0, SEEK_END);
    long int q_bits = ftell(arquivo_txt);
    fseek(arquivo_txt, 0, SEEK_SET);

    int *vetor = tx_data_read(arquivo_txt, q_bits);
    fclose(arquivo_txt);
    return 0;
    //Quantidade de bits

    //rx_data_write(vetor, q_bits, "arquivo.bin");



//    int Nr = 4,Nt = 4;
//    struct Complex **H,**J,**K;
//    double rmax=0,rmin=0;
//    srand(time(NULL));
//
//    H = (struct Complex **)malloc(Nr * sizeof(struct Complex *));
//    J = (struct Complex **)malloc(Nr * sizeof(struct Complex *));
//
//    for (int i = 0; i < Nr; i++)
//    {
//        H[i] = (struct Complex *)malloc(Nt * sizeof(struct Complex));
//        J[i] = (struct Complex *)malloc(Nt * sizeof(struct Complex));
//    }
//
//    H = channel_gen(Nr,H, Nt);
//
//    printf("matriz H:\n");
//
//    for(int i=0; i<Nr; i++){
//        for(int j=0; j<Nt; j++){
//            printf("%.2f + %.2fj\t", H[i][j].real, H[i][j].img);
//        }
//        printf("\n");
//    }
//
//    J = channel_gen(Nr,J, Nt);
//
//    printf("matriz J:\n");
//
//    for(int i=0; i<Nr; i++){
//        for(int j=0; j<Nt; j++){
//            printf("%.2f + %.2fj\t", J[i][j].real, J[i][j].img);
//        }
//        printf("\n");
//    }
//
//    K = channel_transmission(rmax,rmin,J,H,Nr,Nt);
//
//    printf("matriz K:\n");
//
//    for(int i=0; i<Nr; i++){
//        for(int j=0; j<Nt; j++){
//            printf("%.2f + %.2fj\t", K[i][j].real, K[i][j].img);
//        }
//        printf("\n");
//    }
//
//    for (int i = 0; i < Nr; i++){
//            free(H[i]);
//            free(J[i]);
//        }
//        free(H);
//        free(J);
//
//
//        return 0;
}

int * tx_data_read(FILE *texto_str, long int tamanho_retornado) { //long*

    // Alocacão de memoria
    int *vet_int = (int *)malloc(tamanho_retornado * 4 * sizeof(int));
    if (vet_int == NULL) {
        printf("Erro na alocação de memória\n");
        fclose(texto_str);
        return (int *)1;
    }

    // Converte os bytes em inteiros de 2 bits
    for (int i = 0; i < tamanho_retornado; i++)
        {
            char byte;
            fread(&byte, sizeof(byte), 1, texto_str);

            for (int j = 0; j <= 7; j=j+2)
            {
                int bit = (byte >> j) & 3;
                vet_int[(i*4) + (j/2)]= bit;
            }

    }

    return vet_int;
}

void rx_data_write(int* entrada_vet_int, long int q_bits) {

    FILE* binario = fopen("src/matrizes/arquivo.bin", "wb");

    if (binario == NULL) {
        printf("Erro! Arquivo.bin nao pode ser aberto!\n");
        return;

    } else {
        printf("Arquivo.bin gerado com sucesso.\n");
    }

    for (int i = 0; i < q_bits; i++) {

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

struct Complex *rx_layer_demapper(int a, struct Complex *s_mapped,struct Complex *s, int Nstreams){

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        s[(a * Nstreams) + i].real = s_mapped[i].real;
        s[(a * Nstreams) + i].img = s_mapped[i].img ;
    }
    return s;
}

struct Complex *tx_layer_mapper(int a, struct Complex *s,struct Complex *s_mapped, int Nstreams) {

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        s_mapped[i].real = s[a * Nstreams + i].real;
        s_mapped[i].img = s[a * Nstreams + i].img;
    }
    return s_mapped;
}

struct Complex **channel_gen(int Nr,struct Complex **H, int Nt) {

    // Gera os valores aleatórios para a matriz H
      // Inicializa a semente do gerador de números aleatórios

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
