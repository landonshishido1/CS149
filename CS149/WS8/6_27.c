#include <stdio.h>
#include <string.h>

int CalcNumCharacters(char* userString, char userChar){
   int count = 0;
   for(int i = 0; i < 50; i++){
       if (userString[i] == '\0') {
        return count;
       }
       if(userString[i] == userChar){
          count++;
       }
   }
   return 0;
}

int main(void) {
char theChar;
char theString[50];
int result;
   scanf("%c", &theChar);
   scanf("%s", theString);
   
   result = CalcNumCharacters(theString, theChar);
   if(result == 1){
       printf("%d %c\n", result, theChar);
   }
   else{  
   printf("%d %c's\n", result, theChar);
}
   return 0;
}
