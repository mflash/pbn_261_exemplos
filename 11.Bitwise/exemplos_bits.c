#include <stdio.h>

typedef struct {
  int red : 11;
  int green : 11;
  int blue : 11;
} RGBPixel;

void exibeInt(unsigned int v);

int main() {
  printf("sizeof(int)    = %d\n", sizeof(int));
  printf("sizeof(char)   = %d\n", sizeof(char));
  printf("sizeof(float)  = %d\n", sizeof(float));
  printf("sizeof(double) = %d\n", sizeof(double));

  // Deveria ser 5 (são apenas 33 bits), mas o compilador usa 8!
  // (provavelmente para manter alinhamento em múltiplos de 8, ou
  // algo parecido)
  printf("sizeof(RGBPixel) = %d\n", sizeof(RGBPixel));

  unsigned int valor = 235;
  exibeInt(valor);
}

void exibeInt(unsigned int v) {
  // unsigned int masc = 0b10000000000000000000000000000000;
  unsigned int masc = (1 << 31);
  for (int i = 0; i < 32; i++) {
    if ((v & masc) != 0) {
      printf("1");
    } else {
      printf("0");
    }
    masc = masc >> 1;
  }
  printf("\n");
}
