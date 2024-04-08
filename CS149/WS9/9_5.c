#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    char *firstWord;
    char *secondWord;

    while (1) {
        printf("Enter input string:\n");
       
        fgets(input, 100, stdin); 

        if (strcmp(input, "q\n") == 0) {
            break;
        }


        if (strchr(input, ',') == NULL) {
            printf("Error: No comma in string.\n");
         printf("\n");
         continue;
        }

        firstWord = strtok(input, ", ");
        secondWord = strtok(NULL, ", \n");

        if (firstWord && secondWord) {
            printf("First word: %s\n", firstWord);
            printf("Second word: %s\n", secondWord);
        } else {
            printf("Error parsing the string.\n");
        }
        printf("\n");
    }

    return 0;
}
