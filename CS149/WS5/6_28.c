#include <stdio.h>
#include <string.h>
#include <ctype.h>

void RemoveNonAlpha(char str[], char corStr[]){
   int count = 0;
      for(int i = 0; str[i] != '\n'&& str[i] != '\0'; i++) {
      if (isalpha((unsigned char)str[i])) { // Cast to unsigned char for isalpha
            corStr[count] = str[i];
            count++;
        }
    }
    corStr[count] = '\0';
}
int main(void) {
   char str[50];
   char corStr[50] = {0};
    
   fgets(str, 50, stdin);
   
   RemoveNonAlpha(str,corStr);
   printf("%s\n", corStr);
   return 0;
}
