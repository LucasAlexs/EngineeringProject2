#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#define tam 3

// MATRIZ TESTE (CADA ELEMENTO DA MATRIZ É UM VETOR)
struct ComplexNumber a[tam][tam] = { {{5,2},{7,-3},{9,1}   }  ,   {   {1,-6},{-5,3},{4,7}    }   ,   {   {2,5},{1,4},{-9,-3} }   };
struct ComplexNumber b[tam][tam] = { {{7,-5},{3,-1},{1,-6} }    ,   {   {4,2},{-1,1},{2,9}   }   ,   {   {3,8},{2,4},{8,8}   }  };
struct ComplexNumber c[tam][tam] = { {{1,-2},{-3,-3},{1,8}   }  ,   {    {7,3},{0,2},{7,1}   }   ,   {   {2,3},{9,2},{-1,-5} }    };
struct ComplexNumber d[tam][tam] = { {{6,-4},{-8,1},{3,1}  } ,   { {7,2},{1,9},{2,6}   }   ,   {   {6,6},{3,11},{-23,-1}   }  };
struct ComplexNumber result[tam][tam];

// FUNCÕES
int print_name();
struct ComplexNumber **soma(struct ComplexNumber **matrix1,struct ComplexNumber **matrix2, int linhas, int colunas);
int teste_soma();

struct ComplexNumber **subtracao(struct ComplexNumber **matrix1,struct ComplexNumber **matrix2, int linhas, int colunas);
int teste_subtracao();

struct ComplexNumber **transposta(struct ComplexNumber **matrix1, int linhas, int colunas);
int teste_transposta();

struct ComplexNumber **conjulgado(struct ComplexNumber **matrix1, int linhas, int colunas);
int teste_conjugada();

struct ComplexNumber **hermitiano(struct ComplexNumber **matrix1, int linhas, int colunas);
int teste_hermitiana();

struct ComplexNumber produto_escalar(struct ComplexNumber *vet1,struct ComplexNumber *vet2, int neu, int nev);
int teste_produto_escalar();

int produto_matricial(struct ComplexNumber a[][tam], struct ComplexNumber b[][tam], struct ComplexNumber result[][tam]);
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

struct ComplexNumber **soma(struct ComplexNumber **matrix1,struct ComplexNumber **matrix2, int linhas, int colunas)
{
    struct ComplexNumber **rmtx;

    // aloca memória para a matriz de saída
    rmtx = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
        rmtx[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
    }

    // somar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            rmtx[i][j].real = matrix1[i][j].real + matrix2[i][j].real;
            rmtx[i][j].img = matrix1[i][j].img + matrix2[i][j].img;
        }
    }

    return rmtx;
}

int teste_soma()
{
    int linhas = 3;
    int colunas = 3;
    struct ComplexNumber **matrix1;
    struct ComplexNumber **matrix2;
    struct ComplexNumber **rmtx;

     printf("======Teste da Operacao de Soma========\n\n");

    // alocar memória para as matrizes
    matrix1 = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    matrix2 = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
        matrix2[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
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
    printf("operando A:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n");
    }

    printf("operando B:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", matrix2[i][j].real, matrix2[i][j].img);
        }
        printf("\n");
    }

    // somar as matrizes usando a função auxiliar
    rmtx = soma(matrix1, matrix2, linhas, colunas);

    // imprimir a soma das matrizes
    printf("A soma das matrizes :\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n");
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

    return 0;
}

struct ComplexNumber **subtracao(struct ComplexNumber **matrix1,struct ComplexNumber **matrix2, int linhas, int colunas)
{
    struct ComplexNumber **rmtx;

    // aloca memória para a matriz de saída
    rmtx = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
        rmtx[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
    }

    // somar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            rmtx[i][j].real = matrix1[i][j].real - matrix2[i][j].real;
            rmtx[i][j].img = matrix1[i][j].img - matrix2[i][j].img;
        }
    }

    return rmtx;
}

int teste_subtracao()
{
    int linhas = 3;
    int colunas = 3;
    struct ComplexNumber **matrix1;
    struct ComplexNumber **matrix2;
    struct ComplexNumber **rmtx;

     printf("======Teste da Operacao de Subtracao========\n\n");

    // alocar memória para as matrizes
    matrix1 = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    matrix2 = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
        matrix2[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
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
    printf("operando A:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n");
    }

    printf("operando B:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", matrix2[i][j].real, matrix2[i][j].img);
        }
        printf("\n");
    }

    // somar as matrizes usando a função auxiliar
    rmtx = subtracao(matrix1, matrix2, linhas, colunas);

    // imprimir a soma das matrizes
    printf("A subtracao das matrizes :\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n");
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

    return 0;
}


