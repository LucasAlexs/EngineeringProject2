#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include <time.h>
#include <gsl/gsl_linalg.h>
// FUNCÕES

void teste_produto_matricial();

/**### Função print_name()
* Imprime os nomes dos membros de uma equipe na tela. 
* Não há parâmetros de entrada e saída. 
* Essa função não retorna nenhum valor.

 * */

void print_name()
{
    printf("==========Equipe==========\n\n");

        char name1[]= "LUCAS ALEXSANDRO LEAL DOS SANTOS";
        char name2[]= "GABRIEL DE JESUS DOS SANTOS COSTA";
        char name3[]= "SAULO MATTHEUS RIBEIRO DE OLIVEIRA";
        char name4[]= "JOSE HENRIQUE BARBOSA PENA";

        printf(" %s\n %s\n %s\n %s\n\n", name1,name2, name3, name4);
}


/** Função soma()
* - Realiza a soma de duas matrizes complexas, representadas por ponteiros para ponteiros de struct Complex.
* - As matrizes de entrada devem ser alocadas previamente e conter valores válidos.
* - A matriz resultante da soma é alocada dentro da função e precisa ser liberada pelo chamador após o uso.
* - A função verifica se as matrizes têm o mesmo número de linhas e colunas antes de realizar a soma. Caso contrário, retorna NULL. Também realiza a soma dos elementos real e imaginário de cada posição correspondente nas matrizes de entrada e atribui o resultado à matriz resultante.
 * @param[in] Complex **matrix1, Complex **matrix2, linhas, colunas
 * @param[out] rmtx
*/

struct Complex **soma(struct Complex **matrix1,struct Complex **matrix2, int linhas, int colunas)
{

    struct Complex **rmtx;
    if(linhas == colunas){
    // aloca memória para a matriz de saída
    rmtx = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        rmtx[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

    // somar as matrizes

    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            rmtx[i][j].real = matrix1[i][j].real + matrix2[i][j].real;
            rmtx[i][j].img = matrix1[i][j].img + matrix2[i][j].img;
        }
      }
    }
    return rmtx;

}

/** função teste_soma()
* - Verifica a operação de soma de matrizes complexas. 
* - Não possui parâmetros de entrada e não retorna nenhum valor. 
* - Caso as dimensões das matrizes não coincidam, é exibida uma mensagem de erro indicando que a operação de soma não pode ser iniciada.
*/

void teste_soma()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **matrix2;
    struct Complex **rmtx;

     printf("==========Teste da Operacao de Soma==========\n\n");
    if(linhas == colunas){
    // alocar memória para as matrizes
    matrix1 = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    matrix2 = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
        matrix2[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

    // inicializar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matrix1[i][j].real = 1;
            matrix1[i][j].img = 1;
            matrix2[i][j].real = -1;
            matrix2[i][j].img = -1;
        }
    }

    // imprimir as matrizes operandas



    printf("Operando A:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", matrix1[i][j].real);
        }
        printf("\n\n");
    }

    printf("Operando B:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", matrix2[i][j].real);
        }
        printf("\n\n");
    }

    // somar as matrizes usando a função auxiliar
    rmtx = soma(matrix1, matrix2, linhas, colunas);

    // imprimir a soma das matrizes
    printf("A soma das matrizes:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", rmtx[i][j].real);
        }
        printf("\n\n");
    }



    printf("Operando C:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n\n");
    }

    printf("Operando D:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", matrix2[i][j].real, matrix2[i][j].img);
        }
        printf("\n\n");
    }

    // somar as matrizes usando a função auxiliar
    rmtx = soma(matrix1, matrix2, linhas, colunas);

    // imprimir a soma das matrizes
    printf("A soma das matrizes :\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n\n");
    }

    // desalocar a memória alocada
    for(int i=0; i<linhas; i++){
        free(matrix1[i]);
        free(matrix2[i]);
        free(rmtx[i]);
    }
    free(matrix1);
    free(matrix2);
    free(rmtx);
    }
     else{

        printf("ERRO!\n\n");
        printf("A operacao de soma nao pode ser iniciada pois os elementos nao coincidem\n\n");

    }
}

