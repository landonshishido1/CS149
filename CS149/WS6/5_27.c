#include <stdio.h>
#include <string.h>

int main(void) {
    char str[50];

    while(1) {
        fgets(str, 50, stdin);

        str[strcspn(str, "\n")] = 0;

        if (strcmp(str, "done") == 0 || strcmp(str, "Done") == 0 || strcmp(str, "d") == 0) {
            break;
        }

        for(int i = strlen(str) - 1; i >= 0; i--) {
            printf("%c", str[i]);
        }

        printf("\n");
    }

    return 0;
}
