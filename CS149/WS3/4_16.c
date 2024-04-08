#include <stdio.h>

int main(void) {
double average = 0;
int max = 0;
int intCounter = 0;
int CurrentNum = 0;

scanf("%d", &CurrentNum);

//while there is not a negative number
while(CurrentNum >=0){
   //increment int Counter, add value to average, compare to current max
   intCounter++;
   average += CurrentNum;
   if(CurrentNum > max){
      max = CurrentNum;
}
scanf("%d", &CurrentNum);
}
//AFTER LOOP, divided average = average / intCounter;
average = average / intCounter;
printf("%d ", max);
printf("%0.2lf\n", average);

   return 0;
}
