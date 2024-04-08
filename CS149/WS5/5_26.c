#include <stdio.h>
#include <string.h>
int main() {
    char str[50];
    int count = 0;
    fgets(str, 50, stdin);
    for(int i = 0; str[i] != '\n'&& str[i] != '\0'; i++) {
        if(str[i] != ' ' && str[i] != '.' && str[i] != '!' && str[i] != ',') {
            count = count + 1;
        }
    }
    printf("%d\n",count);
    return 0;
}