#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
     FILE *ptr = fopen("contact.csv","w");
    if (ptr == NULL)
    {
        printf("ERROR: while opening file\n");
        return;
    }
    fprintf(ptr, "#%d#\n",addressBook->contactCount);
    
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(ptr, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
    fclose(ptr);
    printf("\e[32mContacts saved successfully...\e[0m\n");
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *ptr = fopen("contact.csv","r");
    if (ptr == NULL)
    {
        printf("ERROR: while opening file\n");
        return;
    }
    fscanf(ptr, "#%d#\n", &addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(ptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    
    fclose(ptr);
}
