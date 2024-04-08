#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 9;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   int curr = 0;
   int counter = 0;

   //read values in until negative number
   while(curr >= 0){
      //add value to array
      userValues[counter] = curr;
      //increase array counter
      counter++;
      //scan next value
       scanf("%d", &curr);
   }
   if(counter > 10){
      printf("Too many numbers\n");
      return 0;
   }
   int middle = (counter / 2);
   printf("Middle item: %d\n",userValues[middle]);
   return 0;
}
