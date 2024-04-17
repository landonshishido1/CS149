#include "ItemToPurchase.h"
#include <stdio.h>
#include <string.h> // Include for strcspn function

int main() {
    ItemToPurchase item1, item2;
    char c;
 
    // Item 1
    printf("Item 1\nEnter the item name:\n");
    fgets(item1.itemName, 50, stdin);
    item1.itemName[strcspn(item1.itemName, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the item price:\n");
    scanf("%d", &item1.itemPrice);

    printf("Enter the item quantity:\n");
    scanf("%d", &item1.itemQuantity);

    // Clear input buffer
    do {
        c = getchar();
    } while(c != '\n' && c != EOF);
        printf("\n");
    // Item 2
    printf("Item 2\nEnter the item name:\n");
    fgets(item2.itemName, 50, stdin);
    item2.itemName[strcspn(item2.itemName, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the item price:\n");
    scanf("%d", &item2.itemPrice);

    printf("Enter the item quantity:\n");
    scanf("%d", &item2.itemQuantity);
    // Output
    printf("\nTOTAL COST\n");
    PrintItemCost(item1);
    PrintItemCost(item2);

    int totalCost = (item1.itemQuantity * item1.itemPrice) + (item2.itemQuantity * item2.itemPrice);
    printf("\nTotal: $%d\n", totalCost);

    return 0;
}
