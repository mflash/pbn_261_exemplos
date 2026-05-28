#include <stdio.h>
#include <math.h>

// Ponteiro para uma função matemática padrão f(x)
typedef double (*FuncaoMatematica)(double);

double f1(double x) {
    return (x * x) - 4;    // f(x) = x^2 - 4
}
double f2(double x) {
    return sin(x);    // f(x) = sin(x)
}

// Aproximação numérica da derivada de f(x) no ponto x por diferença finita
double calcularDerivada(FuncaoMatematica f, double x) {
    double h = 1e-5;
    return (f(x + h) - f(x - h)) / (2 * h);
}

int main() {
    double ponto = 2.0;

    printf("Derivada de x^2 - 4 no ponto %.1f: %f\n", ponto, calcularDerivada(f1, ponto));
    printf("Derivada de sin(x) no ponto %.1f: %f\n", ponto, calcularDerivada(f2, ponto));

    return 0;
}

