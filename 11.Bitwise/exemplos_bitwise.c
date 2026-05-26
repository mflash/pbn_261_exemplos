#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// --- 1. Flags de Estado Baseadas em Máscaras de Bits ---
#define FLAG_READ    (1 << 0)
#define FLAG_WRITE   (1 << 1)
#define FLAG_EXECUTE (1 << 2)

/*

Máscaras de Bits:
FLAG_READ    (1 << 0)  ->  0 0 0 0  0 0 0 1
FLAG_WRITE   (1 << 1)  ->  0 0 0 0  0 0 1 0
FLAG_EXECUTE (1 << 2)  ->  0 0 0 0  0 1 0 0

Operação OR (Ativação):
    0000 0000  (permissões iniciais)
OR  0000 0011  (FLAG_READ | FLAG_WRITE)
---------------------------------------
    0000 0011  (Resultado: 0x03)

Operação XOR (Inversão da flag WRITE):
    0000 0011  (Estado atual)
XOR 0000 0010  (FLAG_WRITE)
---------------------------------------
    0000 0001  (Resultado: WRITE desativado)

*/

void demonstrar_flags() {
    printf("=== 1. Flags de Estado Baseadas em Máscaras de Bits ===\n");
    uint8_t permissoes = 0;

    // Define as flags READ e WRITE (Operação OR)
    permissoes |= (FLAG_READ | FLAG_WRITE);
    printf("Após definir READ e WRITE: 0x%02X\n", permissoes);

    // Verifica a flag EXECUTE (Operação AND)
    bool pode_executar = (permissoes & FLAG_EXECUTE) != 0;
    printf("Pode executar? %s\n", pode_executar ? "Sim" : "Não");

    // Alterna a flag WRITE / Inverte o estado (Operação XOR)
    permissoes ^= FLAG_WRITE;
    printf("Após alternar/desativar WRITE: 0x%02X\n", permissoes);
    printf("\n");
}

// --- 2. Cifra XOR (XOR Cipher) ---

/*

Mensagem Original (Caractere 'S'):      0 1 0 1  0 0 1 1  (0x53)
Chave Secreta (Key 0x4A):          XOR  0 1 0 0  1 0 1 0  (0x4A)
                                   -----------------------
Texto Cifrado (Dado Ofuscado):          0 0 0 1  1 0 0 1  (0x19 -> '\x19')

Desfazer Cifra (Texto Cifrado):         0 0 0 1  1 0 0 1  (0x19)
Chave Secreta (Key 0x4A):          XOR  0 1 0 0  1 0 1 0  (0x4A)
                                   -----------------------
Mensagem Decifrada Original:            0 1 0 1  0 0 1 1  (0x53 -> 'S')

*/

void cifra_xor(char *dados, char chave, size_t tam) {
    for (size_t i = 0; i < tam; i++) {
        dados[i] ^= chave; // Chamar duas vezes: reverte os dados ao estado original
    }
}

void demonstrar_xor() {
    printf("=== 2. Criptografia XOR ===\n");
    char mensagem[] = "MensagemSecreta2026";
    char chave = 0x4A;
    size_t tam = sizeof(mensagem) - 1;

    printf("Original:   %s\n", mensagem);
    
    cifra_xor(mensagem, chave, tam);
    printf("Cifrado:    ");
    for(size_t i = 0; i < tam; i++) printf("\\x%02X", (unsigned char)mensagem[i]);
    printf("\n");

    cifra_xor(mensagem, chave, tam); // Decodificação
    printf("Decifrado:  %s\n", mensagem);
    printf("\n");
}

// --- 3. Extração de Canais de Cor ---

/*

Pixel Completo (0xFF34A211):
+-------------------+-------------------+-------------------+-------------------+
|    R (Vermelho)   |     G (Verde)     |     B (Azul)      |     A (Alfa)      |
|     1111 1111     |     0011 0100     |     1010 0010     |     0001 0001     |
+-------------------+-------------------+-------------------+-------------------+
 bits 31-24          bits 23-16          bits 15-8           bits 7-0

Exemplo: Extraindo o Canal Verde (G)
1. Deslocamento: pixel >> 16
   [0000 0000  0000 0000  1111 1111  0011 0100]  <- O canal G agora está no início (primeiros 8 bits)

2. Máscara: AND 0xFF (0000 0000  0000 0000  0000 0000  1111 1111)
   [0000 0000  0000 0000  1111 1111  0011 0100]
&  [0000 0000  0000 0000  0000 0000  1111 1111]
-------------------------------------------------
   [0000 0000  0000 0000  0000 0000  0011 0100]  -> Isolado: 0x34 (52)

*/