/** função subtracao()
* - Opera a subtração de duas matrizes complexas, representadas por ponteiros para ponteiros de struct Complex.
* - As matrizes de entrada devem ser alocadas previamente e conter valores válidos.
* - A matriz resultante da soma é alocada dentro da função e precisa ser liberada pelo chamador após seu uso.
* - A função verifica se as matrizes têm o mesmo número de linhas e colunas antes de realizar a soma. Caso contrário, retorna NULL.
* - A função realiza a soma dos elementos real e imaginário de cada posição correspondente nas matrizes de entrada e atribui o resultado à matriz resultante.
 * @param[in] Complex **matrix1, Complex **matrix2, linhas, colunas
 * @param[out] rmtx
*/


struct Complex **subtracao(struct Complex **matrix1,struct Complex **matrix2, int linhas, int colunas)
{
    struct Complex **rmtx;
    if(linhas == colunas){
    // aloca memória para a matriz de saída
    rmtx = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        rmtx[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

    // somar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            rmtx[i][j].real = matrix1[i][j].real - matrix2[i][j].real;
            rmtx[i][j].img = matrix1[i][j].img - matrix2[i][j].img;
        }
    }
    }
    return rmtx;
}

/** Função teste_subtracao()
* - Inicia um teste da operação de subtração de matrizes complexas. 
* - Não possui parâmetros de entrada e não retorna nenhum valor. 
* - Caso as dimensões das matrizes não coincidam, é exibida uma mensagem de erro indicando que a operação de subtração não pode ser iniciada.
*/


void teste_subtracao()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **matrix2;
    struct Complex **rmtx;

     printf("==========Teste da Operacao de Subtracao==========\n\n");
    if(linhas == colunas){
    // alocar memória para as matrizes
    matrix1 = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    matrix2 = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
        matrix2[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

    // inicializar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matrix1[i][j].real = 1;
            matrix1[i][j].img = 1;
            matrix2[i][j].real = 1;
            matrix2[i][j].img = 1;
        }
    }

    // imprimir as matrizes operandas

    printf("Operando A:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", matrix1[i][j].real);
        }
        printf("\n\n");
    }

    printf("Operando B:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", matrix2[i][j].real);
        }
        printf("\n\n");
    }

    // somar as matrizes usando a função auxiliar
    rmtx = subtracao(matrix1, matrix2, linhas, colunas);

    // imprimir a soma das matrizes
    printf("A subtracao das matrizes :\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", rmtx[i][j].real);
        }
        printf("\n\n");
    }

    printf("Operando C:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n\n");
    }

    printf("Operando D:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", matrix2[i][j].real, matrix2[i][j].img);
        }
        printf("\n\n");
    }

    // somar as matrizes usando a função auxiliar
    rmtx = subtracao(matrix1, matrix2, linhas, colunas);

    // imprimir a soma das matrizes
    printf("A subtracao das matrizes :\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n\n");
    }

    // desalocar a memória alocada
    for(int i=0; i<linhas; i++){
        free(matrix1[i]);
        free(matrix2[i]);
        free(rmtx[i]);
    }
    free(matrix1);
    free(matrix2);
    free(rmtx);
    }
     else{

        printf("ERRO!\n\n");
        printf("A operacao de soma nao pode ser iniciada pois os elementos nao coincidem\n\n");

    }
}

/** Função transposta 
* - Executa transposição da matriz de entrada matrix1 e armazena o resultado em uma nova matriz rmtx.
 * @param[in] Complex **matrix1, linhas, colunas
 * @param[out] rmtx
*/

struct Complex **transposta(struct Complex **matrix1, int linhas, int colunas)
{
   struct Complex **rmtx;
   int i,j;

