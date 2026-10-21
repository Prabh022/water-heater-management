#ifndef USERS_H
#define USERS_H

typedef struct {
    char username[20];
    char password[20];
    int accessLevel; // 1: Admin, 2: Installer
} User;

int authenticateUser(char* username, char* password);
void intro();

#endif