void demonstrar_cor(void) {
    printf("=== 3. Extração de Canais de Cor ===\n");
    uint32_t pixel = 0xFF34A211; // Formato RGBA empacotado

    // Deslocamento de bits (Shift) combinado com máscara 0xFF (AND)
    uint8_t r = (pixel >> 24) & 0xFF;
    uint8_t g = (pixel >> 16) & 0xFF;
    uint8_t b = (pixel >> 8)  & 0xFF;
    uint8_t a = pixel         & 0xFF;

    printf("Pixel Empacotado: 0x%08X\n", pixel);
    printf("Vermelho (R):    0x%02X (%d)\n", r, r);
    printf("Verde (G):       0x%02X (%d)\n", g, g);
    printf("Azul (B):        0x%02X (%d)\n", b, b);
    printf("Alfa (A):        0x%02X (%d)\n", a, a);
    printf("\n");
}

// --- 4. Truques Matemáticos de Alta Performance ---

/*

Exemplo: 29 MOD 8  (Obs: 8 é 2^3, então a máscara n-1 é 7)

Número 29:    0 0 0 1  1 1 0 1
Máscara 7:  & 0 0 0 0  0 1 1 1   (Bits permitidos pelo divisor 8)
              ------------------
Resultado:    0 0 0 0  0 1 0 1   (Valor decimal: 5)

*/

void demonstrar_matematica() {
    printf("=== 4. Truques Matemáticos de Alta Performance ===\n");
    
    // Validação de potência de dois
    uint32_t val1 = 16;
    uint32_t val2 = 18;
    bool eh_p1 = (val1 != 0) && ((val1 & (val1 - 1)) == 0);
    bool eh_p2 = (val2 != 0) && ((val2 & (val2 - 1)) == 0);
    printf("O número %d é potência de 2? %s\n", val1, eh_p1 ? "Sim" : "Não");
    printf("O número %d é potência de 2? %s\n", val2, eh_p2 ? "Sim" : "Não");

    // Módulo rápido (Resto da divisão onde o divisor 'n' deve ser potência de dois)
    uint32_t x = 29;
    uint32_t n = 8; // 2^3
    uint32_t resto = x & (n - 1);
    printf("%d MOD %d = %d\n", x, n, resto);
    printf("\n");
}

// --- 5. Bitmap para Rastreamento de Alocação de Memória ---

/*

Memória Virtual Rastreada (32 blocos):
Byte 0 (Blocos 0-7)   : [0][0][0][0] [0][0][0][0]
Byte 1 (Blocos 8-15)  : [0][0][1][0] [0][0][0][0]  <- Bloco 14 ativado (bit 6 do Byte 1)
Byte 2 (Blocos 16-23) : [0][0][0][0] [0][0][0][0]
Byte 3 (Blocos 24-31) : [0][0][0][1] [0][0][0][0]  <- Bloco 27 ativado (bit 3 do Byte 3)

Alocação do Bloco 14:
Índice do Byte: 14 / 8 = 1
Posição do Bit: 14 % 8 = 6
Operação      : bitmap[1] |= (1 << 6) -> modifica apenas o bit correspondente.

*/

#define TAMANHO_BITMAP 4 // 4 bytes * 8 bits = 32 blocos rastreados

void alocar_bloco(uint8_t *bitmap, int num_bloco) {
    bitmap[num_bloco / 8] |= (1 << (num_bloco % 8));
}

bool bloco_esta_alocado(const uint8_t *bitmap, int num_bloco) {
    return (bitmap[num_bloco / 8] & (1 << (num_bloco % 8))) != 0;
}

void demonstrar_bitmap() {
    printf("=== 5. Bitmap de Alocação de Memória ===\n");
    uint8_t bitmap_memoria[TAMANHO_BITMAP] = {0}; // Todos os blocos iniciam livres

    alocar_bloco(bitmap_memoria, 14);
    alocar_bloco(bitmap_memoria, 27);

    printf("Bloco 14 alocado: %s\n", bloco_esta_alocado(bitmap_memoria, 14) ? "Sim" : "Não");
    printf("Bloco 15 alocado: %s\n", bloco_esta_alocado(bitmap_memoria, 15) ? "Sim" : "Não");
    printf("Bloco 27 alocado: %s\n", bloco_esta_alocado(bitmap_memoria, 27) ? "Sim" : "Não");
    printf("\n");
}

// --- 6. Mascaramento de Sub-rede ---

