#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int largura;
    int altura;
    int max_valor;
    unsigned char *dados;
} ImagemPGM;

ImagemPGM ler_p5(const char *nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "rb");
    if (!arq) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    char formato[3];
    fscanf(arq, "%2s", formato);
    if (formato[0] != 'P' || formato[1] != '5') {
        fprintf(stderr, "Formato invalido (deve ser P5 binario)\n");
        fclose(arq);
        exit(EXIT_FAILURE);
    }

    ImagemPGM img;
    // Ignorar comentários no cabeçalho de texto
    char ch = fgetc(arq);
    while (ch == '#') {
        while (fgetc(arq) != '\n');
        ch = fgetc(arq);
    }
    ungetc(ch, arq);

    // Ler dimensões do cabeçalho de texto
    fscanf(arq, "%d %d %d", &img.largura, &img.altura, &img.max_valor);
    fgetc(arq); // Consumir o caractere de nova linha isolado

    // Alocação e leitura direta do bloco binário de pixels
    int total_pixels = img.largura * img.altura;
    img.dados = (unsigned char *)malloc(total_pixels);
    
    size_t lidos = fread(img.dados, sizeof(unsigned char), total_pixels, arq);
    if (lidos != total_pixels) {
        fprintf(stderr, "Erro ao ler matriz de pixels.\n");
    }

    fclose(arq);
    return img;
}

void salvar_p5(const char *nome_arquivo, ImagemPGM img) {
    FILE *arq = fopen(nome_arquivo, "wb");
    if (!arq) {
        perror("Erro ao salvar arquivo");
        exit(EXIT_FAILURE);
    }

    // Escrita do cabeçalho formatado
    fprintf(arq, "P5\n%d %d\n%d\n", img.largura, img.altura, img.max_valor);

    // Escrita em lote do buffer de pixels binários
    int total_pixels = img.largura * img.altura;
    fwrite(img.dados, sizeof(unsigned char), total_pixels, arq);

    fclose(arq);
}

int main(int argc, char **argv) {
    // Carrega a imagem binária para a memória
    ImagemPGM img = ler_p5(argv[1]);

    // Operação de baixo nível: manipulação direta de ponteiros de memória
    int total_pixels = img.largura * img.altura;
    unsigned char *ptr = img.dados;

    for (int i = 0; i < total_pixels; i++) {
        // Reduz o brilho dividindo o valor do byte por 2 (shift pointer à direita)
        *ptr = *ptr / 2;
        ptr++;
    }

    // Despeja o buffer modificado de volta no disco
    salvar_p5("saida_escura.pgm", img);

    free(img.dados);
    return 0;
}
