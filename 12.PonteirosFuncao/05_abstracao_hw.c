#include <stdio.h>

// Estrutura que define a interface do driver de comunicação
typedef struct {
    void (*inicializar)(void);
    void (*enviar)(const char *dados);
} DriverComunicacao;

// Implementação para o Hardware Comercial A
void initHardwareA() { printf("HW A: Inicializando pinos do dispositivo.\n"); }
void enviarHardwareA(const char *d) { printf("HW A: Transmitindo: %s\n", d); }

// Implementação para o Hardware Comercial B
void initHardwareB() { printf("HW B: Inicializando registradores internos.\n"); }
void enviarHardwareB(const char *d) { printf("HW B: Transmitindo: %s\n", d); }

int main() {
    // Instanciação dos drivers preenchendo os ponteiros de função
    DriverComunicacao driverA = {initHardwareA, enviarHardwareA};
    DriverComunicacao driverB = {initHardwareB, enviarHardwareB};

    // Ponteiro genérico da aplicação
    DriverComunicacao *periferico;

    // Configura dinamicamente para o Hardware A
    periferico = &driverA;
    periferico->inicializar();
    periferico->enviar("Dados de teste A");

    // Alterna em tempo de execução para o Hardware B
    periferico = &driverB;
    periferico->inicializar();
    periferico->enviar("Dados de teste B");

    return 0;
}
