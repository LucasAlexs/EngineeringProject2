#ifndef PDS_TELECOM_H
#define PDS_TELECOM_H

void print_binario(unsigned char byte, int* vetor, long* index);

int *tx_data_read(const char *texto_str, long *tamanho_retornado);

struct Complex * tx_qam_mapper(int* indice, int size);

int * rx_qam_demapper(struct Complex * symbol,int size);

struct Complex *rx_layer_demapper(int a, struct Complex *s_mapped,struct Complex *s, int Nstreams);

struct Complex *tx_layer_mapper(int a, struct Complex *s,struct Complex *s_mapped, int Nstreams);

struct Complex **channel_gen(int Nr,struct Complex **H, int Nt);

struct Complex **channel_transmission(double rmax, double rmin, struct Complex **mtx_cod, struct Complex **H, int Nr, int Nt);

#endif
