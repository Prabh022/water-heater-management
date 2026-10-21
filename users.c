#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "users.h"

#define USER_FILE "users.csv"

int authenticateUser(char* username, char* password) {
    FILE* file = fopen(USER_FILE, "r");
    if (!file) {
        printf("Error opening user database!\n");
        return 0;
    }

    User user ;
    while (fscanf(file, "%[^,],%[^,],%d\n", user.username, user.password, &user.accessLevel) != EOF) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            fclose(file);
            return user.accessLevel;
        }
    }

    fclose(file);
    return 0; // Authentication failed
}
void intro() {
    printf("-----------------------------------------------------\n");
    printf("+          Welcome to My Company Database!          +\n");
    printf("-----------------------------------------------------\n");
}