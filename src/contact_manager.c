#include <stdio.h>
#include <string.h>
#include "contact_manager.h"

#define MAX_CONTACTS 100

static Contact contacts[MAX_CONTACTS];
static int contact_count = 0;

void add_contact(const Contact *contact) {
    if (contact_count < MAX_CONTACTS) {
        contacts[contact_count++] = *contact;
        printf("Contact added: %s\n", contact->name);
    } else {
        printf("Contact list is full!\n");
    }
}

void delete_contact(const char *name) {
    for (int i = 0; i < contact_count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            for (int j = i; j < contact_count - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            contact_count--;
            printf("Contact deleted: %s\n", name);
            return;
        }
    }
    printf("Contact not found: %s\n", name);
}

void update_contact(const Contact *contact) {
    for (int i = 0; i < contact_count; i++) {
        if (strcmp(contacts[i].name, contact->name) == 0) {
            contacts[i] = *contact;
            printf("Contact updated: %s\n", contact->name);
            return;
        }
    }
    printf("Contact not found: %s\n", contact->name);
}

void display_contacts() {
    printf("Contact List:\n");
    for (int i = 0; i < contact_count; i++) {
        printf("Name: %s, Phone: %s, Email: %s\n",
               contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}