    // aloca memória para a matriz de saída
    rmtx = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        rmtx[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

   for(i = 0; i < linhas; i++)
   {
       for(j = 0; j < colunas; j++)
       {
           rmtx[i][j].real = matrix1[j][i].real;
           rmtx[i][j].img = matrix1[j][i].img;
       }
   }
   return rmtx;
}

/** Função teste_transposta()
* - Realiza um teste da operação transposta de matrizes complexas. 
* - Não possui parâmetros de entrada e não retorna nenhum valor. 
*/

void teste_transposta()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **rmtx;

     printf("==========Teste da Operacao transposta==========\n\n");

    // alocar memória para a matrizes
    matrix1 = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

    // inicializar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matrix1[i][j].real = i;
            matrix1[i][j].img = j;
        }
    }

    // imprimir a matrize operando

    printf("Operando A:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", matrix1[i][j].real);
        }
        printf("\n\n");
    }

    // fazer a matriz transposta usando a função auxiliar
    rmtx = transposta(matrix1, linhas, colunas);

    // imprimir a matriz transposta
    printf("A transposta da matriz:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", rmtx[i][j].real);
        }
        printf("\n\n");
    }


    printf("Operando B:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n\n");
    }

    // fazer a matriz transposta usando a função auxiliar
    rmtx = transposta(matrix1, linhas, colunas);

    // imprimir a matriz transposta
    printf("A transposta da matriz:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n\n");
    }

    // desalocar a memória alocada
    for(int i=0; i<linhas; i++){
        free(matrix1[i]);
        free(rmtx[i]);
    }
    free(matrix1);
    free(rmtx);
}

/** Função conjugado()
* - Realiza a conjulgação da matriz de entrada matrix1 e armazena o resultado em uma nova matriz rmtx.
 * @param[in] Complex **matrix1, linhas, colunas
 * @param[out] rmtx
*/


struct Complex **conjugado(struct Complex **matrix1, int linhas, int colunas)
{
   struct Complex **rmtx;
   int i,j;

    // aloca memória para a matriz de saída
    rmtx = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        rmtx[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

   for(i = 0; i < linhas; i++)
   {
       for(j = 0; j < colunas; j++)
       {
           rmtx[i][j].real = matrix1[i][j].real;
           rmtx[i][j].img = matrix1[i][j].img * (-1);
       }
   }
   return rmtx;
}

/** Função teste_conjugada()
* - Realiza um teste da operação conjugada de matrizes complexas. 
* - Não possui parâmetros de entrada e não retorna nenhum valor. 
*/


void teste_conjugada()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **rmtx;

     printf("==========Teste da Operacao conjugada==========\n\n");

    // alocar memória para a matrizes
    matrix1 = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

    // inicializar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matrix1[i][j].real = 1;
            matrix1[i][j].img = 1;
        }
    }

    // imprimir a matrize operando

    printf("Operando A:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2fj\t",matrix1[i][j].img);
        }
        printf("\n\n");
    }

    // fazer a matriz conjugada usando a função auxiliar
    rmtx = conjugado(matrix1, linhas, colunas);

    // imprimir o conjugada da matriz
    printf("A conjugada da matriz:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2fj\t",rmtx[i][j].img);
        }
        printf("\n\n");
    }


    printf("Operando B:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n\n");
    }

    // fazer a matriz conjugada usando a função auxiliar
    rmtx = conjugado(matrix1, linhas, colunas);

    // imprimir o conjugada da matriz
    printf("A conjugada da matriz:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n\n");
    }

    // desalocar a memória alocada
    for(int i=0; i<linhas; i++){
        free(matrix1[i]);
        free(rmtx[i]);
    }
    free(matrix1);
    free(rmtx);

}

/** Função hermitiano()
* - Calcula o hermitiano da matriz de entrada matrix1 e armazena o resultado em uma nova matriz rmtx.
 * @param[in] Complex **matrix1, linhas, colunas
 * @param[out] rmtx
*/

struct Complex **hermitiano(struct Complex **matrix1, int linhas, int colunas)
{
   struct Complex **rmtx, **aux;
   int i,j;

