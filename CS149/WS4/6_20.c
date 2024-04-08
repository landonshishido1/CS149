#include <stdio.h>

double LapsToMiles(double userLaps){
   return userLaps / 4;
}

int main(void) {
   double num = 0;
   scanf("%lf", &num);
   num = LapsToMiles(num);
   printf("%0.2lf\n", num);
   /* Type your code here. Your code must call the function.  */

   return 0;
}
