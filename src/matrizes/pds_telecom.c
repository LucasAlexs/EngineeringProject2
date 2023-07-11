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