    // aloca memória para a matriz de saída
    rmtx = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    aux = (struct Complex **)malloc(linhas * sizeof(struct Complex *));

    for(int i=0; i<linhas; i++){
         rmtx[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
         aux[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

   for(i = 0; i < linhas; i++)
   {
       for(j = 0; j < colunas; j++)
       {
           aux=transposta(matrix1,linhas,colunas);
           rmtx=conjugado(aux,linhas,colunas);
       }
   }
   return rmtx;
}

/** Função teste_hermitiano()
* - Realiza um teste da operação hermitiano de matrizes complexas. 
* - Não possui parâmetros de entrada e não retorna nenhum valor. 
*/


void teste_hermitiano()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **rmtx;

     printf("==========Teste da Operacao hermitiano==========\n\n");

    // alocar memória para a matrizes
    matrix1 = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

    // inicializar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matrix1[i][j].real = i;
            matrix1[i][j].img = j;
        }
    }

    // imprimir a matrize operando

    printf("Operando A:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2fj\t", matrix1[i][j].img);
        }
        printf("\n\n");
    }

    // fazer a matriz hermitiana usando a função auxiliar
    rmtx = hermitiano(matrix1, linhas, colunas);

    // imprimir o hermitiano da matriz
    printf("Hermitiano da matriz:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2fj\t",rmtx[i][j].img);
        }
        printf("\n\n");
    }


    printf("Operando B:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n\n");
    }

    // fazer a matriz hermitiana usando a função auxiliar
    rmtx = hermitiano(matrix1, linhas, colunas);

    // imprimir o hermitiano da matriz
    printf("Hermitiano da matriz:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n\n");
    }

    // desalocar a memória alocada
    for(int i=0; i<linhas; i++){
        free(matrix1[i]);
        free(rmtx[i]);
    }
    free(matrix1);
    free(rmtx);

}

/** Função produto_escalar()
* - Calcula o produto escalar de dois vetores e armazena o resultado em uma matriz rmtx.
 * @param[in] Complex *vet1,Complex *vet2, int neu, int nev
 * @param[out] rmtx
*/

struct Complex produto_escalar(struct Complex *vet1,struct Complex *vet2, int neu, int nev){
struct Complex rmtx, aux;

    rmtx.real= 0;
    rmtx.img= 0;

    if(neu == nev){
    // multiplicar as matrizes
    for(int i=0; i<neu; i++){
            aux = multiplicacao(vet1[i],vet2[i]);
            rmtx.real = rmtx.real + aux.real;
            rmtx.img = rmtx.img + aux.img;
            }
        }
     else{
            printf("ERRO!\n\n");
            printf("O produto escalar nao pode ser calculado porque entre estes vetores pois o numero de elementos dos vetores nao coincidem.\n\n");
    }


    return rmtx;
}

/** Função teste_produto_escalar()
* - Realiza um teste da operação produto escalar de matrizes complexas. 
* - Não possui parâmetros de entrada e não retorna nenhum valor. 
*/


void teste_produto_escalar(){
    int linhas = 3;
    struct Complex *vet1;
    struct Complex *vet2;
    struct Complex result;

     printf("==========Teste da Operacao de Produto Escalar==========\n\n");

    // alocar memória para a matrizes
    vet1 = (struct Complex *)malloc(linhas * sizeof(struct Complex ));
    vet2 = (struct Complex *)malloc(linhas * sizeof(struct Complex ));

    // inicializar os vetores
    for(int i=0; i<linhas; i++){
            vet1[i].real = 1;
            vet1[i].img = 1;
            vet2[i].real = 1;
            vet2[i].img = 1;
            }
    // imprimir os vetores operandos

    printf("Operando A:\n\n");
    for(int i=0; i<linhas; i++){
            printf("%.2f\t",vet1[i].real);
    }

    printf("\n\n");
    printf("Operando B:\n\n");
    for(int i=0; i<linhas; i++){
            printf("%.2f\t",vet2[i].real);
    }

    printf("\n\n");

    // fazer a matriz conjugada usando a função auxiliar
    result = produto_escalar(vet1, vet2, linhas,linhas);

    // imprimir o conjugada da matriz
    printf("Produto Escalar A . B:\n\n");


            printf("%.2f\t", result.real);

        printf("\n\n");


    printf("Operando C:\n\n");
    for(int i=0; i<linhas; i++){
            printf("%.2f + %.2fj\t",vet1[i].real, vet1[i].img);
    }

    printf("\n\n");
    printf("Operando D:\n\n");
    for(int i=0; i<linhas; i++){
            printf("%.2f + %.2fj\t",vet2[i].real, vet2[i].img);
    }

    printf("\n\n");

    // fazer a matriz conjugada usando a função auxiliar
    result = produto_escalar(vet1, vet2, linhas,linhas);

    // imprimir o conjugada da matriz
    printf("Produto Escalar C . D:\n\n");


            printf("%.2f + %.2fj\t", result.real , result.img);

        printf("\n\n");

    // desalocar a memória alocada

    free(vet1);
    free(vet2);
}

