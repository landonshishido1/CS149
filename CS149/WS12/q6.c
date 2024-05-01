//
//hTe program does not run.
// When valgrind is used, it will report an error due to the program trying
// to access freed memory.
 #include <stdlib.h>
 #include <stdio.h>

int main()
{
    int *data = malloc(100 * sizeof(int));
    free(data);
    printf("%d\n", data[0]);

    return 0;
}
