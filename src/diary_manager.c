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


void deleteDiaryEntry() {
    char date[20] = {0};

    fflush(stdin);

    // Prompt user for date
    printf("Enter Date (DD-MM-YYYY) to delete entries: ");
    if (fgets(date, sizeof(date), stdin)) {
        date[strcspn(date, "\n")] = '\0'; // Remove newline
        printf("Received input for deletion: '%s'\n", date); // Debugging output
    } else {
        printf("Error reading input.\n");
        return;
    }

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
    int found = 0, entryNumber = 0, deleteChoice = 0;

    printf("\nMatching Entries:\n");
    printf("=====================================\n");

    // First pass: Display all matching entries with a number
    while (fread(&d, sizeof(DiaryEntry), 1, file)) {
        if (strcmp(d.date, date) == 0) {
            found = 1;
            entryNumber++;
            printf("Entry #%d:\n", entryNumber);
            printf("Date: %s\n", d.date);
            printf("Note: %s\n", d.note);
            printf("-------------------------------------\n");
        }
    }

    if (!found) {
        printf("No diary entries found for the date '%s'.\n", date);
        fclose(file);
        fclose(tempFile);
        remove("temp.dat");
        return;
    }

    // Ask the user which entry to delete
    printf("Enter the entry number to delete (or 0 to cancel): ");
    if (scanf("%d", &deleteChoice) != 1 || deleteChoice < 0 || deleteChoice > entryNumber) {
        printf("Invalid choice. Operation canceled.\n");
        fclose(file);
        fclose(tempFile);
        remove("temp.dat");
        return;
    }

    rewind(file); // Rewind file to start for second pass
    entryNumber = 0;

    // Second pass: Write non-deleted entries to the temp file
    while (fread(&d, sizeof(DiaryEntry), 1, file)) {
        if (strcmp(d.date, date) == 0) {
            entryNumber++;
            if (entryNumber == deleteChoice) {
                printf("Deleted Diary Entry #%d for Date: %s\n", entryNumber, d.date);
                continue; // Skip writing this entry
            }
        }
        fwrite(&d, sizeof(DiaryEntry), 1, tempFile);
    }

    fclose(file);
    fclose(tempFile);

    if (remove(DIARY_FILE) != 0 || rename("temp.dat", DIARY_FILE) != 0) {
        perror("Error updating diary file");
    } else {
        printf("Diary entry deleted successfully.\n");
    }
}


void updateDiaryEntry() {
    char date[20] = {0};

    fflush(stdin);

    // Prompt user for date
    printf("Enter Date (DD-MM-YYYY): ");
    if (fgets(date, sizeof(date), stdin)) {
        date[strcspn(date, "\n")] = '\0'; // Remove newline
        printf("Received input for update: '%s'\n", date); // Debugging output
    } else {
        printf("Error reading input.\n");
        return;
    }

    FILE *file = fopen(DIARY_FILE, "rb+");
    if (!file) {
        perror("Error opening diary file");
        return;
    }

    DiaryEntry d;
    int found = 0, entryNumber = 0, updateChoice = 0;
    long positions[100] = {0}; // Array to store positions of matching entries

    printf("\nMatching Entries:\n");
    printf("=====================================\n");

    // First pass: Display all matching entries with a number
    while (fread(&d, sizeof(DiaryEntry), 1, file)) {
        if (strcmp(d.date, date) == 0) {
            found = 1;
            positions[entryNumber] = ftell(file) - sizeof(DiaryEntry); // Store position
            entryNumber++;
            printf("Entry #%d:\n", entryNumber);
            printf("Date: %s\n", d.date);
            printf("Note: %s\n", d.note);
            printf("-------------------------------------\n");
        }
    }

    if (!found) {
        printf("No diary entries found for the given date.\n");
        fclose(file);
        return;
    }

    // Ask user to select the entry to update
    printf("Select the entry number to update (1-%d): ", entryNumber);
    if (scanf("%d", &updateChoice) != 1 || updateChoice < 1 || updateChoice > entryNumber) {
        printf("Invalid choice.\n");
        fclose(file);
        return;
    }
    getchar(); // Clear newline left in buffer

    // Seek to the selected entry
    fseek(file, positions[updateChoice - 1], SEEK_SET);
    if (fread(&d, sizeof(DiaryEntry), 1, file) != 1) {
        perror("Error reading selected entry.");
        fclose(file);
        return;
    }

    // Update the selected entry
    printf("Updating Entry #%d:\n", updateChoice);
    printf("Current Note: %s\n", d.note);
    printf("Enter New Note: ");
    if (fgets(d.note, sizeof(d.note), stdin)) {
        d.note[strcspn(d.note, "\n")] = '\0'; // Remove newline
    } else {
        printf("Error reading input for note.\n");
        fclose(file);
        return;
    }

    // Write the updated entry back to the file
    fseek(file, positions[updateChoice - 1], SEEK_SET);
    if (fwrite(&d, sizeof(DiaryEntry), 1, file) != 1) {
        perror("Error updating diary entry.");
    } else {
        printf("Diary Entry Updated Successfully!\n");
    }

    fclose(file);
}
