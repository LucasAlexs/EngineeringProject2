#include <stdio.h>
#include <stdlib.h>
#include "matrizes.h"
#define tam 3

int soma(struct complexo a[][tam],struct complexo b[][tam], struct complexo result[][tam] );

int teste_soma();

int subtracao(struct complexo a[][tam],struct complexo b[][tam], struct complexo result[][tam] );

int teste_subtracao();

int transposta(struct complexo a[][tam], struct complexo result[][tam] );

int teste_transposta();

int conjulgada(struct complexo a[][tam], struct complexo result[][tam] );

int teste_conjulgada();

int soma(struct complexo a[][tam],struct complexo b[][tam], struct complexo result[][tam] )
{
    int i,j;
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                result[i][j].real = a[i][j].real + b[i][j].real;
                result[i][j].img = a[i][j].img + b[i][j].img;
            }
    }
    return 0;
}

int teste_soma()
{
    int i,j;

    struct complexo a[tam][tam] = { {{1, 0}, {3, 0}, {5, 0}},
                         {{7, 0}, {9, 0}, {11, 0}},
                         {{13, 0}, {15, 0}, {17, 0}} };
    struct complexo b[tam][tam] = { {{-1, 0}, {-3, 0}, {-5, 0}},
                         {{-7, 0}, {-9, 0}, {-11, 0}},
                         {{-13, 0}, {-15, 0}, {-17, 0}} };

    struct complexo c[tam][tam] = { {{1, 2}, {3, 4}, {5, 6}},
                         {{7, 8}, {9, 10}, {11, 12}},
                         {{13, 14}, {15, 16}, {17, 18}} };
    struct complexo d[tam][tam] = { {{-1, -2}, {-3, -4}, {-5, -6}},
                         {{-7, -8}, {-9, -10}, {-11, -12}},
                         {{-13, -14}, {-15, -16}, {-17, -18}} };

    struct complexo result[tam][tam];

    printf("--------------------------------------TESTE DA OPERACAO SOMA--------------------------------------\n");

    printf("Operando A:\n");

    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t%.2f ",a[i][j].real);
            }
            printf("\n");
    }

    printf("Operando B:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t%.2f ",b[i][j].real);
            }
            printf("\n");
    }

    soma(a, b, result);

    printf("Resultado (A + B):\n");

    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t%.2f ",result[i][j].real);
            }
            printf("\n");
    }

    printf("Operando C:\n");

    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ",c[i][j].real,c[i][j].img);
            }
            printf("\n");
    }

    printf("Operando D:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ",d[i][j].real,d[i][j].img);
            }
            printf("\n");
    }

    soma(c, d, result);

    printf("Resultado (C + D):\n");


    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t[(%.2f) + (%.2fi)]",result[i][j].real,result[i][j].img);
            }
            printf("\n");
    }

    return 0;

}

int subtracao(struct complexo a[][tam],struct complexo b[][tam], struct complexo result[][tam] )
{
    int i,j;
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                result[i][j].real = a[i][j].real - b[i][j].real;
                result[i][j].img = a[i][j].img - b[i][j].img;
            }
    }
    return 0;
}

int teste_subtracao()
{
    int i,j;

    struct complexo a[tam][tam] = { {{1, 0}, {3, 0}, {5, 0}},
                         {{7, 0}, {9, 0}, {11, 0}},
                         {{13, 0}, {15, 0}, {17, 0}} };
    struct complexo b[tam][tam] = { {{-1, 0}, {-3, 0}, {-5, 0}},
                         {{-7, 0}, {-9, 0}, {-11, 0}},
                         {{-13, 0}, {-15, 0}, {-17, 0}} };

    struct complexo c[tam][tam] = { {{1, 2}, {3, 4}, {5, 6}},
                         {{7, 8}, {9, 10}, {11, 12}},
                         {{13, 14}, {15, 16}, {17, 18}} };
    struct complexo d[tam][tam] = { {{-1, -2}, {-3, -4}, {-5, -6}},
                         {{-7, -8}, {-9, -10}, {-11, -12}},
                         {{-13, -14}, {-15, -16}, {-17, -18}} };

    struct complexo result[tam][tam];

    printf("------------------------------------TESTE DA OPERACAO SUBTRACAO------------------------------------\n");

    printf("Operando A:\n");

    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t%.2f ",a[i][j].real);
            }
            printf("\n");
    }

    printf("Operando B:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t%.2f ",b[i][j].real);
            }
            printf("\n");
    }

    subtracao(a, b, result);

    printf("Resultado (A - B):\n");

    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t%.2f ",result[i][j].real);
            }
            printf("\n");
    }

    printf("Operando C:\n");

    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ",c[i][j].real,c[i][j].img);
            }
            printf("\n");
    }

    printf("Operando D:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ",d[i][j].real,d[i][j].img);
            }
            printf("\n");
    }

    subtracao(c, d, result);

    printf("Resultado (C - D):\n");


    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t[(%.2f) + (%.2fi)]",result[i][j].real,result[i][j].img);
            }
            printf("\n");
    }

    return 0;

}

