#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ContactNode_struct {
   char contactName[50];           
   char contactPhoneNumber[15];    
   struct ContactNode_struct* nextNodePtr;  
} ContactNode;

void InitializeContactNode(ContactNode* thisNode, char* initialName, char* initialPhoneNumber) {
   strcpy(thisNode->contactName, initialName);
   strcpy(thisNode->contactPhoneNumber, initialPhoneNumber);
   thisNode->nextNodePtr = NULL;                             
}

char* GetName(ContactNode* thisNode) {
   return thisNode->contactName;
}

char* GetPhoneNumber(ContactNode* thisNode) {
   return thisNode->contactPhoneNumber;
}

void InsertAfter(ContactNode* thisNode, ContactNode* newContactNode) {
   ContactNode* temp = thisNode->nextNodePtr;
   thisNode->nextNodePtr = newContactNode;
   newContactNode->nextNodePtr = temp;
}

ContactNode* GetNext(ContactNode* thisNode) {
   return thisNode->nextNodePtr;
}

// Updated function to include person numbering
void PrintContactNode(ContactNode* thisNode, int personNumber) {
   printf("Person %d: %s, %s\n", personNumber, thisNode->contactName, thisNode->contactPhoneNumber);
}

int main(void) {
   char inputName[50];
   char inputPhone[15];
   ContactNode* head = NULL;
   ContactNode* current = NULL;
   ContactNode* temp = NULL;
   int personCount = 1;

   for (int i = 0; i < 3; i++) {
      fgets(inputName, 50, stdin);
      inputName[strlen(inputName) - 1] = '\0';  // Remove newline character

      fgets(inputPhone, 15, stdin);
      inputPhone[strlen(inputPhone) - 1] = '\0';  // Remove newline character

      temp = (ContactNode*)malloc(sizeof(ContactNode));
      InitializeContactNode(temp, inputName, inputPhone);

      if (head == NULL) {
         head = temp;
         current = temp;
      } else {
         InsertAfter(current, temp);
         current = temp;
      }
   }

   // Printing each contact with correct numbering
   current = head;
   while (current != NULL) {
      PrintContactNode(current, personCount);
      current = GetNext(current);
      personCount++;
   }

   // Printing "CONTACT LIST" section
   printf("\nCONTACT LIST\n");
   current = head;
   while (current != NULL) {
      printf("Name: %s\n", current->contactName);
      printf("Phone number: %s\n\n", current->contactPhoneNumber);
      current = GetNext(current);
   }

   return 0;
}
