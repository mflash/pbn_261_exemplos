#include <stdio.h>

void remove_espacos(char* str) {
  int i = 0, j = 0;
  int dentro = 0;

  while (str[i] != '\0') {
    if (str[i] != ' ') {  // se não é espaço, copia
      str[j] = str[i];
      j++;
      // ... e não está mais "dentro"
      dentro = 0;
    } else if (!dentro) {
      // se for o primeiro espaço, armazena ele em j
      // e indica que está "dentro"
      str[j] = ' ';
      j++;
      dentro = 1;
    }
    // Sempre avança o i
    // (j só avança quando "entrar" ou quando estiver "fora")
    i++;
  }
  str[j] = '\0';
}

int main() {
  char str[] = "  Olha quantos   espaços tem  aqui  ";
  printf("Original: [%s]\n", str);
  remove_espacos(str);
  printf("Modified: [%s]\n", str);
  return 0;
}