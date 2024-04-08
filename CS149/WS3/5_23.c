#include <stdio.h>

int main(void) {
   int array[20];
   int size = 0;
   int nextVal = 0;
   int min = 0;
   int max = 0;
   
   
   scanf("%d", &size);
   
   for(int i = 0; i < size; i++){
    scanf("%d", &nextVal);
     array[i] = nextVal;
   } 
   scanf("%d", &min);
   scanf("%d", &max);
   
   
   for(int i = 0; i < size; i++){
    if(array[i] >= min && array[i] <= max){
     printf("%d,", array[i]);  
    }
   }
     printf("\n");
   return 0;
}
