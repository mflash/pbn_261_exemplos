#include <stdio.h>

char* minha_strcat(char* s1, char* s2);

char* minha_strcat(char* s1, char* s2) {
  char* ptr1 = s1;
  char* ptr2 = s2;
  // Anda até o final de s1
  while (*ptr1 != '\0') ptr1++;
  // Agora copia todos os caracteres de ptr2 para ptr1
  while (*ptr2 != '\0') {
    *ptr1 = *ptr2;  // copia
    ptr1++;
    ptr2++;
  }
  return s1;  // por padrão, retorna ponteiro para s1
}

int main() {
  char str1[30] = "Minha string ";
  char str2[] = "maior";

  printf("Antes: %s\n", str1);
  minha_strcat(str1, str2);
  printf("Após: %s\n", str1);
}