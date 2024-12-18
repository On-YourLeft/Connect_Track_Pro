#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

typedef struct {
    char name[50];
    char phone[15];
    char email[50];
    char address[100];
} Contact;

extern const char *CONTACT_FILE;

void addContact();
void viewContacts();
void searchContacts();
void deleteContact();
void updateContact();

#endif
