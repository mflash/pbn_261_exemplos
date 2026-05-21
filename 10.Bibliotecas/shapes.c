#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

#include "shapes.h"

// Imagem atual
Img* img;

void setImage(Img* img);
Img* newImage(int width, int height);
void saveImage(Img* img, char* filename);
void freeImage(Img* img);

void drawCircle(int x, int y, int radius, Pixel color);
void drawRect(int left, int top, int width, int height, Pixel color);
void drawLine(int x0, int y0, int x1, int y1, Pixel color, int thickness);
void drawPoint(int x, int y, Pixel color);

void setImage(Img* im) {
  img = im;
}

Img* newImage(int width, int height) {
  img = (Img*)malloc(sizeof(Img));
  img->width = width;
  img->height = height;
  img->channels = 3; // RGB
  img->pixels = (Pixel*)malloc(width * height * sizeof(Pixel));
  return img;
}

void saveImage(Img* img, char* filename) {
    stbi_write_jpg(filename, img->width, img->height, 3, img->pixels, 90);
}

void freeImage(Img* im) {
  free(im->pixels);
  free(im);
}

void drawRect(int left, int top, int width, int height, Pixel color) {
  drawLine(left, top, left + width, top, color, 1); // Top
  drawLine(left, top, left, top + height, color, 1); // Left
  drawLine(left + width, top, left + width, top + height, color, 1); // Right
  drawLine(left, top + height, left + width, top + height, color, 1); // Bottom
}

void drawCircle(int x, int y, int radius, Pixel color) {
  float ang;
  float incr = 0.2;
  for(ang=0; ang <= 2*M_PI; ang+=incr)
  {
    int px1 = (int) (x + radius * cos(ang));
    int py1 = (int) (y + radius * sin(ang));
    int px2 = (int) (x + radius * cos(ang+incr));
    int py2 = (int) (y + radius * sin(ang+incr));
    drawLine(px1, py1, px2, py2, color, 1);
  }
}

// Algoritmo de Bresenham para desenhar uma linha em uma matriz de pixels
void drawLine(int x0, int y0, int x1, int y1, Pixel color, int thickness) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e2;

    int half = thickness / 2;
    while (1) {
        // Draw a square of size thickness x thickness centered at (x0, y0)
        for (int i = -half; i <= half; i++) {
            for (int j = -half; j <= half; j++) {
                int xi = x0 + i, yj = y0 + j;
                if (xi >= 0 && xi < img->width && yj >= 0 && yj < img->height) {
                    img->pixels[yj*img->width + xi] = color;
                }
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

void drawPoint(int x, int y, Pixel color)
{
    if(x >= img->width || x < 0 || y >= img->height || y < 0)
        return;
    // Se quiser, tente fazer pontos mais "largos"
    img->pixels[y*img->width + x] = color;
}

