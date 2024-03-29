#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrizes.h"
#include "pds_telecom.h"
/** Função int main
*   Executa a função channel_simulator com vários parâmetros de entrada diferentes alterando:
*-  Número de antenas receptoras
*-  Número de antenas transmissoras
*-  Intensidade do sinal
*/
int main(){

    channel_simulator(2,4,1,-1);
    channel_simulator(2,4,0.5,-0.5);
    channel_simulator(2,4,0.1,-0.1);
    channel_simulator(2,4,0.01,-0.01);
    channel_simulator(8,8,1,-1);
    channel_simulator(8,8,0.5,-0.5);
    channel_simulator(8,8,0.1,-0.1);
    channel_simulator(8,8,0.01,-0.01);
    channel_simulator(8,32,1,-1);
    channel_simulator(8,32,0.5,-0.5);
    channel_simulator(8,32,0.1,-0.1);
    channel_simulator(8,32,0.01,-0.01);
    channel_simulator(16,32,1,-1);
    channel_simulator(16,32,0.5,-0.5);
    channel_simulator(16,32,0.1,-0.1);
    channel_simulator(16,32,0.01,-0.01);

    return 0;
}

/** função channel_simulator
*
*   - Esta função simula um sistema de transmissão usando modulação QAM.
*   Ela lê dados do arquivo “arquivo.txt” e os converte em um vetor de inteiros usando a função tx_data_read.
*   Os dados são convertidos para números complexos pela função tx_qam_mapper e então mapeados para símbolos QAM usando a função tx_layer_mapper.
*   Os os elementos do vetor s_mapped, que é a saída de tx_layer_mapper, são transmitidos através de um canal gerado pela função channel_gen, transmitidos por channel_transmission e recebidos pelo receptor rx_combiner.
*   Os sinais recebidos são convertidos pela funação rx_layer_demapper, para simbolos symbol.
*   Esses símbolos são então operados peal função rx_feq, possibilitando assim que a função rx_qam_demapper demapeie os sinais
*   Então estatísticas sobre a transmissão são geradas usando a função gera_estatisticas.
*   Finalmente, os dados recebidos são escritos em um arquivo chamado “arquivo.bin” usando a função rx_data_write.
*
*   - As funções denotadas por "tx" são as transmissoras, estão no início da comunicação digital, enquanto as denotadas por "rx" são as receptoras.
*
*   - A ordem de execução é a seguinte: tx_data_read(),tx_qam_mapper(), tx_layer_mapper(), tx_precoder(), channel_gen(), channel_transmission(), rx_combiner(), rx_layer_demapper(), rx_feq(), rx_qam_demapper(), rx_data_write().
*/

