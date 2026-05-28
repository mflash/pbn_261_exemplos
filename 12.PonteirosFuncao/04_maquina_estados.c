#include <stdio.h>

// Definição do tipo para a função de estado
typedef void (*EstadoFcn)(void);

// Declaração das funções de estado
void estadoParado(void);
void estadoExecutando(void);
void estadoBloqueado(void);

// Ponteiro global que armazena o estado atual
EstadoFcn estadoAtual = estadoParado;
int evento = 0; // Controla as transições no exemplo

void estadoParado() {
    printf("Estado: PARADO. Aguardando comando...\n");
    if (evento == 1) estadoAtual = estadoExecutando;
}

void estadoExecutando() {
    printf("Estado: EXECUTANDO. Processando dados...\n");
    if (evento == 2) estadoAtual = estadoBloqueado;
}

void estadoBloqueado() {
    printf("Estado: BLOQUEADO. Recuperando sistema...\n");
    if (evento == 0) estadoAtual = estadoParado;
}

int main() {
    // Simulação do laço de eventos
    estadoAtual();

    evento = 1; // Força transição para Executando
    estadoAtual();

    evento = 2; // Força transição para Bloqueado
    estadoAtual();

    return 0;
}

