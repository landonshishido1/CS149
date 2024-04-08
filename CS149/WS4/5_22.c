#include <stdio.h>
#include <string.h>

int main(void) {
    int numWords;
    scanf("%d", &numWords); // Read the number of words

    char words[numWords][101]; // Create a 2D array to store the words, assuming a max length of 100 characters per word
    for (int i = 0; i < numWords; ++i) {
        scanf("%100s", words[i]); // Read each word and store it in the array
    }

    char targetChar;
    scanf(" %c", &targetChar); // Read the target character, the space before %c is to consume any leftover whitespace characters

    for (int i = 0; i < numWords; ++i) {
        if (strchr(words[i], targetChar) != NULL) {
            // If the target character is found in the word, print the word followed by a comma
            printf("%s,", words[i]);
        }
    }
    printf("\n"); // Print a newline after all words have been processed

    return 0;
}
