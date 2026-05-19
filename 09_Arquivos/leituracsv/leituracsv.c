#include <stdio.h>
#include <string.h>

int main()
{
    FILE* arq = fopen("turmas.csv", "r");

    if (!arq) {
        printf("Impossivel abrir o arquivo!n");
        return 0;
    }

    char buf[1024];
    int linhas = 0;
    int campos = 0;

    while (fgets(buf, 1024, arq)) {
        campos = 0;
        linhas++;

        if (linhas == 1) // pula a primeira linha
           continue;

        // strtok retorna um ponteiro para o primeiro campo
        // ate o separador indicado (";")
        char *campo = strtok(buf, ";");

        // Enquanto nao retornar NULL, e' porque existem mais campos
        while (campo) {
            printf("%02d: %s\n", campos,campo);
            // Pega o proximo campo, passando NULL como primeiro parametro
            campo = strtok(NULL, ";");
            campos++;
        }
        printf("\n");
    }

    fclose(arq);

    return 0;
}
