#include <stdio.h>

#include "shapes.h"

int main(int argc, char *argv[])
{
    Img* imagem = newImage(1024, 768);
    setImage(imagem);

    drawLine(0,0, 1023, 767, (Pixel){255,0,0}, 1);
    drawRect(100, 100, 200, 150, (Pixel){0,255,0});
    drawCircle(512, 384, 100, (Pixel){255,255,0});

    saveImage(imagem, "saida.jpg");
    freeImage(imagem);
}

