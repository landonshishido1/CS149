#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   int counter = 0;
   int input = 0;
   
   scanf("%d", &counter);
   
   //read in all values and keep count
   for(int i = 0; i < counter; i++){
       scanf("%d", &input);
     userValues[i] = input;
   }
   
   int last = 0;
    scanf("%d", &last);
    
   for(int i = 0; i < counter;i++){
      if(userValues[i] < last){
         printf("%d,", userValues[i]);
   }
  
}
 printf("\n");
   return 0;

}