struct ComplexNumber **transposta(struct ComplexNumber **matrix1, int linhas, int colunas)
{
   struct ComplexNumber **rmtx;
   int i,j;

    // aloca memória para a matriz de saída
    rmtx = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
        rmtx[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
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
    struct ComplexNumber **matrix1;
    struct ComplexNumber **rmtx;

     printf("======Teste da Operacao transposta========\n\n");

    // alocar memória para a matrizes
    matrix1 = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
    }

    // inicializar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matrix1[i][j].real = i;
            matrix1[i][j].img = j;
        }
    }

    // imprimir a matrize operando
    printf("operando A:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n");
    }

    // fazer a matriz transposta usando a função auxiliar
    rmtx = transposta(matrix1, linhas, colunas);

    // imprimir a matriz transposta
    printf("a transposta da matriz:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n");
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

struct ComplexNumber **conjulgado(struct ComplexNumber **matrix1, int linhas, int colunas)
{
   struct ComplexNumber **rmtx;
   int i,j;

    // aloca memória para a matriz de saída
    rmtx = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
        rmtx[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
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

int teste_conjulgada()
{
    int linhas = 3;
    int colunas = 3;
    struct ComplexNumber **matrix1;
    struct ComplexNumber **matrix2;
    struct ComplexNumber **rmtx;

     printf("======Teste da Operacao conjulgada========\n\n");

    // alocar memória para a matrizes
    matrix1 = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
    }

    // inicializar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matrix1[i][j].real = 1;
            matrix1[i][j].img = 1;
        }
    }

    // imprimir a matrize operando
    printf("operando A:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n");
    }

    // fazer a matriz conjulgada usando a função auxiliar
    rmtx = conjulgado(matrix1, linhas, colunas);

    // imprimir o conjulgada da matriz
    printf("a conjulgada da matriz:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n");
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

    return 0;
}

struct ComplexNumber **hermitiano(struct ComplexNumber **matrix1, int linhas, int colunas)
{
   struct ComplexNumber **rmtx, **aux;
   int i,j;

    // aloca memória para a matriz de saída
    rmtx = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    aux = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
         rmtx[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
         aux[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
    }

   for(i = 0; i < linhas; i++)
   {
       for(j = 0; j < colunas; j++)
       {
           aux=transposta(matrix1,linhas,colunas);
           rmtx=conjulgado(matrix1,linhas,colunas);
       }
   }
   return rmtx;
}

int teste_hermitiano()
{
    int linhas = 3;
    int colunas = 3;
    struct ComplexNumber **matrix1;
    struct ComplexNumber **matrix2;
    struct ComplexNumber **rmtx;

     printf("======Teste da Operacao hermitiano========\n\n");

    // alocar memória para a matrizes
    matrix1 = (struct ComplexNumber **)malloc(linhas * sizeof(struct ComplexNumber *));
    for(int i=0; i<linhas; i++){
        matrix1[i] = (struct ComplexNumber *)malloc(colunas * sizeof(struct ComplexNumber));
    }

    // inicializar as matrizes
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            matrix1[i][j].real = i;
            matrix1[i][j].img = j;
        }
    }

    // imprimir a matrize operando
    printf("operando A:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", matrix1[i][j].real, matrix1[i][j].img);
        }
        printf("\n");
    }

    // fazer a matriz hermitiana usando a função auxiliar
    rmtx = hermitiano(matrix1, linhas, colunas);

    // imprimir o hermitiano da matriz
    printf(") hermitiano da matriz:\n");
    for(int i=0; i<linhas; i++){
        for(int j=0; j<colunas; j++){
            printf("%.2f + %.2fi\t", rmtx[i][j].real, rmtx[i][j].img);
        }
        printf("\n");
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

    return 0;
}

struct ComplexNumber multiplicacao(struct ComplexNumber x,struct ComplexNumber y)
{
    struct ComplexNumber rmtx;

    // multiplicar as matrizes
    for(int i=0; i<1; i++){
            rmtx.real = (x.real * y.real) + (x.img * y.img) * (-1);
            rmtx.img = (x.real * y.img)  +  (x.img * y.real);
    }

    return rmtx;
}

struct ComplexNumber produto_escalar(struct ComplexNumber *vet1,struct ComplexNumber *vet2, int neu, int nev)
{
    struct ComplexNumber rmtx, aux;

