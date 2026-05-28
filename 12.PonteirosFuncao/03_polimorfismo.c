#include <stdio.h>

// Definição da estrutura que simula uma "interface" ou "classe abstrata"
typedef struct Botao {
    char label[20];
    void (*click)(void); // Ponteiro para a função de comportamento
} Botao;

void acaoConfiguracoes() {
    printf("Abriu o menu de configuracoes.\n");
}

void acaoSair() {
    printf("Encerrando o programa.\n");
}

int main() {
    Botao btn1 = {"Configurar", acaoConfiguracoes};
    Botao btn2 = {"Sair", acaoSair};

    // Execução do comportamento dinâmico associado ao objeto
    printf("Clicando no botao 1 (%s): ", btn1.label);
    btn1.click();

    printf("Clicando no botao 2 (%s): ", btn2.label);
    btn2.click();

    return 0;
}
