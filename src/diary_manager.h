
#ifndef DIARY_MANAGER_H
#define DIARY_MANAGER_H

#define MAX_DATE_LEN 11
#define MAX_NOTE_LEN 256

typedef struct {
    char date[MAX_DATE_LEN];
    char note[MAX_NOTE_LEN];
} DiaryEntry;

extern const char *DIARY_FILE;

void addDiaryEntry(const char *entry);

#endif // DIARY_MANAGER_H
