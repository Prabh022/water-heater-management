#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staging.h"

#define STAGING_FILE "staging.csv"

void addStagingTank() {
    FILE* file = fopen(STAGING_FILE, "a");
    if (!file) {
        printf("Error opening staging file!\n");
        return;
    }

    Staging staging;
    printf("Enter House Number: ");
    scanf("%s", staging.houseNumber);
    printf("Enter Street Name: ");
    scanf(" %[^\n]", staging.streetName);
    printf("Enter City: ");
    scanf("%s", staging.city);
    printf("Enter Postal Code: ");
    scanf("%s", staging.postalCode);
    printf("Enter Scheduled Date (YYYY-MM-DD): ");
    scanf("%s", staging.scheduledDate);
    printf("Enter Crew Name: ");
    scanf("%s", staging.crewName);
    printf("Enter Tank Type: ");
    scanf("%s", staging.tankType);

    fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", staging.houseNumber, staging.streetName, staging.city, staging.postalCode, staging.scheduledDate, staging.crewName, staging.tankType);
    fclose(file);
}

void displayStagingTanks(char* loggedInCrew) {
    FILE* file = fopen(STAGING_FILE, "r");
    if (!file) {
        printf("Error opening staging file!\n");
        return;
    }

    Staging staging;
    int found = 0;
    printf("\nStaged Tanks for Installation (Assigned to: %s)\n", loggedInCrew);
    printf("House No | Street | City | Postal Code | Date | Tank Type\n");

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", staging.houseNumber, staging.streetName, staging.city, staging.postalCode, staging.scheduledDate, staging.crewName, staging.tankType) != EOF) {
        if (strcmp(staging.crewName, loggedInCrew) == 0) { // Only show tanks for the logged-in installer
            printf("%s | %s | %s | %s | %s | %s\n", staging.houseNumber, staging.streetName, staging.city, staging.postalCode, staging.scheduledDate, staging.tankType);
            found = 1;
        }
    }

    if (!found) {
        printf("No tanks staged for installation assigned to you.\n");
    }

    fclose(file);
}