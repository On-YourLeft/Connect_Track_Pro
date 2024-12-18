#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"
#include "contact_manager.h"
#include "diary_manager.h"
#include "utils.h"
#include "notifications.h"

void login() 
{
    char username[20], password[20];
    char correctUsername[] = "admin";
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
            checkNotifications();  // Check for notifications
            mainMenu();
            break;
        } else {
            printf("Incorrect Username or Password. Try again.\n");
        }
    }
}

void mainMenu() {
    int choice;

    while (1) {
        printf("\n=== Main Menu ===\n");
        printf("1. Manage Contacts\n");
        printf("2. Manage Diary\n");
        printf("3. View Calendar\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: contactMenu(); break;
            case 2: diaryMenu(); break;
            case 3: calendarView(); break;
            case 4: printf("Goodbye!\n"); exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}

void contactMenu()
{

}

void diaryMenu()
{
    
}