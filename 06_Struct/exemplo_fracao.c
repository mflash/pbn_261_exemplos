#include <stdio.h>

typedef struct {
  float numerador;
  float denominador;
} Fracao;

float calcula(Fracao frac);
float calculaRef(Fracao* frac);
void adiciona(Fracao* f1, Fracao* f2);
void multiplica(Fracao* f1, Fracao* f2);

float calcula(Fracao frac) {
  return frac.numerador / frac.denominador;
}

float calculaRef(Fracao* frac) {
    return frac->numerador / frac->denominador;
}

void adiciona(Fracao* f1, Fracao* f2)
{
  float den = f1->denominador * f2->denominador;
  f1->numerador = den/f1->denominador * f1->numerador +
      den/f2->denominador * f2->numerador;
  f1->denominador = den;
}

void multiplica(Fracao* f1, Fracao* f2)
{
  f1->numerador = f1->numerador * f2->numerador;
  f1->denominador = f1->denominador * f2->denominador;
}

int main() {
  Fracao f1;
  f1.numerador = 1;
  f1.denominador = 2;
  Fracao f2 = { 3 , 4 };
//  printf("Valor: %f\n", calcula(f1));
//  printf("Valor: %f\n", calculaRef(&f1));
  printf("Fracao 1: %.2f / %.2f\n", f1.numerador, f1.denominador);
  printf("Fracao 2: %.2f / %.2f\n", f2.numerador, f2.denominador);
  Fracao f3 = f1;
  adiciona(&f1, &f2);
  printf("Adição: %.2f / %.2f\n", f1.numerador, f1.denominador);
  multiplica(&f3, &f2);
  printf("Multiplicação: %.2f / %.2f\n", f3.numerador, f3.denominador);
}