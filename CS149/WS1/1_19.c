#include <stdio.h>

int main(void) {
   int userNum;
  int secondNum;
  printf("Enter integer:\n");
  scanf("%d\n", &userNum);
  printf("You entered: %d\n", userNum);
  int numSq = userNum * userNum;
  printf("%d squared is %d\n", userNum, numSq);
  int numCub = userNum * userNum * userNum;
  printf("And %d cubed is %d!!\n", userNum, numCub);
  printf("Enter another integer:\n");
  scanf("%d", &secondNum);
  printf("%d + %d is ", userNum, secondNum);
  int total = userNum + secondNum;
  printf("%d\n", total);
  printf("%d * %d is ", userNum, secondNum);
  int mult = userNum * secondNum;
  printf("%d\n", mult);
   return 0;
}