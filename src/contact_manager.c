#include <stdio.h>
#include <string.h>
#include "contact_manager.h"

const char *CONTACT_FILE = "contacts.dat";

void addContact() {
    FILE *file = fopen(CONTACT_FILE, "ab");
    Contact c;

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter Phone: ");
    scanf("%s", c.phone);
    printf("Enter Email: ");
    scanf("%s", c.email);
    printf("Enter Address: ");
    scanf(" %[^\n]", c.address);

    fwrite(&c, sizeof(Contact), 1, file);
    printf("Contact Added Successfully!\n");

    fclose(file);
}

// Implement other contact functions (viewContacts, searchContacts, deleteContact, etc.)