/** Função somanc()
* - Calcula a soma de dois numeros complexos.
 * @param[in] struct Complex a,struct Complex b
 * @param[out] struct Complex result
*/


struct Complex somanc(struct Complex a,struct Complex b) {

    struct Complex result;

    result.real = a.real + b.real;
    result.img = a.img + b.img;

    return result;
}

/** Função multiplicacao()
* - Calcula o produto de dois numeros complexos.
 * @param[in] Complex x, Complex y
 * @param[out] rmtx
*/

struct Complex multiplicacao(struct Complex x,struct Complex y)
{
    struct Complex rmtx;

    // multiplicar as matrizes
    for(int i=0; i<1; i++){
            rmtx.real = (x.real * y.real) + (x.img * y.img) * (-1);
            rmtx.img = (x.real * y.img)  +  (x.img * y.real);
    }

    return rmtx;
}

/** Função produto_matricial()
* - Calcula produto matricial de duas matrizes complexas, representadas por ponteiros para ponteiros de struct Complex.
 * @param[in] Complex **matrix1, Complex **matrix2, linhas, colunas
 * @param[out] rmtx
*/

struct Complex **produto_matricial(struct Complex **matrix1,struct Complex **matrix2, int linhas, int colunas)
{
    struct Complex **rmtx, aux, sum;

    // aloca memória para a matriz de saída
    rmtx = (struct Complex **)malloc(linhas * sizeof(struct Complex *));

    for(int i=0; i<linhas; i++){
        rmtx[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));

    }

    if(linhas==colunas){

    // somar as matrizes
    for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
        sum.real = 0;
        sum.img = 0;
        for (int k = 0; k < colunas; k++) {
            aux = multiplicacao(matrix1[i][k], matrix2[k][j]);
            sum = somanc(sum, aux);
        }
        rmtx[i][j] = sum;
    }
    }
    }
    else{

            printf("ERRO!\n\n");
            printf("A operacao de Produto Matricial nao pode ser iniciada porque o numero de linhas e colunas nao coincidem.\n\n");

        }
    return rmtx;
}

/** Função teste_produto_matricial()
* - Verifica a validade da operação produto matricial de matrizes complexas. 
* - Não possui parâmetros de entrada e não retorna nenhum valor. 
*/

