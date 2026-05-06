#include <stdio.h>

void elimina(int* v, int posicao, int *qtd);
void exibe(int v[], int qtd);

void elimina(int* v, int posicao, int *qtd) { // 1 - qtd por ref
    int* start = v + posicao;
    int* end = v + *qtd;  // 2 - qtd por ref + v (início do vetor)
    while(start < end) { // 3 - para não passar do final
        *(start) = *(start+1); // 4 - estava invertido
        start++;
    }
    (*qtd)--; // 5 - não estava diminuindo a qtd por ref
}

void exibe(int v[], int qtd) {
    for(int i=0; i<qtd; i++)
        printf("%d ", v[i]);
    printf("\n");
}

int main() {
    int vetor[50] = { 1,2,3,4,5,6,7 };
    int qtdElementos = 7;
    exibe(vetor, qtdElementos);
    elimina(&vetor[1], 3, &qtdElementos); // { 1,2,3,4,6,7 }
    exibe(vetor, qtdElementos);
    elimina(&vetor[5], 0, &qtdElementos); // { 1,2,3,4,6 }
    exibe(vetor, qtdElementos);
}