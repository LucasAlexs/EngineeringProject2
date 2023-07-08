#ifndef PDS_TELECOM_H
#define PDS_TELECOM_H

void print_binario(unsigned char byte, int* vetor, long* index);

int* tx_data_read(const char* texto_str, long int* tamanho_retornado);

struct Complex *tx_qam_mapper(int* indice, int size);

int *rx_qam_demapper(struct Complex * symbol,int size);

struct Complex **channel_gen(int Nr,struct Complex **H, int Nt);

struct Complex **channel_transmission(double rmax, double rmin, struct Complex **mtx_cod, struct Complex **H, int Nr, int Nt);

void rx_data_write(int* entrada_vet_int, long int *q_bits_retornado);

#endif
