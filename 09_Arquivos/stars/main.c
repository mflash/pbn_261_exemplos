#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

typedef struct
{
    float x,y,z;
} Star;

// A imagem
Img out;

// Protótipos
void draw_line(int width, int height, Pixel img[][width], int x0, int y0, int x1, int y1, Pixel color, int thickness);
void draw_point(int width, int height, Pixel img[][width], int x, int y, Pixel color);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("stars [arquivo]\n");
        exit(1);
    }

    Star* stars = malloc(sizeof(Star) * 88000);

    out.width = 1024;
    out.height = 768;

    // Exibe as dimensões na tela, para conferência
    printf("Imagem   : %d x %d\n", out.width, out.height);

    printf("Processando...\n");


    FILE* arq = fopen(argv[1], "r");
    if(!arq) {
        printf("Erro abrindo o arquivo!\n");
        exit(1);
    }

    char linha[1024];
    fgets(linha, 1024, arq); // pula cabeçalho
    int totalPontos = 0;
    while(fgets(linha, 1024, arq))
    {
        float ra, dec, dist;
        sscanf(linha, "%f %f %f", &ra, &dec, &dist);
        // printf("%f %f %f\n", ra, dec, dist);

        // Converte para coords cartesianas (x,y,z)
        float x = dist * cos(dec) * cos(ra);
        float y = dist * cos(dec) * sin(ra);
        float z = dist * sin(dec);
        stars[totalPontos].x = x;
        stars[totalPontos].y = y;
        stars[totalPontos].z = z;
        totalPontos++;
        printf("%f %f %f\n", x, y, z);
    }

    fclose(arq);

    // Cria imagem de saída e "zera" ela
    int tam = out.width * out.height;
    out.pixels = malloc(tam * sizeof(Pixel));
    memset(out.pixels, 0, tam * sizeof(Pixel));

    // Converte para interpretar como matriz
    Pixel (*pout)[out.width] = (Pixel(*)[out.height]) out.pixels;

    // Exemplo: desenha uma linha vermelha de um canto a outro da imagem
    // Pixel red = {255, 0, 0};
    // draw_line(out.width, out.height, pout, 0, 0, out.width-1, out.height-1, red, 5);

    // NÃO ALTERAR A PARTIR DAQUI!

    Pixel white = { 255, 255, 255};
    for(int i=0; i<10000; i++) {
        int x = rand()%out.width;
        int y = rand()%out.height;
        draw_point(out.width, out.height, pout, x, y, white);
    }
    // Grava a imagem como JPEG para registro
    stbi_write_jpg("saida.jpg", out.width, out.height, 3, pout, 90);

    free(out.pixels);
    free(stars);
}


// Algoritmo de Bresenham para desenhar uma linha em uma matriz de pixels
void draw_line(int width, int height, Pixel img[][width], int x0, int y0, int x1, int y1, Pixel color, int thickness) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    int half = thickness / 2;
    while (1) {
        // Draw a square of size thickness x thickness centered at (x0, y0)
        for (int i = -half; i <= half; i++) {
            for (int j = -half; j <= half; j++) {
                int xi = x0 + i, yj = y0 + j;
                if (xi >= 0 && xi < width && yj >= 0 && yj < height)
                    img[yj][xi] = color;
            }
        }
        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy)  {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_point(int width, int height, Pixel img[][width], int x, int y, Pixel color)
{
    if(x >= width || x < 0 || y >= height || y < 0)
        return;
    // Se quiser, tente fazer pontos mais "largos"
    img[y][x] = color;
}

