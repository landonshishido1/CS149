#include <stdio.h>
#include <limits.h>

int main(void) {
int array[20];
int numInt = 0;
int nextInt = 0;
int small = INT_MAX;
int small2 = INT_MAX;

scanf("%d", &numInt);
for(int i = 0; i < numInt; i++){
   scanf("%d", &nextInt);
   array[i] = nextInt;
}

for(int i = 0; i < numInt; i++){
   if(array[i] < small){
     small2 = small;
     small = array[i];
   }else if(array[i] < small2){
   small2 = array[i];
   }
}
printf("%d and %d\n", small, small2);

   return 0;
}
