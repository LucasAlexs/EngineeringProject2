#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#include <gsl/gsl_linalg.h>

// FUNCÕES

int teste_produto_matricial();


print_name()
{
    printf("=====Equipe=====\n\n");

        char name1[]= "LUCAS ALEXSANDRO LEAL DOS SANTOS";
        char name2[]= "GABRIEL DE JESUS DOS SANTOS COSTA";
        char name3[]= "SAULO MATTHEUS RIBEIRO DE OLIVEIRA";
        char name4[]= "JOSE HENRIQUE BARBOSA PENA";

        printf(" %s\n %s\n %s\n %s\n\n", name1,name2, name3, name4);
}

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

int teste_soma()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **matrix2;
    struct Complex **rmtx;

     printf("======Teste da Operacao de Soma========\n\n");
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
    return 0;
}

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

int teste_subtracao()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **matrix2;
    struct Complex **rmtx;

     printf("======Teste da Operacao de Subtracao========\n\n");
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
    return 0;
}


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

int teste_transposta()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **rmtx;

     printf("======Teste da Operacao transposta========\n\n");

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

    return 0;
}

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

int teste_conjugada()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **rmtx;

     printf("======Teste da Operacao conjugada========\n\n");

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

    return 0;
}

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

int teste_hermitiano()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **rmtx;

     printf("======Teste da Operacao hermitiano========\n\n");

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

    return 0;
}

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

int teste_produto_escalar(){
    int linhas = 3;
    struct Complex *vet1;
    struct Complex *vet2;
    struct Complex result;

     printf("======Teste da Operacao de Produto Escalar========\n\n");

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

    return 0;
}

struct Complex somanc(struct Complex a,struct Complex b) {

    struct Complex result;

    result.real = a.real + b.real;
    result.img = a.img + b.img;

    return result;
}

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

int teste_produto_matricial()
{
    int linhas = 3;
    int colunas = 3;
    struct Complex **matrix1;
    struct Complex **matrix2;
    struct Complex **rmtx;

     printf("======Teste da Operacao de produto matricial========\n\n");

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


    return 0;
}

calc_svd(struct Complex **matrix, int linhas, int colunas)
{
    int i, j;

    // Verifica se há parte imaginária nos elementos da matriz
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            if (matrix[i][j].img != 0)
            {
                printf("Aviso: A função usará apenas a parte real da matriz\n");
                break;
            }
        }
    }

    // Alocação das matrizes e vetores necessários para o cálculo SVD
    gsl_matrix *A = gsl_matrix_alloc(linhas, colunas);
    gsl_matrix *V = gsl_matrix_alloc(colunas, colunas);
    gsl_vector *S = gsl_vector_alloc(colunas);
    gsl_vector *work = gsl_vector_alloc(colunas);
    
    printf("\n Matriz operanda:\n");
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            printf("%.2f ", matrix[i][j].real);
            gsl_matrix_set(A, i, j, matrix[i][j].real);
        }
        printf("\n");
    }

    // Cálculo do SVD
    gsl_linalg_SV_decomp(A, V, S, work);

    printf("\n Matriz U:\n");
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            printf("%f ", gsl_matrix_get(A, i, j));
        }
        printf("\n");
    }

    printf("\n Vetor S\n");
    for (i = 0; i < colunas; i++)
    {
        printf("%f\n", gsl_vector_get(S, i));
    }

    printf("\n\nMatriz V\n");
    for (i = 0; i < colunas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            printf("%f ", gsl_matrix_get(V, i, j));
        }
        printf("\n");
    }
}

void teste_calc_svd()
{
    int i, j;
    struct Complex **matrix1, **matrix2, **matrix3, **matrix4;

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
            matrix1[i][j].real = i * j;
            matrix1[i][j].img = 0;
        }
    }

    for (i = 0; i < l2; i++)
    {
        for (j = 0; j < c2; j++)
        {
            matrix2[i][j].real = j - i;
            matrix2[i][j].img = 0;
        }
    }

    for (i = 0; i < l3; i++)
    {
        for (j = 0; j < c3; j++)
        {
            matrix3[i][j].real = 1 - 4 * j;
            matrix3[i][j].img = 4;
        }
    }

    for (i = 0; i < l4; i++)
    {
        for (j = 0; j < c4; j++)
        {
            matrix4[i][j].real = 1 + i;
            matrix4[i][j].img = i - 3 + 2 * j;
        }
    }

    // Chamadas da função calc_svd para cada matriz
    calc_svd(matrix1, l1, c1);
    calc_svd(matrix2, l2, c2);
    calc_svd(matrix3, l3, c3);
    calc_svd(matrix4, l4, c4);
}

teste_todos()
{
    printf("======Teste Geral========\n\n");

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