    rmtx.real= 0;
    rmtx.img= 0;

    if(neu == nev){
    // multiplicar as matrizes
    for(int i=0; i<neu; i++){
            aux= multiplicacao(vet1[i],vet2[i]);
            rmtx.real = rmtx.real + aux.real;
            rmtx.img = rmtx.img + aux.img;
    }

    }

    else{
            printf("impossivel calcular o produto escalar entre estes vetores.");
    }

    return rmtx;
}

int teste_produto_escalar(){
    int linhas = 3;
    struct ComplexNumber *vet1;
    struct ComplexNumber *vet2;
    struct ComplexNumber result;

     printf("======Teste da Operacao produto escalar========\n\n");

    // alocar memória para a matrizes
    vet1 = (struct ComplexNumber *)malloc(linhas * sizeof(struct ComplexNumber ));
    vet2 = (struct ComplexNumber *)malloc(linhas * sizeof(struct ComplexNumber ));

    // inicializar os vetores
    for(int i=0; i<linhas; i++){
            vet1[i].real = 1;
            vet1[i].img = 1;
            vet2[i].real = 1;
            vet2[i].img = 1;
    }

    // imprimir os vetores operandos
    printf("operando A:\n");
    for(int i=0; i<linhas; i++){
            printf("%.2f + %.2fi\t",vet1[i].real, vet1[i].img);
    }

    printf("\n");

    printf("operando B:\n");
    for(int i=0; i<linhas; i++){
            printf("%.2f + %.2fi\t",vet2[i].real, vet2[i].img);
    }

    printf("\n");

    // fazer a matriz conjulgada usando a função auxiliar
    result = produto_escalar(vet1, vet2, linhas,linhas);

    // imprimir o conjulgada da matriz
    printf("a conjulgada da matriz:\n");
    printf("%.2f + %.2fi\t", result.real, result.img);
    printf("\n");

    // desalocar a memória alocada
    free(vet1);
    free(vet2);

    return 0;
}

int produto_matricial(struct ComplexNumber a[][tam], struct ComplexNumber b[][tam], struct ComplexNumber result[][tam])
{
        int i,j;
        for(i = 0 ; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
               result[i][j].real = a[i][j].real * b [j][i].real;
               result[i][j].img = a[i][j].img * b [j][i].img;
            }
        }
}

int teste_produto_matricial()
{
    int i,j;
    printf("======Teste do Produto Matricial========\n\n");
    printf("Operando A:\n\n");
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
            {
                printf("\t%.2f",a[i][j].real);
            }
        printf("\n");
    }
    printf("\n");
    printf("Operando B:\n\n");
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
            {
                printf("\t%.2f",b[i][j].real);
            }
        printf("\n");
    }
    printf("\n");
    produto_matricial(a,b,result);
    printf("Produto dos elementos de A e B:\n\n");
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
            {
                printf("\t%.2f",result[i][j].real);
            }
        printf("\n");
    }
     printf("\n");
    printf("Operando C:\n\n");
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
            {
                printf("\t(%.2f) + (%.2fi)",c[i][j].real,c[i][j].img);
            }
        printf("\n");
    }
    printf("\n");
    printf("Operando D:\n\n");
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
            {
                printf("\t(%.2f) + (%.2fi)",d[i][j].real,d[i][j].img);
            }
        printf("\n");
    }
    printf("\n");
    produto_matricial(c,d,result);
    printf("Produto Matricial de C * D:\n\n");
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
            {
                printf("\t%.2f",result[i][j].real+result[i][j].img); //AQUI NÃO IMPLEMENTEI A SOMA REAL + IMG DIRETO NA FUNÇÃO
            }
        printf("\n");
    }
    printf("\n");
}

teste_todos()
{
    printf("======Teste Geral========\n\n");
    //MATRIZ PARA TESTE GERAL
    struct ComplexNumber x[tam][tam] = { {{5,2},{7,-3},{9,1}   }  ,   {   {1,-6},{-5,3},{4,7}    }   ,   {   {2,5},{1,4},{-9,-3} }   };
    struct ComplexNumber y[tam][tam] = { {{5,2},{7,-3},{9,1}   }  ,   {   {1,-6},{-5,3},{4,7}    }   ,   {   {2,5},{1,4},{-9,-3} }   };

    //FUNÇÕES
    teste_soma();
    teste_subtracao();
    teste_transposta();
    teste_conjugada();
    teste_hermitiana();
    teste_produto_escalar();
    teste_produto_matricial();
}

