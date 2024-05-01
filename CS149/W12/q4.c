//The program allocates memory using malloc but forgets to free it before exiting.
// To find memory leaks using gdb, run the program in gdb and run the "leak check" command
//Running Valgrind using the command --leak-check=yes wVCould report that memory is allocated and never freed,
#include <stdlib.h>

int main()
{
    int *ptr = malloc(sizeof(int));

    return 0;
}
