#include <stdio.h>
#include <string.h>
#include "diary_manager.h"
#include "notifications.h" // Include the header file

const char *DIARY_FILE = "diary.dat"; // Define DIARY_FILE here

void addDiaryEntry() {
    FILE *file = fopen(DIARY_FILE, "ab"); // Open in append mode
    if (!file) {
        perror("Error opening diary file");
        return;
    }

    DiaryEntry d;

    fflush(stdin);

    // Prompt for the date
    printf("Enter Date (DD-MM-YYYY): ");
    if (fgets(d.date, sizeof(d.date), stdin) == NULL || d.date[0] == '\n') {
        printf("Invalid input for date.\n");
        fclose(file);
        return;
    }
    d.date[strcspn(d.date, "\n")] = '\0'; // Remove newline character

    // Clear the input buffer to ensure clean note entry
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    // Prompt for the note
    printf("Enter Note: ");
    if (fgets(d.note, sizeof(d.note), stdin) == NULL || d.note[0] == '\n') {
        printf("Invalid input for note.\n");
        fclose(file);
        return;
    }
    d.note[strcspn(d.note, "\n")] = '\0'; // Remove newline character

    // Write the entry to the file
    if (fwrite(&d, sizeof(DiaryEntry), 1, file) != 1) {
        perror("Error writing to diary file");
    } else {
        printf("Diary Entry Added Successfully!\n");
    }

    fclose(file);
}

void viewDiary() {
    FILE *file = fopen(DIARY_FILE, "rb");
    if (!file) {
        perror("Error opening diary file");
        return;
    }

    DiaryEntry d; // Struct to hold diary entry data
    int entryCount = 0;

    printf("\nDiary Entries:\n");
    printf("=====================================\n");

    // Read and display all entries from the diary file
    while (fread(&d, sizeof(DiaryEntry), 1, file) == 1) {
        printf("Entry #%d:\n", ++entryCount);
        printf("Date: %s\n", d.date);
        printf("Note: %s\n", d.note);
        printf("-------------------------------------\n");
    }

    if (entryCount == 0) {
        printf("No diary entries found.\n");
    }

    if (ferror(file)) {
        perror("Error reading from diary file");
    }

    fclose(file);
}



/*void searchDiaryByDate(const char *date) {
    FILE *file = fopen(DIARY_FILE, "rb");
    if (!file) {
        perror("Error opening diary file");
        return;
    }

    DiaryEntry d;
    int found = 0;

    printf("\nSearching for Diary Entries on Date: %s\n", date);
    printf("=====================================\n");

    while (fread(&d, sizeof(DiaryEntry), 1, file) == 1) {
        if (strcmp(d.date, date) == 0) {
            printf("Date: %s\n", d.date);
            printf("Note: %s\n", d.note);
            printf("-------------------------------------\n");
            found = 1;
        }
    }

    if (!found) {
        printf("No diary entries found for the given date.\n");
    }

    if (ferror(file)) {
        perror("Error reading from diary file");
    }

    fclose(file);
}*/


void deleteDiaryEntry(const char *date) {
    FILE *file = fopen(DIARY_FILE, "rb");
    if (!file) {
        perror("Error opening diary file");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    DiaryEntry d;
    int found = 0;

    while (fread(&d, sizeof(DiaryEntry), 1, file) == 1) {
        if (strcmp(d.date, date) == 0) {
            found = 1;
            printf("Deleted Diary Entry for Date: %s\n", d.date);
        } else {
            if (fwrite(&d, sizeof(DiaryEntry), 1, tempFile) != 1) {
                perror("Error writing to temporary file");
                fclose(file);
                fclose(tempFile);
                return;
            }
        }
    }

    if (!found) {
        printf("No diary entry found for the date '%s'.\n", date);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        if (remove(DIARY_FILE) != 0 || rename("temp.dat", DIARY_FILE) != 0) {
            perror("Error updating diary file");
        }
    } else {
        remove("temp.dat");
    }
}


void updateDiaryEntry(const char *date) {
    FILE *file = fopen(DIARY_FILE, "rb+");
    if (!file) {
        perror("Error opening diary file");
        return;
    }

    DiaryEntry d;
    int found = 0;

    while (fread(&d, sizeof(DiaryEntry), 1, file) == 1) {
        if (strcmp(d.date, date) == 0) {
            found = 1;

            printf("Updating Diary Entry for Date: %s\n", d.date);

            printf("Enter New Note: ");
            if (fgets(d.note, sizeof(d.note), stdin) == NULL) {
                printf("Error reading note input.\n");
                fclose(file);
                return;
            }
            d.note[strcspn(d.note, "\n")] = '\0'; // Remove newline

            fseek(file, -sizeof(DiaryEntry), SEEK_CUR);
            if (fwrite(&d, sizeof(DiaryEntry), 1, file) != 1) {
                perror("Error updating diary entry");
            } else {
                printf("Diary Entry Updated Successfully!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("No diary entry found for the date '%s'.\n", date);
    }

    if (ferror(file)) {
        perror("Error reading/writing to diary file");
    }

    fclose(file);
}