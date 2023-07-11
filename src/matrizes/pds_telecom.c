#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrizes.h"
#include "pds_telecom.h"

int main()
{
   //tx_data_read();

   int Nr = 4, Nt = 4 ,size = 8, Nstreams,Nqam = 4;
    double rmax, rmin;
    struct Complex *s,*s_mapped, *o, *lm,*ld;
    struct Complex **H,**U,*S,**V;
    struct Complex **F, **Y, **W,*Z;

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

    lm = (struct Complex *)malloc(Nstreams * sizeof(struct Complex ));
    ld = (struct Complex *)malloc(Nstreams * sizeof(struct Complex ));

    o = (struct Complex *)malloc(Nt * sizeof(struct Complex ));

    s = (struct Complex *)malloc(Nstreams * sizeof(struct Complex ));

    H = (struct Complex **)malloc(Nr * sizeof(struct Complex *));
    for (int i = 0; i < Nt; i++){
        H[i] = (struct Complex *)malloc(Nt * sizeof(struct Complex));
    }

    H = channel_gen(Nr,H,Nt);

    U = (struct Complex **)malloc(Nr * sizeof(struct Complex *));
    for (int i = 0; i < Nr; i++){
        U[i] = (struct Complex *)malloc(Nt * sizeof(struct Complex));
    }

    S = (struct Complex *)malloc(Nt * sizeof(struct Complex));

    V = (struct Complex **)malloc(Nt * sizeof(struct Complex *));
    for (int i = 0; i < Nt; i++)
    {
        V[i] = (struct Complex *)malloc(Nt * sizeof(struct Complex));
    }

    calc_svd(H,U,S,V,Nr,Nt);

    s_mapped = tx_qam_mapper(vector,size);

    for (int a = 0; a < size; a+= Nstreams)
    {
        lm = tx_layer_mapper(a,s,s_mapped,Nstreams);
        F = tx_precoder(lm,V,Nr, Nt, Nstreams);
        Y = channel_transmission(rmax,rmin,F,H,Nr,Nt, Nstreams);
        free(F);
        W = rx_combiner(Y,U,Nr,Nt,Nstreams);
        free(Y);
        Z = rx_layer_demapper(a,W,ld,Nstreams);
        free(W);
        o = rx_feq(a,S,Z,Nr,Nt,Nstreams,size);
        free(Z);
    }

    vector = rx_qam_demapper(o,size);

    printf("Elementos do vetor Etapa2:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");

    free(vector);

    return 0;
}

void print_binario(unsigned char byte, int* vetor, long int* index) {
    for (int i = 6; i >= 0; i -= 2) {
        int num = ((byte >> i) & 1) + ((byte >> (i + 1)) & 1) * 2;
        vetor[(*index)++] = num;
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
        free(buffer);
        fclose(file);
        return NULL;
    }

    int* vetor = (int*)malloc((tamanho * 4) * sizeof(int)); // Cada byte gera 4 dígitos de 2 bits
    if (vetor == NULL) {
        printf("Erro! Memória não pode ser alocada.\n");
        free(buffer);
        fclose(file);
        return NULL;
    }

    long int index = 0;
    for (long i = 0; i < tamanho; i++) {
        print_binario(buffer[i - 1], vetor, &index);
    }

    free(buffer);
    fclose(file);

    *tamanho_retornado = tamanho * 4;
    return vetor;
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

int *rx_qam_demapper(struct Complex * symbol,int size){

    int *indice;

    indice = (int*)malloc(size * sizeof( int ));

    for (int i = 0; i < size; i++) {
        if (symbol[i].real < 0 && symbol[i].img > 0){
            indice[i] = 0;
        }
        else if (symbol[i].real < 0 && symbol[i].img < 0){
            indice[i] = 1;
        }
        else if (symbol[i].real > 0 && symbol[i].img > 0){
            indice[i] = 2;
        }
        else if (symbol[i].real > 0 && symbol[i].img < 0){
            indice[i] = 3;
        }
    }

    return indice;
}

struct Complex *rx_layer_demapper(int a, struct Complex **s_mapped,struct Complex *s, int Nstreams){

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        s[a + i ].real = s_mapped[0][i].real;
        s[a + i ].img = s_mapped[0][i].img ;
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

struct Complex **channel_transmission(double rmax, double rmin, struct Complex **mtx_cod, struct Complex **H,int Nr, int Nt, int Nstreams){
    struct Complex **rmtx;

    rmtx = produto_matricial( H, mtx_cod,Nr,Nt,Nt,1);

    for (int j = 0; j < Nstreams; j++) {
        rmtx[0][j].real = rmtx[0][j].real + ((double)rand() / RAND_MAX) * (rmax - rmin) + rmin;
        rmtx[0][j].img = rmtx[0][j].img + ((double)rand() / RAND_MAX) * (rmax - rmin) + rmin;
    }


    return rmtx;

}

struct Complex **tx_precoder(struct Complex *x,struct Complex **V, int Nr, int Nt, int Nstreams){
    struct Complex **x_aux,**x_aux2,**rmtx;

    x_aux = (struct Complex **)malloc(Nstreams * sizeof(struct Complex *));
    for(int i=0; i<Nstreams; i++){
        x_aux[i] = (struct Complex *)malloc(1 * sizeof(struct Complex));
    }

    for(int i=0; i<Nstreams; i++){
        x_aux[i][0].real = x[i].real;
        x_aux[i][0].img = x[i].img;
    }
    x_aux2 = hermitiano(V,Nt,Nt);
    rmtx = produto_matricial(V,x_aux2,Nt,Nstreams,Nt,1);

    free(x_aux);

    return rmtx;
}

struct Complex **rx_combiner(struct Complex **Y,struct Complex **U, int Nr, int Nt, int Nstreams){
    struct Complex **rmtx, **aux;

    aux = hermitiano(U,Nr,Nt);

    rmtx = produto_matricial(U,Y,Nt,Nr,Nr,1);


    return rmtx;
}


struct Complex *rx_feq(int a,struct Complex *S,struct Complex *W,int Nr, int Nt, int Nstreams,int size){
    struct Complex *rmtx;

    rmtx = (struct Complex *)malloc(size * sizeof(struct Complex));


    for(int i=0; i<Nstreams; i++){
        rmtx[a + i ].real = W[i].real / S[i].real;
        rmtx[a + i ].img = W[i].img  / S[i].real;
    }

    return rmtx;
}
