#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str[]= "NOME DO ALUNO";

    char name1[]= "LUCAS ALEXSANDRO LEAL DOS SANTOS:";
    char name2[]= "SAULO MATTHEUS RIBEIRO DE OLIVEIRA:";
    char name3[]= "JOSE HENRIQUE BARBOSA PENA:";
    char name4[]= "GABRIEL DE JESUS DOS SANTOS COSTA:";

    char str2[]= "MATRICULA";

    char * matri1= "(202207040035)";
    char * matri2= "(202206840041)";
    char * matri3= "(202206840036)";
    char * matri4= "(202206840044)";

    char divisoria[]= "------------------------------------";
    char divisoria2[]= " --------------";

    printf(" \t %s \t", str);
    printf("\t\t %s \n\n", str2);
    printf("%s \t", divisoria);
    printf("%s \n", divisoria2);
    printf("%s \t %s \n", name1, matri1);
    printf("%s \t %s \n", name2, matri2);
    printf("%s \t\t %s \n", name3, matri3);
    printf("%s \t %s \n", name4, matri4);

    return 0;
}
