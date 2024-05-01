//The program creates an array of integers using malloc and
// data[100] is out of bounds and returns a memory error to the user.
//Valgrind will detect the out of bounds access and report an error.
//
//No, the program is not correct.

#include <stdlib.h>

int main()
{
    int *data = malloc(100 * sizeof(int));
    data[100] = 0;

    return 0;
}

