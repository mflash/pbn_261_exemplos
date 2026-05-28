#include <stdio.h>

void abrir() {
    printf("Abrindo arquivo...\n");
}
void salvar() {
    printf("Salvando arquivo...\n");
}
void fechar() {
    printf("Fechando arquivo...\n");
}

int main() {
    // Vetor de ponteiros de função que não recebem argumentos e retornam void
    void (*menu[])() = {abrir, salvar, fechar};

    int opcao;
    printf("Digite 0 para Abrir, 1 para Salvar, 2 para Fechar: ");
    if (scanf("%d", &opcao) == 1 && opcao >= 0 && opcao <= 2) {
        menu[opcao](); // Chamada direta via índice
    }

    return 0;
}
