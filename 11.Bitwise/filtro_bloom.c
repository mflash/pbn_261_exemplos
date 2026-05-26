#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// Funções de hash simples para strings
uint32_t hash1(const char *str) {
    uint32_t hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + *str++; // hash * 33 + c
    }
    return hash % 32; // Limita ao tamanho do nosso vetor de 32 bits
}

uint32_t hash2(const char *str) {
    uint32_t hash = 0;
    while (*str) {
        hash = *str++ + (hash << 6) + (hash << 16) - hash;
    }
    return hash % 32;
}

// Insere um elemento ativando os bits correspondentes via OR (|)
void bloom_inserir(uint32_t *filtro, const char *item) {
    uint32_t h1 = hash1(item);
    uint32_t h2 = hash2(item);
    
    *filtro |= (1 << h1);
    *filtro |= (1 << h2);
}

// Verifica a existência testando os bits via AND (&)
bool bloom_verificar(uint32_t filtro, const char *item) {
    uint32_t h1 = hash1(item);
    uint32_t h2 = hash2(item);
    
    // Se QUALQUER um dos bits gerados pelo hash estiver em 0, o item NÃO existe
    if (((filtro & (1 << h1)) == 0) || ((filtro & (1 << h2)) == 0)) {
        return false; // Definitivamente não está presente
    }
    return true; // Provavelmente está presente
}

int main() {
    uint32_t filtro_bloom = 0; // Vetor de 32 bits zerado

    printf("=== Exemplo Avançado: Filtro de Bloom Simplificado ===\n");

    // Inserindo elementos no conjunto
    bloom_inserir(&filtro_bloom, "huguinho");
    bloom_inserir(&filtro_bloom, "zezinho");
    
    printf("Filtro de Bloom (Estado do Vetor de Bits): 0x%08X\n\n", filtro_bloom);

    // Testando elementos
    const char *teste1 = "huguinho";
    const char *teste2 = "luizinho"; // Nunca foi inserido

    printf("Verificando '%s': %s\n", teste1, 
           bloom_verificar(filtro_bloom, teste1) ? "Provavelmente Presente" : "Definitivamente Ausente");
           
    printf("Verificando '%s': %s\n", teste2, 
           bloom_verificar(filtro_bloom, teste2) ? "Provavelmente Presente" : "Definitivamente Ausente");
}

