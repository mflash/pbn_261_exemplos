#include <stdio.h>

int eh_palindromo(char* s);

int eh_palindromo(char* s) {
  char* ptr1 = s;
  char* ptr2 = s;
  while (*ptr2 != '\0') {
    ptr2++;
  }
  ptr2--;  // volta um (pára na última letra)
  // Enquanto não chegar no meio da string
  // (ou não passar um pelo outro)...
  while (ptr1 < ptr2) {
    if (*ptr1 != *ptr2) return 0;  // não é!
    ptr1++;
    ptr2--;
  }
  return 1;  // é palíndromo!
}

int main() {
  char str[] = "SOPAPOS";
  if (eh_palindromo(str))
    printf("%s é um palíndromo\n", str);
  else
    printf("%s não é palíndromo...\n", str);
}