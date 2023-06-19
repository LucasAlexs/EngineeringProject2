#ifndef MATRIZES_H
#define MATRIZES_H

/**### typedef struct Complex
* - É uma estrutura de dados que permite representar números complexos em linguagem c 
*/
typedef struct Complex
{

    double real;
    double img;

} Complex;

void print_name();

struct Complex somanc(struct Complex a,struct Complex b);
struct Complex multiplicacao(struct Complex x,struct Complex y);

struct Complex **soma(struct Complex **matrix1,struct Complex **matrix2, int linhas, int colunas);
void teste_soma();

struct Complex **subtracao(struct Complex **matrix1,struct Complex **matrix2, int linhas, int colunas);
void teste_subtracao();

struct Complex **transposta(struct Complex **matrix1, int linhas, int colunas);
void teste_transposta();

struct Complex **conjugado(struct Complex **matrix1, int linhas, int colunas);
void teste_conjugada();

struct Complex **hermitiano(struct Complex **matrix1, int linhas, int colunas);
void teste_hermitiana();

struct Complex produto_escalar(struct Complex *vet1,struct Complex *vet2, int neu, int nev);
void teste_produto_escalar();

struct Complex **produto_matricial(struct Complex **matrix1,struct Complex **matrix2, int linhas, int colunas);

#endif
