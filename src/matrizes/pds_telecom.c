#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrizes.h"
#include "pds_telecom.h"

//FUNCÕES
/*
*   - As funções denotadas por "tx" são as transmissoras, estão no início da comunicação digital, enquanto as denotadas por "rx" são as receptoras.
*/

int main()
{

   FILE *arquivo_txt = fopen("src/matrizes/arquivo.txt","rb");

    fseek(arquivo_txt,0,SEEK_END);
    long int q_bytes = ftell(arquivo_txt);
    fseek(arquivo_txt,0,SEEK_SET);


    int* vetor_int = (int *)malloc(q_bytes * sizeof(int));

    vetor_int = tx_data_read(arquivo_txt,q_bytes);

    long int tamanho = (q_bytes*2*((sizeof(arquivo_txt)) / 4)) - 4;

    printf("\n[Vetor de Inteiros Resultante de tx_data_read]\n\n");

    for(int i = 0; i < tamanho; i++){
        printf(" %d", vetor_int[i]);
    }
    printf("\n");

   int Nr = 4, Nt = 4 ,size = tamanho, Nstreams,Nqam = 4,est;
   double rmax = 0, rmin = 0;
   struct Complex *s,*s_mapped, *o, *lm,*ld;
   struct Complex **H,**U,*S,**V;
   struct Complex **F, **Y, **W,*Z;

   if (Nr < Nt) {
        Nstreams = Nr;
    } else {
        Nstreams = Nt;
    }

    if (vetor_int == NULL) {
        printf("\n\nErro ao alocar memória para o vetor.\n\n");
        return 1;
    }
    //Atribuição de valores para s_mapped, ld, o, H, U, S, V e s.
    s_mapped = (struct Complex *)malloc(Nstreams * sizeof(struct Complex ));
    ld = (struct Complex *)malloc(Nstreams * sizeof(struct Complex ));
    o = (struct Complex *)malloc(Nt * sizeof(struct Complex ));
    
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

    s = tx_qam_mapper(vetor_int,size);

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
    
    //Valores recebidos
    vetor_int = rx_qam_demapper(o,size);

    printf("\n\n[Vetor de Inteiros Resultante de rx_qam_demapper]\n\n");
    for (int i = 0; i < size; i++) {
        printf(" %d", vetor_int[i]);
    }
    printf("\n");
    
    //dados da transmissão
    est = gera_estatisticas(s,o,size);

    printf("\n\n Número de símbolos QAM transmitidos: %d \n",size);
    printf("\n Número de símbolos QAM recebidos com erro: %d \n",est);
    printf("\n Porcentagem de símbolos QAM recebidos com erro: %d% \n\n",est/size);

    printf("\n[Escrevendo dados no Arquivo.bin com rx_data_write]\n\n");

    rx_data_write(vetor_int,q_bytes);

    FILE *arquivo_bin = fopen("src/matrizes/arquivo.bin","rb");

    int* vetor_int_bin = (int *)malloc(q_bytes * sizeof(int));

    vetor_int_bin = tx_data_read(arquivo_bin,q_bytes);

    printf("\n[Conteudo gerado pela função tx_data_read para arquivo.txt]\n\n");

    for(int i = 0; i < size; i++){

        printf("%d", vetor_int[i]);
    }


    printf("\n\n[Conteudo gerado pela função tx_data_read para arquivo.bin]\n\n");

    for(int i = 0; i < size; i++){

        printf("%d", vetor_int_bin[i]);

    }
    printf("\n\n");

    fclose(arquivo_bin);
    fclose(arquivo_txt);
    free(vetor_int);
    free(s_mapped);
    free(o);

    return 0;
}

/** Função tx_data_read
*   - Esta funçao faz a leitura dos dados que entram no sistema;
*   - O arquivo selecionado é um arquivo de texto;
*   - O código de cada caractere segue a tabela ASCII;
*   - A função separa cada byte do arquivo em 4 números inteiros de 0 a 3 (00-11);
*   - o valor retornado é um vetor.
 * @param[in] int entrada_arquivo, q_bytes
 * @param[out] vet_int
*/

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
/** Função tx_qam_mapper
*   - Os dados de entrada é um vetor dos binários do arquivo-texto selecionado;
*   - Para cada elemento do vetor indice, verifica o seu valor e atribui valores correspondentes ao campo real e img da estruct complex de seu índice;
*   - O tráfego do vetor de índices é feito em pacotes de 0 a 3 bits(00-11).
 * @param[in] Complex indice, size
 * @param[out] symbol
*/

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

