#include <stdio.h>
#include <string.h>
#include "search_manager.h"
#include "contact_manager.h"
#include "diary_manager.h"

// Search Contact by Name
void searchContactByName(const char *name) {
    FILE *file = fopen(CONTACT_FILE, "rb");
    Contact c;
    int found = 0;

    if (!file) {
        printf("Error opening contact file!\n");
        return;
    }

    while (fread(&c, sizeof(Contact), 1, file)) {
        if (strcmp(c.name, name) == 0) {
            printf("Contact Found:\n");
            printf("Name: %s\nPhone: %s\nEmail: %s\nAddress: %s\n", c.name, c.phone, c.email, c.address);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    }

    fclose(file);
}

// Search Diary Entry by Date
void searchDiaryByDate(const char *date) {
    FILE *file = fopen(DIARY_FILE, "rb");
    DiaryEntry d;
    int found = 0;

    if (!file) {
        printf("Error opening diary file!\n");
        return;
    }

    while (fread(&d, sizeof(DiaryEntry), 1, file)) {
        if (strcmp(d.date, date) == 0) {
            printf("Diary Entry Found:\n");
            printf("Date: %s\nNote: %s\n", d.date, d.note);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Diary entry not found for the given date!\n");
    }

    fclose(file);
}

// Search for Diary Entries by Keyword
void searchDiaryByKeyword(const char *keyword) {
    FILE *file = fopen(DIARY_FILE, "rb");
    DiaryEntry d;
    int found = 0;

    if (!file) {
        printf("Error opening diary file!\n");
        return;
    }

    while (fread(&d, sizeof(DiaryEntry), 1, file)) {
        if (strstr(d.note, keyword)) {
            printf("Found Diary Entry:\n");
            printf("Date: %s\nNote: %s\n", d.date, d.note);
            found = 1;
        }
    }

    if (!found) {
        printf("No diary entries found with the given keyword!\n");
    }

    fclose(file);
}

// Helper function to perform search
void performSearch() {
    int choice;
    char name[50], date[20], keyword[100];

    printf("\n=== Search Menu ===\n");
    printf("1. Search Contacts by Name\n");
    printf("2. Search Diary Entries by Date\n");
    printf("3. Search Diary Entries by Keyword\n");
    printf("4. Return to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter Contact Name to Search: ");
            scanf(" %[^\n]", name);
            searchContactByName(name);
            break;
        case 2:
            printf("Enter Date (DD-MM-YYYY) to Search: ");
            scanf("%s", date);
            searchDiaryByDate(date);
            break;
        case 3:
            printf("Enter Keyword to Search in Diary: ");
            scanf(" %[^\n]", keyword);
            searchDiaryByKeyword(keyword);
            break;
        case 4:
            return;
        default:
            printf("Invalid Choice!\n");
            break;
    }
}