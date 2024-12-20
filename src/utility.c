#include <stdio.h>
#include <string.h>
#include <time.h>
#include "utility.h"
#include "diary_manager.h"

void calendarView() 
{
    int year, month, day, daysInMonth, startDay, i;
    FILE *file = fopen(DIARY_FILE, "rb");
    DiaryEntry d;
    int markedDays[32] = {0}; 

    printf("Enter Month (1-12): ");
    scanf("%d", &month);
    printf("Enter Year: ");
    scanf("%d", &year);

    if (month < 1 || month > 12) {
        printf("Invalid month. Please enter a value between 1 and 12.\n");
        return;
    }

    // Check the diary file for entries in the given month/year
    if (file) {
        char targetDate[20];
        sprintf(targetDate, "-%02d-%04d", month, year); // Format to match dates like "-06-2024"

        while (fread(&d, sizeof(DiaryEntry), 1, file)) {
            if (strstr(d.date, targetDate)) { 
                int entryDay;
                sscanf(d.date, "%02d", &entryDay);
                if (entryDay >= 1 && entryDay <= 31) {
                    markedDays[entryDay] = 1; // Mark the day
                }
            }
        }
        fclose(file);
    } else {
        printf("No diary file found. Calendar will be shown without highlights.\n");
    }

    // Get the start day of the month (Zeller's Congruence)
    struct tm firstDay = {0};
    firstDay.tm_mday = 1;
    firstDay.tm_mon = month - 1; // tm_mon is 0-based
    firstDay.tm_year = year - 1900;

    mktime(&firstDay); // Normalize time
    startDay = firstDay.tm_wday; // 0 = Sunday

    // Days in each month
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        monthDays[1] = 29; // Leap year
    }
    daysInMonth = monthDays[month - 1];

    // Print the calendar
    printf("\n   Calendar - %02d/%04d\n", month, year);
    printf(" Sun Mon Tue Wed Thu Fri Sat\n");

    for (i = 0; i < startDay; i++) {
        printf("    "); // Blank spaces for days before the 1st
    }

    for (day = 1; day <= daysInMonth; day++) {
        if (markedDays[day]) {
            printf(" *%02d", day); // Highlight days with diary entries
        } else {
            printf("  %02d", day);
        }
        if ((day + startDay) % 7 == 0) {
            printf("\n"); // New week
        }
    }
    if ((day + startDay - 1) % 7 != 0) {
        printf("\n"); // Final newline
    }
}