/** Função rx_qam_demmaper
*   - Desfaz o processamento feito pela função tx_qam_mapper;
*   - Para cada elemento do vetor symbol é verificado os valores do campo real e img e atribui um valor corresponte do vetor de inteiro do mesmo índice.
 * @param[in] int Complex *symbol, size
 * @param[out] indice
*/

int *rx_qam_demapper(struct Complex * symbol,int size){

    int *indice;

    indice = (int*)malloc(size * sizeof( int ));

    for (int i = 0; i < size; i++) {
        if (symbol[i].real < 0 && symbol[i].img > 0){
            indice[i] = 0;
        }
        else if (symbol[i].real < 0 && symbol[i].img > 0){
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

/** Função rx_layer_demapper
*   - Desfaz o processamento feito pela função tx_layer_mapper;
*   - Percorre cada elemento do vetor s_mapped e atribui valores aos campos real e img das estruturas no vetor s.
 * @param[in] Complex a, Complex *s_mapped, Complex *s, Nstreams
 * @param[out] s
*/

struct Complex *rx_layer_demapper(int a, struct Complex **s_mapped,struct Complex *s, int Nstreams){

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        s[(a) + i ].real = s_mapped[i][0].real;
        s[(a) + i ].img = s_mapped[i][0].img ;
    }
    return s;
}

/** Função tx_layer_mapper
*   - Mapeia os símbolos da função "tx_qam_mapper" para cada stream;
*   - percorre os elementos do vetor s e atribui seus valores aos campos real e img das estruturas no vetor s_mapped;
*   - O valor de entrada é um vetor de números complexos.
 * @param[in] Complex a, Complex*s, Complex s_mapped, Nstreams
 * @param[out] s_mapped
*/

struct Complex *tx_layer_mapper(int a, struct Complex *s,struct Complex *s_mapped, int Nstreams) {

    // Loop para percorrer os símbolos de entrada
    for (int i = 0; i < Nstreams; i++) {
        // Mapeia o símbolo QAM para a stream correspondente
        s_mapped[i].real = s[(a ) + i ].real;
        s_mapped[i].img = s[(a) + i ].img;
    }
    return s_mapped;
}

/** Função channel_gen
*   - Gera uma matriz de elementos aleatórios que representa o canal H;
*   - Possui dimensão é Nr x Nt (Número de antenas receptoras x antenas transmissoras);
*   - Inicializa a semente do gerador de números aleatórios com o tempo atual;
*   - Os elementos da matriz são gerados como números reais e com ponto flutuante, variando entre -1 e 1.
 * @param[in] Complex Nr, Complex **H, Nt
 * @param[out] H
*/

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

/** Função channel_transmission
*   - Gera uma matriz que representa com ruído aleatório que ocorre durante a transmissão;
*   - Os valores dessa matriz são um multiplicadores dos símbolos da matriz H;
*   - Realiza a Operação produto matricial entre mtx_cod e H e armazena o resultado em rmtx;
*   - percorre os elementos da matriz rmtx e adiciona um valor aleatório entre rmin e rmax aos campos real e img;
*   - O valor dos máximos e mínimos do ruído pode ser ajustado através do parâmetro de entrada da função.
 * @param[in] Complex rmax, rmin, Complex **mtx_cod, Complex **H, Nr, Nt
 * @param[out] rmtx
*/

struct Complex **channel_transmission(double rmax, double rmin, struct Complex **mtx_cod, struct Complex **H,int Nr, int Nt, int Nstreams){
    struct Complex **rmtx;

    rmtx = produto_matricial( H, mtx_cod,Nr,Nt,Nt,1);

    for (int j = 0; j < Nstreams; j++) {
        rmtx[0][j].real = rmtx[0][j].real + ((double)rand() / RAND_MAX) * (rmax - rmin) + rmin;
        rmtx[0][j].img = rmtx[0][j].img + ((double)rand() / RAND_MAX) * (rmax - rmin) + rmin;
    }

    return rmtx;

}

/** Função gera_estatísticas
*   - Gera dados sobre a taxa de erros dos simbolos recebidos;
*   - Os dados informados são: símbolos QAM transmitidos, símbolos QAM recebidos com erro e porcentagem dos símbolos QAM recebidos com erro;
*   - A verificação é feita comparando os dados transmitidos na saída da função "tx-qam_mapper" com "rx_qam_demapper".
 * @param[in] int Complex *s, Complex *o, size
 * @param[out] result
*/

int gera_estatisticas(struct Complex *s,struct Complex *o, int size){
    int result = 0;

    for (int i = 0; i < size ; i++) {
        if (s[i].real == o[i].real && s[i].img == o[i].img){
            result ++;
        }
    }
    
    return result;
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
