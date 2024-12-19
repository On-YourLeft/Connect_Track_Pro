#include <stdio.h>
#include <string.h>
#include "contact_manager.h"

const char *CONTACT_FILE = "contacts.dat";

void addContact() 
{
    FILE *file = fopen(CONTACT_FILE, "ab");
    Contact c;

    if (!file) 
    {
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

void viewContacts() {
    FILE *file = fopen(CONTACT_FILE, "rb");
    Contact c;

    if (!file) {
        printf("Error opening file or no contacts found!\n");
        return;
    }

    printf("\nContacts List:\n");
    printf("=====================================\n");

    while (fread(&c, sizeof(Contact), 1, file)) {
        printf("Name: %s\n", c.name);
        printf("Phone: %s\n", c.phone);
        printf("Email: %s\n", c.email);
        printf("Address: %s\n", c.address);
        printf("-------------------------------------\n");
    }

    fclose(file);
}

void deleteContact() 
{
    char nameToDelete[MAX_NAME_LEN] = {0};

    fflush(stdin);

    // Prompt user for name
    printf("Enter name to delete: ");
    if (fgets(nameToDelete, MAX_NAME_LEN, stdin)) 
    {
        nameToDelete[strcspn(nameToDelete, "\n")] = '\0'; // Remove newline
        printf("Received input for deletion: '%s'\n", nameToDelete); // Debugging output
    }
    else 
    {
        printf("Error reading input.\n");
        return;
    }

    FILE *file = fopen(CONTACT_FILE, "rb");
    if (!file) {
        perror("Error opening contact file");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    Contact c;
    int found = 0;

    while (fread(&c, sizeof(Contact), 1, file)) {
        printf("Checking contact: '%s'\n", c.name); // Debugging output
        if (strcmp(c.name, nameToDelete) == 0) {
            found = 1;
            printf("Deleted Contact: %s\n", c.name);
        } else {
            if (fwrite(&c, sizeof(Contact), 1, tempFile) != 1) {
                perror("Error writing to temporary file");
                fclose(file);
                fclose(tempFile);
                return;
            }
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        if (remove(CONTACT_FILE) != 0 || rename("temp.dat", CONTACT_FILE) != 0) {
            perror("Error updating contact file");
        } else {
            printf("Contact deleted successfully.\n");
        }
    } else {
        printf("No contact found with the name '%s'.\n", nameToDelete);
        remove("temp.dat");
    }
}

void updateContact() {
    char nameToUpdate[MAX_NAME_LEN] = {0};

    fflush(stdin);

    // Prompt user for name
    printf("Enter name to update: ");
    if (fgets(nameToUpdate, MAX_NAME_LEN, stdin)) {
        nameToUpdate[strcspn(nameToUpdate, "\n")] = '\0'; // Remove newline
        printf("Received input for update: '%s'\n", nameToUpdate); // Debugging output
    } else {
        printf("Error reading input.\n");
        return;
    }

    FILE *file = fopen(CONTACT_FILE, "rb+");
    if (!file) {
        perror("Error opening contact file");
        return;
    }

    Contact c;
    int found = 0;

    while (fread(&c, sizeof(Contact), 1, file)) {
        printf("Checking contact: '%s'\n", c.name); // Debugging output
        if (strcmp(c.name, nameToUpdate) == 0) {
            found = 1;
            printf("Updating Contact: %s\n", c.name);

            printf("Enter New Phone: ");
            scanf(" %[^\n]", c.phone);  // Use space before %[^\n] to clear buffer
            printf("Enter New Email: ");
            scanf(" %[^\n]", c.email);
            printf("Enter New Address: ");
            scanf(" %[^\n]", c.address);

            fseek(file, -sizeof(Contact), SEEK_CUR);
            if (fwrite(&c, sizeof(Contact), 1, file) != 1) {
                perror("Error updating contact");
            } else {
                printf("Contact Updated Successfully!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("No contact found with the name '%s'.\n", nameToUpdate);
    }

    fclose(file);
}
