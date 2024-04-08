#include <stdio.h>
#include <string.h>

int main(void) {
int num;
char sol[50] = "";
   scanf("%d", &num);
   while(num > 0){
   if((num % 2) == 0){
   strcat(sol, "0");
     }
     else{
 strcat(sol, "1");
}
   num = num / 2;
}
printf("%s\n", sol);
return 0;
}