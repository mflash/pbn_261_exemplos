#include <stdio.h>
#include <stdlib.h>

#define SIZE 2000000 // two millions
int main()
{
        //double* array = malloc(sizeof *array * SIZE);
        double* array = calloc(SIZE, sizeof *array);
        printf("mem. size: %zu\n", sizeof *array * SIZE);
	int i;
        for(i=0; i<SIZE; i++)
            array[i] = i;
        free(array);
}