int channel_simulator(int Nr,int Nt,int rmax,int rmin)
{
    if(Nr != Nt){
        printf("Se você está vendo isso significa que não conseguimos implementar a transmissão para sistemas com Nr e Nt diferentes entre si.\n");
        return 1;
    }

    // Abertura do arquivo "arquivo.txt" em modo de leitura binária
   FILE *arquivo_txt = fopen("src/matrizes/arquivo.txt","rb");

   // Determinação do número de bytes no arquivo
    fseek(arquivo_txt,0,SEEK_END);
    long int q_bytes = ftell(arquivo_txt);
    fseek(arquivo_txt,0,SEEK_SET);

    // Alocação dinâmica de memória para o vetor de inteiros
    int* vetor_int = (int *)malloc(q_bytes * sizeof(int));

     // Leitura dos dados do arquivo e armazenamento no vetor de inteiros
    vetor_int = tx_data_read(arquivo_txt,q_bytes);

    // Cálculo do tamanho do vetor de inteiros
    long int tamanho = (q_bytes*2*((sizeof(arquivo_txt)) / 4)) - 4;

    // Impressão dos valores do vetor de inteiros na tela
    printf("\n[Vetor de Inteiros Resultante de tx_data_read]\n\n");

    for(int i = 0; i < tamanho; i++){
        printf(" %d", vetor_int[i]);
    }
    printf("\n");

    // Declaração de variáveis e ponteiros
   int size = tamanho, Nstreams,Nqam = 4,est;
   struct Complex *s,*s_mapped, *o, *lm,*ld;
   struct Complex **H,**U,*S,**V;
   struct Complex **F, **Y, **W,*Z;

   // Verificação se o número de antenas receptoras é menor que o número de antenas transmissoras
   if (Nr < Nt) {
        Nstreams = Nr;
    } else {
        Nstreams = Nt;
    }

    if (vetor_int == NULL) {
        printf("\n\nErro ao alocar memória para o vetor.\n\n");
        return 1;
    }
    // Alocação dinâmica de memória para vários ponteiros
    s_mapped = (struct Complex *)malloc(Nstreams * sizeof(struct Complex ));
    ld = (struct Complex *)malloc(Nstreams * sizeof(struct Complex ));
    o = (struct Complex *)malloc(Nt * sizeof(struct Complex ));

     // Geração da matriz do canal H
     H = (struct Complex **)malloc(Nr * sizeof(struct Complex *));
    for (int i = 0; i < Nt; i++){
        H[i] = (struct Complex *)malloc(Nt * sizeof(struct Complex));
    }

    H = channel_gen(Nr,H,Nt);

    U = (struct Complex **)malloc(Nr * sizeof(struct Complex *));
    for (int i = 0; i < Nr; i++){
        U[i] = (struct Complex *)malloc(Nt * sizeof(struct Complex));
    }

    // Alocação dinâmica de memória para o vetor S
    S = (struct Complex *)malloc(Nt * sizeof(struct Complex));

    // Alocação dinâmica de memória para a matriz V
    V = (struct Complex **)malloc(Nt * sizeof(struct Complex *));
    for (int i = 0; i < Nt; i++)
    {
        V[i] = (struct Complex *)malloc(Nt * sizeof(struct Complex));
    }

    // Cálculo da decomposição em valores singulares (SVD) da matriz H
    calc_svd(H,U,S,V,Nr,Nt);

    // Mapeamento dos dados do vetor de inteiros para símbolos QAM
    s = tx_qam_mapper(vetor_int,size);

    // Processamento de cada grupo de símbolos
    for (int a = 0; a < size; a+= Nstreams)
    {
        // Mapeamento dos símbolos para camadas
        lm = tx_layer_mapper(a,s,s_mapped,Nstreams);

        // Pré-codificação dos símbolos usando a matriz V da decomposição SVD
        F = tx_precoder(lm,V,Nr, Nt, Nstreams);

        // Transmissão dos símbolos pré-codificados através do canal gerado pela função channel_gen
        Y = channel_transmission(rmax,rmin,F,H,Nr,Nt, Nstreams);
        free(F);

        // Combinação dos sinais recebidos usando a matriz U da decomposição SVD
        W = rx_combiner(Y,U,Nr,Nt,Nstreams);
        free(Y);

        // Demapeamento das camadas para símbolos QAM
        Z = rx_layer_demapper(a,W,ld,Nstreams);
        free(W);

        // Equalização dos símbolos QAM recebidos
        o = rx_feq(a,S,Z,Nr,Nt,Nstreams,size);
        free(Z);
    }

    // Demapeamento dos símbolos QAM recebidos para dados inteiros
    vetor_int = rx_qam_demapper(o,size);

    // Geração de estatísticas sobre a transmissão
    est = gera_estatisticas(s,o,size);

    printf("\n\n Número de símbolos QAM transmitidos: %d \n",size);
    printf("\n Número de símbolos QAM recebidos com erro: %d \n",est);
    printf("\n Porcentagem de símbolos QAM recebidos com erro: %d% \n\n",est/size);

    printf("\n[Escrevendo dados no Arquivo.bin com rx_data_write]\n\n");

    // Escrita dos dados recebidos no arquivo "arquivo.bin"
    rx_data_write(vetor_int,q_bytes);

    // Abertura do arquivo "arquivo.bin" em modo de leitura binária
    FILE *arquivo_bin = fopen("src/matrizes/arquivo.bin","rb");

    // Alocação dinâmica de memória para o vetor de inteiros
    int* vetor_int_bin = (int *)malloc(q_bytes * sizeof(int));

    // Leitura dos dados do arquivo "arquivo.bin" e armazenamento no vetor de inteiros
    vetor_int_bin = tx_data_read(arquivo_bin,q_bytes);

    // Impressão dos valores do vetor de inteiros lidos do arquivo "arquivo.bin" na tela
    printf("\n[Conteudo gerado pela função tx_data_read para arquivo.bin]\n\n");

    for(int i = 0; i < size; i++){

        printf("%d", vetor_int[i]);
    }
    printf("\n\n");

    // Fechamento dos arquivos e liberação da memória alocada dinamicamente
    fclose(arquivo_bin);
    fclose(arquivo_txt);
    free(vetor_int);
    free(s_mapped);
    free(o);

    return 0;
}

