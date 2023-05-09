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
int soma(struct ComplexNumber a[][tam], struct ComplexNumber b[][tam], struct ComplexNumber result[][tam]);
int teste_soma();

int subtracao(struct ComplexNumber a[][tam], struct ComplexNumber b[][tam], struct ComplexNumber result[][tam]);
int teste_subtracao();

int transposta(struct ComplexNumber a[][tam],struct ComplexNumber result[][tam]);
int teste_transposta();

int conjugada(struct ComplexNumber a[][tam],struct ComplexNumber result[][tam]);
int teste_conjugada();

int hermitiana(struct ComplexNumber a[][tam],struct ComplexNumber result[][tam]);
int teste_hermitiana();

int produto_escalar(struct ComplexNumber a[][tam], struct ComplexNumber b[][tam], struct ComplexNumber result[][tam]);
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

int soma(struct ComplexNumber a[][tam], struct ComplexNumber b[][tam], struct ComplexNumber result[][tam])
{
    int i,j;
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
            {
                result[i][j].real = a[i][j].real + b[i][j].real;
                result[i][j].img = a[i][j].img + b[i][j].img;
            }
    }
    return 0;
}

int teste_soma()
{
    int i,j;
    printf("======Teste da Operacao de Soma========\n\n");
    printf("Operando A:\n\n");

     for(i = 0;i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                    printf("\t%.2f ",a[i][j].real);
                }
                printf("\n");
        }
        printf("\n");

    printf("Operando B:\n\n");

     for(i = 0;i < tam; i++)
        {
            for(j = 0; j < tam; j++)
                {
                    printf("\t%.2f ",b[i][j].real);
                }
                printf("\n");
        }
        printf("\n");

    soma(a,b,result);

     printf("Resultado A + B: \n\n");

     for(i = 0;i < tam; i++)
        {
            for(j = 0; j < tam; j++)
                {
                    printf("\t%.2f ",result[i][j].real);
                }
                printf("\n");
        }
        printf("\n\n");

    printf("Operando C:\n\n");

    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
                {
                    printf("\t(%.2f) + (%.2fi)",c[i][j].real,c[i][j].img);
                }
                printf("\n");
        }
    printf("\n\n");

    printf("Operando D:\n\n");

    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
                {
                    printf("\t(%.2f) + (%.2fi)",d[i][j].real,d[i][j].img);
                }
                printf("\n");
        }
        printf("\n\n");


    soma(c,d,result);
     printf("Resultado C + D: \n\n");

     for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
                {
                    printf("\t[(%.2f) + (%.2fi)]",result[i][j].real,result[i][j].img);
                }
                printf("\n");
        }
        printf("\n\n");




    return 0;
}

int subtracao(struct ComplexNumber a[][tam], struct ComplexNumber b[][tam], struct ComplexNumber result[][tam])
{
    int i,j;
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
                {
                    result[i][j].real = a[i][j].real - b[i][j].real;
                    result[i][j].img = a[i][j].img - b[i][j].img;
                }
        }
    return 0;
}

int teste_subtracao()
{
    int i,j;
    printf("======Teste da Operacao de Subtracao========\n\n");
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

    subtracao(a,b,result);
    printf("Resultado A - B:\n\n");

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
                printf("\t(%.2f) + (%.2f)i",c[i][j].real,c[i][j].img);
            }
        printf("\n");
    }
    printf("\n");

    printf("Operando D:\n\n");

    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
            {
                printf("\t(%.2f) + (%.2f)i",d[i][j].real,d[i][j].img);
            }
        printf("\n");
    }
    printf("\n");

    subtracao(c,d,result);
    printf("Resultado C - D:\n\n");

    for(i = 0; i < tam; i++)
        {
            for(j = 0 ; j < tam; j++)
            {
                    printf("\t[(%.2f) + (%.2fi)]",result[i][j].real, result[i][j].img);
            }
            printf("\n");
        }
        printf("\n");



}

