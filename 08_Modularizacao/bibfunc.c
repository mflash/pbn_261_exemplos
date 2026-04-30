#include "bibfunc.h"

long fatorial(int v)
{
    long fat = 1;
    for(int i=1; i<=v; i++)
        fat = fat * i;
    return fat;
}

long somatorio(int v)
{
    //return (v*(v+1))/2;
    long soma = 0;
    for(int i=1; i<=v; i++)
        soma += i;
    return soma;
}