#include <stdio.h>

int main(void) {
   int currentPrice;
   int lastMonthsPrice;
   
   scanf("%d", &currentPrice);
   scanf("%d", &lastMonthsPrice);
   
   int priceChange = currentPrice - lastMonthsPrice;
   double estMonMort = (currentPrice * 0.051) / 12;
   printf("This house is $%d. The change is $%d since last month.\n", currentPrice, priceChange);
   printf("The estimated monthly mortgage is $%f.\n", estMonMort);

   return 0;
}
