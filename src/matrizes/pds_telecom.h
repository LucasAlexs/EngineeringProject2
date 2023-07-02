#ifndef MATRIZES_H
#define MATRIZES_H

int hexToDecimal(char hex);

int *tx_data_read(const char *filename, int *size);

int * tx_layer_mapper(struct Complex * symbol,int size);

void rx_data_write(const char *filename, const int *data, int size);


#endif
