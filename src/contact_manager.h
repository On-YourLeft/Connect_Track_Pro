#ifndef CONTACT_MANAGER_H
#define CONTACT_MANAGER_H

typedef struct {
    char name[50];
    char phone[15];
    char email[50];
} Contact;

void add_contact(const Contact *contact);
void delete_contact(const char *name);
void update_contact(const Contact *contact);
void display_contacts();

#endif
