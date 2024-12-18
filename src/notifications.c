#include <stdio.h>
#include <time.h>
#include <string.h>
#include "notifications.h"
#include "diary_manager.h"

void checkNotifications(void) {
    FILE *file = fopen(DIARY_FILE, "rb");
    DiaryEntry d;
    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    char currentDate[20];

    if (!file) {
        printf("No diary entries to check for notifications.\n");
        return;
    }

    // Get today's date as a string
    sprintf(currentDate, "%02d-%02d-%04d", today.tm_mday, today.tm_mon + 1, today.tm_year + 1900);

    printf("\n=== Notifications ===\n");

    int found = 0;
    while (fread(&d, sizeof(DiaryEntry), 1, file)) {
        if (strcmp(d.date, currentDate) == 0) {
            printf("Reminder: Diary Entry for Today - %s\n", d.note);
            found = 1;
        }
    }

    if (!found) {
        printf("No notifications for today.\n");
    }

    fclose(file);
}
