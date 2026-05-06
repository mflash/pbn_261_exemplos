#include <stdio.h>

int main()
{
    char texto[2][5] = {
        {'a', 'b', 'c', 'd', 'e'},
        {'A', 'B', 'C', 'D', 'E'}
    };

    char *ptr1, *ptr2;

    ptr1 = (char*) texto;
    ptr1 = ptr1 + 9;
    ptr2 = (char*) texto;

    for(int i=0; i<5; i++) {
        *ptr2 = (*ptr1) + 1; // letra seguinte que está em ptr1
        ptr2++;  // avança
        ptr1--;  // volta
    }

    ptr2 = (char* )texto;

    for(int i=0; i<10; i++) {
        printf("%c ", *ptr2);
        ptr2++;
    }
    printf("\n");
}