#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "installation.h"

#define INSTALL_FILE "installation.csv"\

void addInstallation() {
    FILE *file = fopen(INSTALL_FILE, "a");
    if (!file) {
        printf("Error opening installation file!\n");
        return;
    }
    
    Installation install;
    printf("Enter Crew Name: ");
    scanf("%s", install.crewName);
    printf("Enter House Address: ");
    scanf("%s", install.address);
    printf("Enter Scheduled Date (YYYY-MM-DD): ");
    scanf("%s", install.date);
    printf("Enter Tank Type: ");
    scanf("%s", install.tankType);

    fprintf(file, "%s,%s,%s,%s\n", install.crewName, install.address, install.date, install.tankType);
    fclose(file);
}

void displaySchedule() {
    FILE *file = fopen(INSTALL_FILE, "r");
    if (!file) {
        printf("Error opening installation file!\n");
        return;
    }

    Installation install;
    printf("Upcoming Installations:\nCrew | Address | Date | Tank Type\n");
    while (fscanf(file, "%[^,],%[^,],%[^,],%s\n", install.crewName, install.address, install.date, install.tankType) != EOF) {
        printf("%s | %s | %s | %s\n", install.crewName, install.address, install.date, install.tankType);
    }
    fclose(file);
}