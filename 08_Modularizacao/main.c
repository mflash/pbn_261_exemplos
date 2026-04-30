#include <stdio.h>
#include "bibfunc.h"

int main()
{
    int valor;
    printf("Digite um valor inteiro: ");
    scanf("%d", &valor);
    long f = fatorial(valor);
    long s = somatorio(valor);
    printf("Fatorial:  %ld\n", f);
    printf("Somatorio: %ld\n", s);
}