#include <stdio.h>
#include "diary_manager.h"

void create_diary_entry(const char *entry) {
    FILE *file = fopen("diary.txt", "a");
    if (file) {
        fprintf(file, "%s\n", entry);
        fclose(file);
        printf("Diary entry saved.\n");
    } else {
        printf("Error: Unable to save diary entry.\n");
    }
}

void view_diary_entries() {
    char buffer[256];
    FILE *file = fopen("diary.txt", "r");
    if (file) {
        printf("Diary Entries:\n");
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("No diary entries found.\n");
    }
}
