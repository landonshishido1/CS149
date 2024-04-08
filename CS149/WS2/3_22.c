#include <stdio.h>

int main(void) {
   int first;
   int second;
   int third;
   
   scanf("%d", &first);
   scanf("%d", &second);
   scanf("%d", &third);

   if((first <= second) && (first <= third)){
   printf("%d\n", first);
   }
   else if ((second <= first) && (second <= third)){
   printf("%d\n", second);
   }
   else{
    printf("%d\n", third);
    }
}
