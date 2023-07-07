#ifndef PDS_TELECOM_H
#define PDS_TELECOM_H

void print_binario(unsigned char byte, int* vetor, long* index);

int *tx_data_read(const char *texto_str, long *tamanho_retornado);

struct Complex * tx_qam_mapper(int* indice, int size);

int * rx_qam_demapper(struct Complex * symbol,int size);

#endif
