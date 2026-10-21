#ifndef INSTALLATION_H
#define INSTALLATION_H

typedef struct {
    char crewName[30];
    char address[50];
    char date[15];
    char tankType[10];
} Installation;

void addInstallation();
void displaySchedule();

#endif