
#ifndef DIARY_MANAGER_H
#define DIARY_MANAGER_H

#define MAX_DATE_LEN 11
#define MAX_NOTE_LEN 256

typedef struct {
    char date[MAX_DATE_LEN];
    char note[MAX_NOTE_LEN];
} DiaryEntry;

extern const char *DIARY_FILE;

void addDiaryEntry();
void viewDiary();
void searchDiaryByDate();
void deleteDiaryEntry();
void updateDiaryEntry();

#endif // DIARY_MANAGER_H
