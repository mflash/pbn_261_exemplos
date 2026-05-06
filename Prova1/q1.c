#include <stdio.h>

char* minha_strpbrk(char s1[], char s2[]);
char* minha_strpbrk2(char s1[], char s2[]);

char* minha_strpbrk(char s1[], char s2[])
{
    for(int pos2=0; s2[pos2] != '\0'; pos2++) {
        for(int pos1=0; s1[pos1] != '\0'; pos1++) {
            if(s1[pos1] == s2[pos2]) {
                return &s1[pos1];
            }
        }
    }
    return NULL;
}

char* minha_strpbrk2(char s1[], char s2[])
{
    char* aux2 = s2;
    while(*aux2 != '\0') {
        char *aux = s1;
        while(*aux != '\0') {
            if(*aux == *aux2) {
                return aux;
            }
            aux++;
        }
        aux2++;
    }
    return NULL;
}

int main()
{
    char *str1 = "arvore";
    char *str2 = "cet";

    printf("End. de str1: %p %s\n", str1, str1);
    printf("End. de str2: %p %s\n", str2, str2);

    char *res = minha_strpbrk2(str1, str2);
    if(res != NULL)
        printf("Encontrado no end. %p : %c\n", res, *res);
    else
        printf("Não encontrado!\n");
}