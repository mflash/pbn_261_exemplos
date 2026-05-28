#include <stdio.h>
#include <stdbool.h>

typedef bool (*Predicado)(int);

bool ehPar(int n) {
    return n % 2 == 0;
}
bool ehPositivo(int n) {
    return n > 0;
}

// Filtra o vetor original e preenche o vetor de saída com base no critério do ponteiro
int filtrar(const int *entrada, int tamanho, int *saida, Predicado criterio) {
    int contagem = 0;
    for (int i = 0; i < tamanho; i++) {
        if (criterio(entrada[i])) {
            saida[contagem] = entrada[i];
            contagem++;
        }
    }
    return contagem; // Retorna o número de elementos inseridos
}

int main() {
    int valores[] = {-3, -2, -1, 0, 1, 2, 3, 4};
    int n = sizeof(valores) / sizeof(valores[0]);
    int resultado[8];

    int n_filtrados = filtrar(valores, n, resultado, ehPar);
    printf("Elementos pares: ");
    for (int i = 0; i < n_filtrados; i++) printf("%d ", resultado[i]);
    printf("\n");

    n_filtrados = filtrar(valores, n, resultado, ehPositivo);
    printf("Elementos positivos: ");
    for (int i = 0; i < n_filtrados; i++) printf("%d ", resultado[i]);
    printf("\n");

    return 0;
}
