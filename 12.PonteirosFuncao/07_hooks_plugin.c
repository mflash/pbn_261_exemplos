#include <stdio.h>

// Definição do ponteiro de função para o Hook
typedef void (*HookPreEnvio)(const char *mensagem);

// Ponteiro global que agirá como o plugin registrado
HookPreEnvio pluginPreEnvio = NULL;

// Função para o usuário registrar o plugin customizado
void registrarPlugin(HookPreEnvio novoHook) {
    pluginPreEnvio = novoHook;
}

// Extensão externa (Plugin) desenvolvida pelo usuário
void pluginCriptografia(const char *msg) {
    printf("[PLUGIN] Criptografando logs antes de transmitir...\n");
}

// Núcleo do sistema (Core)
void processarEnvio(const char *dados) {
    // Executa o hook se algum plugin estiver acoplado
    if (pluginPreEnvio != NULL) {
        pluginPreEnvio(dados);
    }
    printf("[CORE] Transmitindo payload: %s\n", dados);
}

int main() {
    printf("--- Execução sem Plugin ---\n");
    processarEnvio("Texto Puro");

    printf("\n--- Execução com Plugin Acoplado ---\n");
    registrarPlugin(pluginCriptografia);
    processarEnvio("Texto Puro");

    return 0;
}