void teste_produto_matricial()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **matrix2;
    struct Complex **rmtx;

     printf("==========Teste da Operacao de produto matricial==========\n\n");

    // alocar memória para as matrizes

    if(linhas==colunas){

    matrix1 = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    matrix2 = (struct Complex **)malloc(linhas * sizeof(struct Complex *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
        matrix2[i] = (struct Complex *)malloc(colunas * sizeof(struct Complex));
    }

    // inicializar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matrix1[i][j].real = 1;
            matrix1[i][j].img = 1;
            matrix2[i][j].real = -1;
            matrix2[i][j].img = -1;
        }
    }

    // imprimir as matrizes operandas

    printf("Operando A:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", matrix1[i][j].real);
        }
        printf("\n\n");
    }

    printf("Operando B:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", matrix2[i][j].real);
        }
        printf("\n\n");
    }

    // formar o produto das matrizes usando a função auxiliar
    rmtx = produto_matricial(matrix1, matrix2, linhas, colunas);

    // imprimir o produto matricial
    printf("A soma das matrizes :\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f\t", rmtx[i][j].real);
        }
        printf("\n\n");
    }



    printf("Operando C:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n\n");
    }

    printf("Operando D:\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", matrix2[i][j].real, matrix2[i][j].img);
        }
        printf("\n\n");
    }

    // formar o produto das matrizes usando a função auxiliar
    rmtx = produto_matricial(matrix1, matrix2, linhas, colunas);

    // imprimir o produto matricial
    printf("A soma das matrizes :\n\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fj\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n\n");
    }

    // desalocar a memória alocada
    for(int i=0; i<linhas; i++){
        free(matrix1[i]);
        free(matrix2[i]);
        free(rmtx[i]);
    }
    free(matrix1);
    free(matrix2);
    free(rmtx);

    }

    else{rmtx = produto_matricial(matrix1, matrix2, linhas, colunas);}
}

/**### Função calc_svd()
* Executa o cálculo da decomposição SVD (Singular Value Decomposition) da parte real de uma matriz complexa.
* Onde: 
* - A função recebe como parâmetros uma matriz complexa de tamanho linhas X colunas.
* - Exibe um aviso caso a matriz em questão possua uma parte imaginária diferente de 0.
* - Verifica se o número de colunas é menor ou igual ao número de linhas.
* - Se a condição for verdadeira, significa que é possível realizar o cálculo da decomposição SVD.
* - Exibe a matriz U na tela, formatando-a como uma matriz.
* - Em seguida, exibe o vetor S, que contém os valores singulares, um por linha.
* - Por fim, exibe a matriz V na tela, formatando-a como uma matriz.
* - Todos os valores são obtidos utilizando as funções da biblioteca GSL.
* - Caso o número de colunas não for menor ou igual ao número de linhas, a função exibe uma mensagem informando que a operação não pode ser concluída porque o número de linhas é menor que o número de colunas.
* - Os elementos das matrizes e vetores são acessados e exibidos utilizando as funções gsl_matrix_get e gsl_vector_get da biblioteca GSL.
* - A função não retorna nenhum valor.
 * @param[in] Complex **matrix1, linhas, colunas

*/

void calc_svd(struct Complex **matrix, int linhas, int colunas)
{

    int i, j;
    // Verifica se há parte imaginária nos elementos da matriz
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            if(matrix[i][j].img != 0)
            {
                printf("Aviso: A função usará apenas a parte real da matriz\n\n");
            }
            break;
        }
        break;
    }

    // Alocação das matrizes e vetores necessários para o cálculo SVD
    gsl_matrix * A = gsl_matrix_alloc(linhas, colunas);
    gsl_matrix * V = gsl_matrix_alloc(colunas, colunas);
    gsl_vector * S = gsl_vector_alloc(colunas);
    gsl_vector * work = gsl_vector_alloc(colunas);

    printf("Matriz de entrada %d X %d:\n\n",linhas, colunas);
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            printf("%.2f\t", matrix[i][j].real);
            gsl_matrix_set(A, i, j, matrix[i][j].real);
        }
        printf("\n\n");
    }

    // Cálculo do SVD
    if(colunas<=linhas)
    {
        gsl_linalg_SV_decomp(A, V, S, work);
        printf("Matriz U:\n\n");
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            printf("%.2f\t", gsl_matrix_get(A, i, j));
        }
        printf("\n\n");
    }

    printf("Vetor S:\n\n");
    for (i = 0; i < colunas; i++)
    {
        printf("%.2f\n", gsl_vector_get(S, i));
    }
    printf("\n\n");

    printf("Matriz V:\n\n");
    for (i = 0; i < colunas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            printf("%.2f\t", gsl_matrix_get(V, i, j));
        }
        printf("\n\n");
    }
    }
    else
    {
        printf("A operacao nao pode ser concluída porque o numero de linhas eh menor que o numero de colunas\n\n");
    }
}

