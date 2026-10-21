#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "users.h"
#include "installation.h"
#include "staging.h"

void menu(int accessLevel, char* username) {
    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Water Heater\n");
        printf("2. Display Inventory\n");
        printf("3. Check Restocking Alerts\n");
        printf("4. Schedule Installation\n");
        printf("5. View Installation Schedule\n");
        printf("6. Stage Tanks for Installation\n");
        printf("7. View My Staged Tanks\n");
        printf("8. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (accessLevel == 1) addWaterHeater();
            else printf("Access Denied!\n");
            break;
        case 2:
            displayInventory();
            break;
        case 3:
            checkRestockingAlerts();
            break;
        case 4:
            if (accessLevel == 1) addInstallation();
            else printf("Access Denied!\n");
            break;
        case 5:
            displaySchedule();
            break;
        case 6:
            if (accessLevel == 1) addStagingTank();
            else printf("Access Denied!\n");
            break;
        case 7:
            if (accessLevel == 2) displayStagingTanks(username);
            else printf("Access Denied!\n");
            break;
        case 8:
            return;
        default:
            printf("Invalid choice!\n");
        }
    }
}

int main() {
    intro();
    char username[20], password[20];
    int accessLevel;

    while (1) {
        printf("\nEnter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        accessLevel = authenticateUser(username, password);

        if (accessLevel > 0) {
            printf("Login Successful! Welcome, %s.\n", username);
            menu(accessLevel, username);
            break;
        }
        else {
            printf("Invalid Credentials! Try again.\n");
        }
    }

    return 0;
}