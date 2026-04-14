#include <stdio.h>

typedef union
{
    unsigned int v;
    unsigned char b[4];
} ValorInt;

int main()
{
    ValorInt v1;
    v1.v = 255; // atribuindo um int (4 bytes)
    printf("Valor int: %u\n", v1.v);
    printf("Valor no vetor: ");
    for(int i=0; i<4; i++)
        printf("%d ", v1.b[i]);
    printf("\n");
    v1.b[1] = 255; 
    v1.b[2] = 255;
    v1.b[3] = 255;
    printf("Valor int: %u\n", v1.v);
}