/*

IP Local:    192.168.1.50   ->  11000000  10101000  00000001  00110010
Máscara:     255.255.255.0  ->  11111111  11111111  11111111  00000000 [AND]
                                --------------------------------------------
ID de Rede:  192.168.1.0    ->  11000000  10101000  00000001  00000000

IP Remoto:   192.168.1.200  ->  11000000  10101000  00000001  11001000
Máscara:     255.255.255.0  ->  11111111  11111111  11111111  00000000 [AND]
                                --------------------------------------------
ID de Rede:  192.168.1.0    ->  11000000  10101000  00000001  00000000

Conclusão: Os IDs de rede são idênticos (0xC0A80100). Comunicação direta permitida.

*/

#define ENDERECO_IP(a,b,c,d) (((uint32_t)(a) << 24) | ((uint32_t)(b) << 16) | ((uint32_t)(c) << 8) | (uint32_t)(d))

void demonstrar_subrede() {
    printf("=== 6. Mascaramento de Sub-rede ===\n");
    
    uint32_t ip_local   = ENDERECO_IP(192, 168, 1, 50);   // 0xC0A80132
    uint32_t ip_remoto  = ENDERECO_IP(192, 168, 1, 200);  // 0xC0A801C8
    uint32_t mascara    = ENDERECO_IP(255, 255, 255, 0);  // 0xFFFFFF00

    uint32_t rede_local = ip_local & mascara;
    uint32_t rede_remota = ip_remoto & mascara;

    printf("ID da Rede Local:  0x%08X\n", rede_local);
    printf("ID da Rede Remota: 0x%08X\n", rede_remota);
    
    if (rede_local == rede_remota) {
        printf("Resultado: Os pacotes podem ser entregues localmente.\n");
    } else {
        printf("Resultado: Os pacotes devem ser enviados para o gateway.\n");
    }
    printf("\n");
}

// --- 7. Inversão de Endianness ---

/*

Dado Original: [ Byte 3 ] [ Byte 2 ] [ Byte 1 ] [ Byte 0 ]  (0x12345678)
                 0x12       0x34       0x56       0x78

Byte 3 vai para posição 0 ->  >> 24
Byte 2 vai para posição 1 ->  >> 8
Byte 1 vai para posição 2 ->  << 8
Byte 0 vai para posição 3 ->  << 24

Combinação Final (OR):

               [ Byte 3 ] [ Byte 2 ] [ Byte 1 ] [ Byte 0 ]  (0x78563412)
                 0x78       0x56       0x34       0x12

*/
uint32_t inverter_endian32(uint32_t val) {
    return ((val & 0xFF000000) >> 24) |
           ((val & 0x00FF0000) >> 8)  |
           ((val & 0x0000FF00) << 8)  |
           ((val & 0x000000FF) << 24);
}

void demonstrar_endianness() {
    printf("=== 7. Inversão de Endianness (Byte Swap) ===\n");
    uint32_t original = 0x12345678;
    uint32_t invertido = inverter_endian32(original);
    
    printf("Original:  0x%08X\n", original);
    printf("Invertido: 0x%08X\n", invertido);
    printf("\n");
}

// --- 8. Valor Absoluto Sem Desvios (Branchless Absolute Value) ---

/*

Cenário: Número Negativo (v = -42)
Em binário: v = 11111111 11111111 11111111 11010110

1. Criar Máscara (v >> 31):

   O bit de sinal (1) se propaga por todo o registrador:
   mascara = 11111111 11111111 11111111 11111111 (equivalente a -1)

2. Somar a Máscara (v + mascara):

   -42 + (-1) = -43
   11111111 11111111 11111111 11010101

3. Operação XOR final ((v + mascara) ^ mascara):
   Inverte todos os bits do valor intermediário, completando a conversão do sinal:

     11111111 11111111 11111111 11010101  (-43)
XOR  11111111 11111111 11111111 11111111  (mascara)
-------------------------------------------
     00000000 00000000 00000000 00101010  (Resultado: +42 em decimal)

*/

int32_t valor_absoluto_bitwise(int32_t v) {
    int32_t const mascara = v >> 31; // Preenche com 1s se for negativo, 0s se for positivo
    return (v + mascara) ^ mascara;
}

void demonstrar_absoluto() {
    printf("=== 8. Valor Absoluto Sem Desvios Condicionais ===\n");
    int32_t pos = 42;
    int32_t neg = -42;

    printf("Abs(%d) = %d\n", pos, valor_absoluto_bitwise(pos));
    printf("Abs(%d) = %d\n", neg, valor_absoluto_bitwise(neg));
    printf("\n");
}

// --- Função Principal ---
//
int main() {
    demonstrar_flags();
    //demonstrar_xor();
    //demonstrar_cor();
    //demonstrar_matematica();
    //demonstrar_bitmap();
    //demonstrar_subrede();
    //demonstrar_endianness();
    //demonstrar_absoluto();
    return 0;
}

