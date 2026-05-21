#ifndef SHAPES_H
#define SHAPES_H

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

// Biblioteca de formas simples
void setImage(Img* img);
Img* newImage(int width, int height);
void freeImage(Img* img);
void saveImage(Img* img, char* filename);

void drawCircle(int x, int y, int radius, Pixel color);
void drawRect(int left, int top, int width, int height, Pixel color);
void drawLine(int x1, int y1, int x2, int y2, Pixel color, int thickness);
void drawPoint(int x, int y, Pixel color);

#endif
