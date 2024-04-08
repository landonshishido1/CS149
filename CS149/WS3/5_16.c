#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];         // Array to hold the user's input integers
   
    int size = sizeof(userVals);
   scanf("%d", &size);
   int curr = 0;
   
   for (int i = 0; i < size; i++){
        scanf("%d", &curr);
      userVals[i]= curr;
}
for (int i = size - 1; i >= 0 ; i--){
   
   printf("%d,", userVals[i]);
}
   printf("\n");
   return 0;
}
