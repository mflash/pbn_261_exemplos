#include <stdio.h>
#include <math.h>

typedef struct {
    int x,y;
} Ponto;


float calculaDistancia(Ponto a, Ponto b) {
    float dx = a.x - b.x; 
    dx = dx * dx;
    float dy = a.y - b.y;
    dy = dy * dy;
    return sqrt(dx + dy);

    // return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void localizaMaisProximos(Ponto vet[], int qtd, int* pos1, int* pos2)
{
    float menorDist = calculaDistancia(vet[0], vet[1]);
    *pos1 = 0;
    *pos2 = 1;
    for(int p1=0; p1<qtd; p1++) {
        for(int p2=p1+1; p2<qtd; p2++) {
            float dist = calculaDistancia(vet[p1], vet[p2]);
            if(dist < menorDist) {
                menorDist = dist;
                *pos1 = p1; // atualizo os mais próximos
                *pos2 = p2;
            }
        }
    }
}

int main()
{
    Ponto vet[] = { {0,0}, {5, 5}, {2, 2}, {6, 6}};
    /*
    Ponto a = { 0, 0 };
    Ponto b = { 1, 1 };
    float dist = calculaDistancia(a, b);
    printf("Dist: %f\n", dist);
    */
    int p1, p2;
    localizaMaisProximos(vet, 4, &p1, &p2);
    printf("Os pontos mais próximos são: (%d,%d) e (%d,%d)\n",
        vet[p1].x, vet[p1].y, vet[p2].x, vet[p2].y);
}