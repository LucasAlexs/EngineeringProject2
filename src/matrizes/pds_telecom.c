//    teste_svd();
//    teste_mapper();
//    teste_rw();

    FILE *arquivo_txt = fopen("src/matrizes/arquivo.txt","rb");

    fseek(arquivo_txt,0,SEEK_END);
    long int q_bytes = ftell(arquivo_txt);
    fseek(arquivo_txt,0,SEEK_SET);

    int* vetor_int = (int *)malloc(q_bytes * sizeof(int));
    vetor_int = tx_data_read(arquivo_txt,q_bytes);

    long int tamanho = (q_bytes*2*((sizeof(arquivo_txt)) / 4)) - 4;

    printf("\n\n[Vetor de Inteiros Resultante de tx_data_read]\n\n");

    for(int i = 0; i < tamanho; i++){
        printf("%d", vetor_int[i]);
    }

    printf("\n[--------------------------------------------]\n\n");

    int Nr = 4, Nt = 4 ,size = tamanho, Nstreams,Nqam = 4;
    struct Complex *vetor_c,*s_mapped, *o;

    vetor_c = tx_qam_mapper(vetor_int,size);

        printf("\n\n[Vetor de Complexos Resultante de tx_qam_mapper]\n\n");

    for(int i = 0; i < tamanho; i++){
        printf(" %.4f %.4fj\n", vetor_c[i].real,vetor_c[i].img);
    }

    printf("\n[--------------------------------------------]\n\n");
