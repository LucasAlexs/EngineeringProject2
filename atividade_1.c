#include <stdio.h>
#include <stdlib.h>

int main()
{
    char str[]= "NOME DO ALUNO";

    //nome aqui
    char name1[]= "LUCAS ALEXSANDRO LEAL DOS SANTOS;";
    char name2[]= "GABRIEL DE JESUS DOS SANTOS COSTA;";
    char name3[]= "SAULO MATTHEUS RIBEIRO DE OLIVEIRA;";
    char name4[]= "JOSE HENRIQUE BARBOSA PENA;";

    char str2[]= "MATRICULA";

    //matricula aqui
    char * matri1= "(202207040035)";
    char * matri2= "(202206840044)";
    char * matri3= "(202206840041)";
    char * matri4= "(202206840036)";

    char divisoria[]= "------------------------------------";
    char divisoria2[]= " --------------";

    printf(" \t %s \t", str);
    printf("\t\t %s \n\n", str2);
    printf("%s \t", divisoria);
    printf("%s \n", divisoria2);
    printf("%s \t %s \n", name1, matri1);
    printf("%s \t %s \n", name2, matri2);
    printf("%s \t %s \n", name3, matri3);
    printf("%s \t %s \n", name4, matri4);
    
    //eh okay
    
    return 0;
}
