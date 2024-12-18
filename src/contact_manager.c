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

void searchContacts(const char *query) {
    FILE *file = fopen(CONTACT_FILE, "rb");
    Contact c;
    int found = 0;

    if (!file) {
        printf("Error opening file or no contacts found!\n");
        return;
    }

    printf("\nSearch Results for '%s':\n", query);
    printf("=====================================\n");

    while (fread(&c, sizeof(Contact), 1, file)) {
        if (strstr(c.name, query) || strstr(c.phone, query) || strstr(c.email, query) || strstr(c.address, query)) {
            printf("Name: %s\n", c.name);
            printf("Phone: %s\n", c.phone);
            printf("Email: %s\n", c.email);
            printf("Address: %s\n", c.address);
            printf("-------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No contacts found matching the query '%s'.\n", query);
    }

    fclose(file);
}

void deleteContact(const char *nameToDelete) {
    FILE *file = fopen(CONTACT_FILE, "rb");
    FILE *tempFile = fopen("temp.dat", "wb");
    Contact c;
    int found = 0;

    if (!file || !tempFile) {
        printf("Error opening file(s)!\n");
        return;
    }

    while (fread(&c, sizeof(Contact), 1, file)) {
        if (strcmp(c.name, nameToDelete) == 0) {
            found = 1;
            printf("Deleted Contact: %s\n", c.name);
        } else {
            fwrite(&c, sizeof(Contact), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(CONTACT_FILE);
        rename("temp.dat", CONTACT_FILE);
    } else {
        printf("No contact found with the name '%s'.\n", nameToDelete);
        remove("temp.dat");
    }
}

void updateContact(const char *nameToUpdate) {
    FILE *file = fopen(CONTACT_FILE, "rb+");
    Contact c;
    int found = 0;

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&c, sizeof(Contact), 1, file)) {
        if (strcmp(c.name, nameToUpdate) == 0) {
            found = 1;
            printf("Updating Contact: %s\n", c.name);
            printf("Enter New Phone: ");
            scanf("%s", c.phone);
            printf("Enter New Email: ");
            scanf("%s", c.email);
            printf("Enter New Address: ");
            scanf(" %[^\n]", c.address);

            fseek(file, -sizeof(Contact), SEEK_CUR);
            fwrite(&c, sizeof(Contact), 1, file);
            printf("Contact Updated Successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("No contact found with the name '%s'.\n", nameToUpdate);
    }

    fclose(file);
}