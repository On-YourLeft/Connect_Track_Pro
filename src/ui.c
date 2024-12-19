#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"
#include "contact_manager.h"
#include "diary_manager.h"
#include "utility.h"
#include "notifications.h"
#include "search_manager.h"

void login() 
{
    char username[20], password[20];
    char correctUsername[] = "admin123";
    char correctPassword[] = "password";

    printf("Welcome to Connect Track Pro\n");
    printf("Please Login\n");

    while (1) {
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
            printf("Login Successful!\n");
            mainMenu();
            break;
        } else {
            printf("Incorrect Username or Password. Try again.\n");
        }
    }
}

void mainMenu() {

    checkNotifications(); 
    
    int choice;

    while (1) {
        printf("\n=== Main Menu ===\n");
        printf("1. Manage Contacts\n");
        printf("2. Manage Diary\n");
        printf("3. View Calendar\n");
        printf("4. Perform Search\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: contactMenu(); break;
            case 2: diaryMenu(); break;
            case 3: calendarView(); break;
            case 4: performSearch(); break;
            case 5: printf("Goodbye!\n"); exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}

void contactMenu()
{
    int choice;
    while (1)
    {
        printf("\n===== Contacts Menu =====\n");
        printf("1. Add contact.\n");
        printf("2. View contacts.\n");
        printf("3. Delete contact.\n");
        printf("4. Update Contact.\n");
        printf("5. Back to main menu.\n");
        printf("Enter your choice: ");
        scanf(" %d",&choice);

        switch(choice)
        {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: deleteContact(); break;
            case 4: updateContact(); break;
            case 5: mainMenu(); break;
        }
    }
}

void diaryMenu()
{
    int choice;
    while (1)
    {
        printf("\n===== Diary Menu =====\n");
        printf("1. Add diary entry.\n");
        printf("2. View diary entries.\n");
        printf("3. Delete diary entry.\n");
        printf("4. Update diary entry.\n");
        printf("5. Back to main menu.\n");
        printf("Enter your choice: ");
        scanf(" %d",&choice);

        switch(choice)
        {
            case 1: addDiaryEntry(); break;
            case 2: viewDiary(); break;
            case 3: deleteDiaryEntry(); break;
            case 4: updateDiaryEntry(); break;
            case 5: mainMenu(); break;
        }
    }
}