/** função tx_data_read
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

/** função tx_qam_mapper
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

/** Função rx_data_write
*   - Escreve os dados em um arquivo binário, utilizando recuperados de um vetor de inteiros dos bytes originais;
*   - Recebe uma sequência de dígitos de 0 a 3;
*   - A função então percorre cada elemento do vetor de inteiros e converte cada grupo de 4 inteiros em um único byte;
*   - Operação OR bit a bit;
*   - A função então executa a operação OR entre o valor de byte e o resultado da operação de deslocamento à esquerda do valor de bit por (2 * j) posições e atribui o resultado ao valor de byte
*   - O byte resultante é escrito no arquivo binário usando a função fwrite.
 *  @param[in] int entrada_vet_int, tamanho
*/

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

/** função rx_qam_demmaper
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

/** função rx_layer_demapper
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

/** função tx_layer_mapper
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

/** função channel_gen
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

/** função channel_transmission
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

/** função gera_estatísticas
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

/** Função tx_precoder
*-  A variável x_aux é atribuída ao resultado da chamada da função malloc com o parâmetro Nstreams * sizeof(struct Complex *);
*-  Dentro do primeiro laço o elemento de índice [i] de x_aux é atribuído ao resultado da função malloc com o parâmetro 1 * sizeof(struct Complex);
*-  No próximo laço as propriedades real e img do elemento de índice [0] do elemento de índice [i] de x_aux são atribuídas aos valores das propriedades real e img, respectivamente, do elemento de índice [i] de x;
*-  A variável x_aux2 é atribuída ao resultado da função hermitiano;
*-  A variável rmtx é atribuída ao resultado da função produto_matricial.
 *  @param[in] Complex Complex *x, Complex **V, Nr, Nstreams
 *  #param[out] rmtx
*/

struct Complex **tx_precoder(struct Complex *x,struct Complex **V, int Nr, int Nt, int Nstreams){
    struct Complex **x_aux,**x_aux2,**rmtx;

    x_aux = (struct Complex **)malloc(Nstreams * sizeof(struct Complex *));
    for(int i=0; i<Nstreams; i++){
        x_aux[i] = (struct Complex *)malloc(Nstreams * sizeof(struct Complex));
    }

    for(int i=0; i<Nstreams; i++){
        x_aux[i][0].real = x[i].real;
        x_aux[i][0].img = x[i].img;
    }
    x_aux2 = hermitiano(V,Nt,Nt);

    rmtx = produto_matricial(x_aux2,x_aux,Nt,Nstreams,Nt,1);

    free(x_aux);

    return rmtx;
}

/** Função rx_combiner
*-   Pré-codifica os códigos antes deles serem transmitidos;
*-   A variável aux é atribuída ao resultado da função hermitiano;
*-   A variável rmtx é atribuída ao resultado da função produto_matricial.
 * @param[in] Complex Complex **Y, Complex **U, Nr, Ny, Nstreams
 * @param[out] rmtx
*/

struct Complex **rx_combiner(struct Complex **Y,struct Complex **U, int Nr, int Nt, int Nstreams){
    struct Complex **rmtx, **aux;

    aux = hermitiano(U,Nr,Nt);

    rmtx = produto_matricial(aux,Y,Nt,Nr,Nr,1);


    return rmtx;
}

/** Função rx_feq
*-  A variável rmtx é atribuída ao resultado da função malloc com o parâmetro size * sizeof(struct Complex);
*-  A função então executa um loop for que itera de 0 até Nstreams;
*-  As propriedades real e img do elemento de índice [a + i] de rmtx são atribuídas aos valores de divisão das propriedades real e img do elemento de índice [i] de W, respectivamente, pela propriedade real do elemento de índice [i] de S.
 *@param[in] Complex a, Complex *s, Complex *W, Nr, Nt, Nstreams, size
 *@param[out] rmtx
*/

struct Complex *rx_feq(int a,struct Complex *S,struct Complex *W,int Nr, int Nt, int Nstreams,int size){
    struct Complex *rmtx;

    rmtx = (struct Complex *)malloc(size * sizeof(struct Complex));


    for(int i=0; i<Nstreams; i++){
        rmtx[a + i ].real = W[i].real / S[i].real;
        rmtx[a + i ].img = W[i].img  / S[i].real;
    }

    return rmtx;
}
