#ifndef PDS_TELECOM_H
#define PDS_TELECOM_H

int hexToDecimal(char hex);

int *tx_data_read(const char *filename, int *size);

struct Complex * tx_qam_mapper(int* indice, int size) ;

int * rx_qam_demapper(struct Complex * symbol,int size);

#endif
