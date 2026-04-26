#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para usar strings
#include <time.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

// Um pixel Pixel (24 bits)
typedef struct
{
    unsigned char r, g, b;
} Pixel;

// Uma imagem Pixel
typedef struct
{
    int width, height;
    int channels;
    Pixel *pixels;
} Img;

// Protótipos
void load(char *name, Img *pic);

// As 2 imagens
Img in, out;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("forensics [origem]\n");
        exit(1);
    }

    // Carrega a imagem original
    load(argv[1], &in);

    // Exibe as dimensões na tela, para conferência
    printf("Origem   : %s %d x %d\n", argv[1], in.width, in.height);

    printf("Processando...\n");

    // Cria imagem de saída e "zera" ela
    int tam = in.width * in.height;
    out = in;
    out.pixels = malloc(tam * sizeof(Pixel));
    memset(out.pixels, 0, tam * sizeof(Pixel));
   
    // Converte para interpretar como matrizes
    Pixel (*pin)[in.width] = (Pixel(*)[in.height]) in.pixels;
    Pixel (*pout)[in.width] = (Pixel(*)[in.height]) out.pixels;

    //
    // Neste ponto, voce deve implementar o algoritmo!
    // (ou chamar funcoes para fazer isso)
    //
    // Aplica o algoritmo em pin e gera a saida em pout
    // ...
    //
    // Exemplo: inverte as cores
    for(int i=0; i<in.height; i++) {
        for(int j=0; j<in.width; j++) {
            pout[i][j].r = 255 - pin[i][j].r;
            pout[i][j].g = 255 - pin[i][j].g;
            pout[i][j].b = 255 - pin[i][j].b;
        }
    }

    // NÃO ALTERAR A PARTIR DAQUI!

    // Grava a imagem como JPEG para registro
    stbi_write_jpg("saida.jpg", out.width, out.height, 3, pout, 90);

    free(in.pixels);
    free(out.pixels);
}

void load(char *name, Img *pic)
{
    pic->pixels = (Pixel *)stbi_load(name, &pic->width, &pic->height, &pic->channels, 0);
    if (!pic->pixels)
    {
        printf("STB loading error\n");
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, pic->channels);
    // Exibe os 16 primeiros pixels (teste)
    for (int i = 0; i < 16; i++)
    {
        printf("[%02X %02X %02X] ", pic->pixels[i].r, pic->pixels[i].g, pic->pixels[i].b);
    }
    printf("\n");
}