/** função teste_calc_svd()
* - Testa a função calc_svd() para a parte real de matrizes complexas. 
* - Não possui parâmetros de entrada e não retorna nenhum valor. 
*/

void teste_calc_svd()
{
    int i, j;
    srand(time(NULL)); 
    struct Complex **matrix1, **matrix2, **matrix3, **matrix4;

    printf("==========Teste da Operacao de SVD==========\n\n");

    int l1 = 3, c1 = 2;
    int l2 = 4, c2 = 4;
    int l3 = 6, c3 = 5;
    int l4 = 5, c4 = 6;

    // Alocação de memória para as matrizes
    matrix1 = (struct Complex **)malloc(l1 * sizeof(struct Complex *));
    matrix2 = (struct Complex **)malloc(l2 * sizeof(struct Complex *));
    matrix3 = (struct Complex **)malloc(l3 * sizeof(struct Complex *));
    matrix4 = (struct Complex **)malloc(l4 * sizeof(struct Complex *));
    for (int i = 0; i < l1; i++)
    {
        matrix1[i] = (struct Complex *)malloc(c1 * sizeof(struct Complex));
    }
    for (int i = 0; i < l2; i++)
    {
        matrix2[i] = (struct Complex *)malloc(c2 * sizeof(struct Complex));
    }
    for (int i = 0; i < l3; i++)
    {
        matrix3[i] = (struct Complex *)malloc(c3 * sizeof(struct Complex));
    }
    for (int i = 0; i < l4; i++)
    {
        matrix4[i] = (struct Complex *)malloc(c4 * sizeof(struct Complex));
    }

    // Inicialização das matrizes
    for (i = 0; i < l1; i++)
    {
        for (j = 0; j < c1; j++)
        {
            matrix1[i][j].real = (rand() % 5) - 5;
            matrix1[i][j].img = 0;
        }
    }

    for (i = 0; i < l2; i++)
    {
        for (j = 0; j < c2; j++)
        {
            matrix2[i][j].real = (rand() % 5) - 5;
            matrix2[i][j].img = 0;
        }
    }

    for (i = 0; i < l3; i++)
    {
        for (j = 0; j < c3; j++)
        {
            matrix3[i][j].real = (rand() % 5) - 5;
            matrix3[i][j].img = 0;
        }
    }

    for (i = 0; i < l4; i++)
    {
        for (j = 0; j < c4; j++)
        {
            matrix4[i][j].real = (rand() % 5) - 5;
            matrix4[i][j].img = 1;   //Aqui definimos a matrix complexa a ser testada
        }
    }

    calc_svd(matrix1, l1, c1); // Chamada da função calc_svd para matriz 3 X 2
    calc_svd(matrix2, l2, c2); // Chamada da função calc_svd para matriz 4 X 4
    calc_svd(matrix3, l3, c3); // Chamada da função calc_svd para matriz 6 X 5
    calc_svd(matrix4, l4, c4); // Chamada da função calc_svd para matriz 5 X 6
 // desalocar a memória alocada
    for(int i=0; i<l1; i++){
        free(matrix1[i]);
    }
    for(int i=0; i<l2; i++){
        free(matrix2[i]);
    }
    for(int i=0; i<l3; i++){
        free(matrix3[i]);
    }
    for(int i=0; i<l4; i++){
        free(matrix4[i]);
    }
    free(matrix1);
    free(matrix2);
    free(matrix3);
    free(matrix4);
}

void teste_todos()
{
    printf("==========Teste Global==========\n\n");

    //FUNÇÕES
    print_name();
    teste_soma();
    teste_subtracao();
    teste_transposta();
    teste_conjugada();
    teste_hermitiano();
    teste_produto_escalar();
    teste_produto_matricial();
    teste_calc_svd();
}
