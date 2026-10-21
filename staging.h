#ifndef STAGING_H
#define STAGING_H

typedef struct {
    char houseNumber[10];
    char streetName[50];
    char city[30];
    char postalCode[10];
    char scheduledDate[15];
    char crewName[30];
    char tankType[10];
} Staging;

void addStagingTank();
void displayStagingTanks(char* loggedInCrew);

#endif