int transposta(struct ComplexNumber a[][tam],struct ComplexNumber result[][tam])
{

    int i,j;
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                result[i][j].real = a[j][i].real;
                result[i][j].img = a[j][i].img;
            }
        }
    return 0;
}
int teste_transposta()
{
    int i,j;
    printf("======Teste da Operacao Transposta======\n\n");
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
    printf("Transposta de A:\n\n");
    transposta(a,result);
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                printf("\t%.2f",result[i][j].real);
            }
            printf("\n");
        }
        printf("\n");

printf("Operando B:\n\n");
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                printf("\t(%.2f) + (%.2fi)",b[i][j].real,b[i][j].img);
            }
            printf("\n");
        }
        printf("\n");
    printf("Transposta de B:\n\n");
    transposta(b,result);
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                printf("\t(%.2f) + (%.2fi)",result[i][j].real,result[i][j].img);
            }
            printf("\n");
        }
    printf("\n");
}

int conjugada(struct ComplexNumber a[][tam],struct ComplexNumber result[][tam])
{


   int i,j;
   for(i = 0; i < tam; i++)
   {
       for(j = 0; j < tam; j++)
       {
           result[i][j].img = a[i][j].img * (-1);
           result[i][j].real = a[i][j].real;
       }
   }
   return 0;
}
int teste_conjugada()
{


    int i,j;
    printf("======Teste da Conjugada========\n\n");
    printf("Operando A:\n\n");
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                printf("\t%.2fi",b[i][j].img);
            }
            printf("\n");
        }
        printf("\n");
    printf("Conjugada de A:\n\n");
    conjugada(b,result);
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                printf("\t%.2fi",result[i][j].img);
            }
            printf("\n");
        }
        printf("\n");

printf("Operando B:\n\n");
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                printf("\t(%.2f) + (%.2fi)",b[i][j].real,b[i][j].img);
            }
            printf("\n");
        }
        printf("\n");
    printf("Conjugada de B:\n\n");
    conjugada(b,result);
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                printf("\t(%.2f) + (%.2fi)",result[i][j].real,result[i][j].img);
            }
            printf("\n");
        }
        printf("\n");

}
int hermitiana(struct ComplexNumber a[][tam],struct ComplexNumber result[][tam])
{


    struct ComplexNumber i[tam][tam];
   transposta( a, i);
   conjugada( i, result);

    return 0;

}
int teste_hermitiana()
{
    printf("======Teste da Hermitiana========\n\n");
    int i,j;
    printf("Operando A:\n\n");
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
        {
            printf("\t%.2fi",a[i][j].img);
        }
        printf("\n");
    }
    printf("\n");
    printf("Hermitiana de A:\n\n");
    hermitiana(a,result);
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
            {
                printf("\t%.2fi",result[i][j].img);
            }
            printf("\n");
        }
    printf("\n");
    printf("Operando B:\n\n");
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam ; j++)
                {
                    printf("\t(%.2f) + (%.2fi)",a[i][j].real,a[i][j].img);
                }
            printf("\n");
        }
    printf("\n");
    printf("Hermitiana de B:\n\n");
    for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
                {
                    printf("\t(%.2f) + (%.2fi)",result[i][j].real,result[i][j].img);
                }
                printf("\n");
        }
    printf("\n");
    return 0;


}
int produto_escalar(struct ComplexNumber a[][tam], struct ComplexNumber b[][tam], struct ComplexNumber result[][tam])
{
        int i,j;
        for(i = 0; i < tam; i++)
        {
            for(j = 0; j < tam; j++)
                {
                    result[i][j].real = ((a[i][j].real) * (b[i][j].real));
                    result[i][j].img = ((a[i][j].img) * (b[i][j].img));

                }
        }



        return 0;
}
int teste_produto_escalar()
{
    int i,j;
    printf("======Teste do Produto Escalar========\n\n");
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
    produto_escalar(a,b,result);
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
    produto_escalar(c,d,result);
    printf("Produto Escalar de C * D:\n\n");
    for(i = 0; i < tam; i++)
    {
        for(j = 0; j < tam; j++)
            {
                printf("\t(%.2f)",result[i][j].real + result[i][j].img); //AQUI NÃO IMPLEMENTEI A SOMA REAL + IMG DIRETO NA FUNÇÃO
            }
        printf("\n");
    }
    printf("\n");
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

