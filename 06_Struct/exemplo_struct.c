#include <stdio.h>

typedef struct {
    float p1, p2, trab;
    int faltas;
} Aluno;

void exibeAluno(Aluno a);
void exibeAlunoRef(const Aluno* a);
void calculaExibeMedia(const Aluno vet[], int total);

void exibeAluno(Aluno a) {
    printf("Nota da P1: %.1f\n", a.p1);
    printf("Nota da P2: %.1f\n", a.p2);
    printf("Nota do T1: %.1f\n", a.trab);
    printf("Faltas: %d\n", a.faltas);
}

void exibeAlunoRef(const Aluno* a) {
    printf("Nota da P1: %.1f\n", a->p1);
    printf("Nota da P2: %.1f\n", a->p2);
    printf("Nota do T1: %.1f\n", a->trab);
    printf("Faltas: %d\n", a->faltas);
    // a->p1 = 0; // operação inválida pois é const!
}

void calculaExibeMedia(const Aluno vet[], int total)
{
    float mediaTurma = 0;
    for(int i=0; i<total; i++) {
        // Aqui usa o operador ponto, pois o vetor JÁ É ponteiro
        mediaTurma += (vet[i].p1 + vet[i].p2 + vet[i].trab)/3;
    }
    mediaTurma = mediaTurma / total;
    printf("Media da turma: %f\n", mediaTurma);
}

int main()
{
    Aluno a1, a2;
    a1.p1 = 8.5;
    a1.p2 = 7;
    a1.trab = 6.7;
    a1.faltas = 3;
    
    a2 = a1; // copia toda a struct a1 para a2
    a2.p1 = 9.0;

    Aluno a3 = a2;
    a3.p1 = 5.5;
    a3.p2 = 7.8;

    Aluno alunos[3] = { a1, a2, a3 };

    exibeAluno(a1);
    printf("\n");
    exibeAluno(a2);

    printf("\n");
    exibeAlunoRef(&a1);
    printf("\n");
    exibeAlunoRef(&a2);

    printf("===================\n");
    for(int i=0; i<3; i++) {
        exibeAlunoRef(&alunos[i]);
        printf("\n");
    }

    printf("\n");
    calculaExibeMedia(alunos, 3);
}