int transposta(struct complexo a[][tam], struct complexo result[][tam] )
{
    int i,j;
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                result[i][j].real = a[j][i].real;
                result[i][j].img = a[j][i].img;
            }
    }
    return 0;
}

int teste_transposta()
{
    int i,j;

    struct complexo a[tam][tam] = { {{1, 0}, {3, 0}, {5, 0}},
                         {{7, 0}, {9, 0}, {11, 0}},
                         {{13, 0}, {15, 0}, {17, 0}} };

    struct complexo b[tam][tam] = { {{-1, -2}, {-3, -4}, {-5, -6}},
                         {{-7, -8}, {-9, -10}, {-11, -12}},
                         {{-13, -14}, {-15, -16}, {-17, -18}} };


    struct complexo result[tam][tam];

    printf("------------------------------------TESTE DA OPERACAO TRANSPOSTA------------------------------------\n");

    printf("Operando A:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f)", a[i][j].real);
            }
            printf("\n");
    }

    transposta(a, result);

    printf("Transposta de A:\n");


    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f)", result[i][j].real);
            }
            printf("\n");
    }

     printf("Operando B:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ", b[i][j].real, b[i][j].img);
            }
            printf("\n");
    }

    transposta(b, result);

    printf("Transposta de B:\n");

    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ", result[i][j].real, result[i][j].img);
            }
            printf("\n");
    }

    return 0;

}

int conjulgada(struct complexo a[][tam], struct complexo result[][tam] )
{
    int i,j;
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                result[i][j].real = a[i][j].real;
                result[i][j].img = a[i][j].img * ( -1 );
            }
    }
    return 0;
}

int teste_conjulgada()
{
    int i,j;

    struct complexo a[tam][tam] = { {{1, 0}, {3, 0}, {5, 0}},
                         {{7, 0}, {9, 0}, {11, 0}},
                         {{13, 0}, {15, 0}, {17, 0}} };

    struct complexo b[tam][tam] = { {{-1, -2}, {-3, -4}, {-5, -6}},
                         {{-7, -8}, {-9, -10}, {-11, -12}},
                         {{-13, -14}, {-15, -16}, {-17, -18}} };


    struct complexo result[tam][tam];

    printf("------------------------------------TESTE DA OPERACAO CONJULGADA------------------------------------\n");

    printf("Operando A:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f)", a[i][j].real);
            }
            printf("\n");
    }

    conjulgada(a, result);

    printf("Conjulgada de A:\n");


    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f)", result[i][j].real);
            }
            printf("\n");
    }

     printf("Operando B:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ", b[i][j].real, b[i][j].img);
            }
            printf("\n");
    }

    conjulgada(b, result);

    printf("Conjulgada de B:\n");

    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ", result[i][j].real, result[i][j].img);
            }
            printf("\n");
    }

    return 0;
}

int hermitiano(struct complexo a[][tam], struct complexo result[][tam] )
{

    struct complexo i[tam][tam];

    transposta( a, i);
    conjulgada( i, result);

}

int teste_hermitiano()
{
    int i,j;

    struct complexo a[tam][tam] = { {{1, 0}, {3, 0}, {5, 0}},
                         {{7, 0}, {9, 0}, {11, 0}},
                         {{13, 0}, {15, 0}, {17, 0}} };

    struct complexo b[tam][tam] = { {{-1, -2}, {-3, -4}, {-5, -6}},
                         {{-7, -8}, {-9, -10}, {-11, -12}},
                         {{-13, -14}, {-15, -16}, {-17, -18}} };


    struct complexo result[tam][tam];

    printf("------------------------------------TESTE DA OPERACAO HERMITIANA------------------------------------\n");

    printf("Operando A:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f)", a[i][j].real);
            }
            printf("\n");
    }

    hermitiano(a, result);

    printf("Hermitiano de A:\n");


    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f)", result[i][j].real);
            }
            printf("\n");
    }

     printf("Operando B:\n");
    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ", b[i][j].real, b[i][j].img);
            }
            printf("\n");
    }

    hermitiano(b, result);

    printf("Hermitiano de B:\n");

    for( i = 0 ; i < tam ; i++ ){
            for( j = 0 ; j < tam ; j++ ){
                printf("\t(%.2f) + (%.2fi) ", result[i][j].real, result[i][j].img);
            }
            printf("\n");
    }

    return 0;
}
