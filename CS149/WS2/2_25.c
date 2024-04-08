#include <stdio.h>

int main(void) {

  int userNum;
  int divNum;
  scanf("%d", &userNum);
  scanf("%d", &divNum);
  userNum = userNum / divNum;
  printf("%d ", userNum);
  userNum = userNum / divNum;
  printf("%d ", userNum);
  userNum = userNum / divNum;
  printf("%d\n", userNum);
   return 0;
}
