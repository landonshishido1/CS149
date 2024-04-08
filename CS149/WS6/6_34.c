#include <stdio.h>
#include <stdbool.h>

// Function to check if all elements are multiples of 10
bool IsArrayMult10(int inputVals[], int numVals) {
   for (int i = 0; i < numVals; i++) {
      if (inputVals[i] % 10 != 0) {
         return false;
      }
   }
   return true;
}

// Function to check if no elements are multiples of 10
bool IsArrayNoMult10(int inputVals[], int numVals) {
    for (int i = 0; i < numVals; i++) {
        if (inputVals[i] % 10 == 0) {
            return false;
        }
    }
    return true;
}

int main(void) {
   int count = 0;
   scanf("%d", &count);

   int array[count];
   for (int i = 0; i < count; i++) {
      scanf("%d", &array[i]);
   }
   
   // Check the properties of the array
   bool mults = IsArrayMult10(array, count);
   bool notMults = IsArrayNoMult10(array, count);

   // Determine and print the result based on the properties
   if (mults) {
      printf("all multiples of 10\n");
   } else if (notMults) {
      printf("no multiples of 10\n");
   } else {
      printf("mixed values\n");
   }

   return 0;
}
