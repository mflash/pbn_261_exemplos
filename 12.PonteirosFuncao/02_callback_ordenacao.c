#include <stdio.h>

// Definição do tipo para simplificar a sintaxe
typedef int (*Comparador)(int, int);

int ascendente(int a, int b) {
    return a - b;
}
int descendente(int a, int b) {
    return b - a;
}

void ordenar(int *vetor, int tamanho, Comparador comp) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (comp(vetor[i], vetor[j]) > 0) {
                int temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
}

void imprimir(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) printf("%d ", vetor[i]);
    printf("\n");
}

int main() {
    int dados[] = {5, 2, 9, 1, 56};
    int n = sizeof(dados) / sizeof(dados[0]);

    ordenar(dados, n, ascendente);
    imprimir(dados, n);

    ordenar(dados, n, descendente);
    imprimir(dados, n);

    return 0;
}
