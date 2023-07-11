#ifndef PDS_TELECOM_H
#define PDS_TELECOM_H
int * tx_data_read(FILE* entrada_arquivo, long int q_bytes);

void rx_data_write(int* entrada_vet_int, long int tamanho);

struct Complex * tx_qam_mapper(int* indice, int size);

int * rx_qam_demapper(struct Complex * symbol,int size);

struct Complex *rx_layer_demapper(int a, struct Complex **s_mapped,struct Complex *s, int Nstreams);

struct Complex *tx_layer_mapper(int a, struct Complex *s,struct Complex *s_mapped, int Nstreams);

struct Complex **channel_gen(int Nr,struct Complex **H, int Nt);

struct Complex **tx_precoder(struct Complex *x,struct Complex **V, int Nr, int Nt, int Nstreams);

struct Complex **channel_transmission(double rmax, double rmin, struct Complex **mtx_cod, struct Complex **H,int Nr, int Nt, int Nstreams);

struct Complex **rx_combiner(struct Complex **Y,struct Complex **U, int Nr, int Nt, int Nstreams);

struct Complex *rx_feq(int a,struct Complex *S,struct Complex *W,int Nr, int Nt, int Nstreams,int size);

int gera_estatisticas(struct Complex *s,struct Complex *o, int size);

#endif
