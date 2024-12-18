#include <stdio.h>
#include <string.h>
#include "diary_manager.h"
#include "notifications.h" // Include the header file

const char *DIARY_FILE = "diary.dat"; // Define DIARY_FILE here

void addDiaryEntry(const char *entry) 
{
    FILE *file = fopen(DIARY_FILE, "ab"); // Open in append mode
    if (!file) {
        perror("Error opening diary file");
        return;
    }

    DiaryEntry d;

    printf("Enter Date (DD-MM-YYYY): ");
    if (fgets(d.date, sizeof(d.date), stdin) == NULL) {
        printf("Error reading date input.\n");
        fclose(file);
        return;
    }
    d.date[strcspn(d.date, "\n")] = '\0'; // Remove newline

    printf("Enter Note: ");
    if (fgets(d.note, sizeof(d.note), stdin) == NULL) {
        printf("Error reading note input.\n");
        fclose(file);
        return;
    }
    d.note[strcspn(d.note, "\n")] = '\0'; // Remove newline

    if (fwrite(&d, sizeof(DiaryEntry), 1, file) != 1) {
        perror("Error writing to diary file");
    } else {
        printf("Diary Entry Added Successfully!\n");
    }

    fclose(file);
}
