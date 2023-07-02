#include <stdio.h>
#include <stdlib.h>
#include "matrizes/pds_telecom.h"

int main()
{
    int vet[20];
    struct Complex * symbol;

    for(int i=0; i < 20; i = i + 4){
        vet[i]= 0;
        vet[i+1]= 1;
        vet[i+2]= 2;
        vet[i+3]= 3;
    }

    symbol = tx_qam_mapper(vet, 20);

    for(int i=0; i < 20; i++){
        printf("%.2f + %.2fj\t", symbol[i].real, symbol[i].img);
        
        printf("\n\n");
    }

    return 0;
}
