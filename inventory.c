#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inventory.h"

#define FILE_PATH "data.csv"
#define RESTOCK_THRESHOLD 5

void addWaterHeater() {
    FILE* file = fopen(FILE_PATH, "a");
    if (!file) {
        printf("Error opening inventory file!\n");
        return;
    }

    WaterHeater heater;
    printf("Enter brand (GSW, Rheem, Rinnai, Combicore, Polaris, Bosch): ");
    scanf("%s", heater.brand);

    // Validate brand entry
    if (strcmp(heater.brand, "GSW") != 0 && strcmp(heater.brand, "Rheem") != 0 &&
        strcmp(heater.brand, "Rinnai") != 0 && strcmp(heater.brand, "Combicore") != 0 &&
        strcmp(heater.brand, "Polaris") != 0 && strcmp(heater.brand, "Bosch") != 0) {
        printf("Invalid brand! Only allowed brands are: GSW, Rheem, Rinnai, Combicore, Polaris, Bosch.\n");
        fclose(file);
        return;
    }

    printf("Enter type: ");
    scanf("%s", heater.type);
    printf("Enter quantity: ");
    scanf("%d", &heater.quantity);

    printf("Enter serial number: ");
    scanf("%s", heater.serialNumber);

    fprintf(file, "%s,%s,%s,%d\n", heater.brand, heater.type, heater.serialNumber, heater.quantity);
    fclose(file);
    printf("Water heater added successfully!\n");
}

void displayInventory() {
    FILE* file = fopen(FILE_PATH, "r");
    if (!file) {
        printf("Error opening inventory file!\n");
        return;
    }

    WaterHeater heater;
    printf("\nInventory:\nBrand | Type | Serial Number | Quantity\n");
    while (fscanf(file, "%[^,],%[^,],%[^,],%d\n", heater.brand, heater.type, heater.serialNumber, &heater.quantity) != EOF) {
        printf("%s | %s | %s | %d\n", heater.brand, heater.type, heater.serialNumber, heater.quantity);
    }
    fclose(file);
}

static int containsIgnoreCase(const char* text, const char* term) {
    size_t tlen = strlen(term);
    if (tlen == 0) return 1;
    for (const char* p = text; *p; p++) {
        size_t i = 0;
        while (i < tlen && p[i] &&
               tolower((unsigned char)p[i]) == tolower((unsigned char)term[i])) {
            i++;
        }
        if (i == tlen) return 1;
    }
    return 0;
}

void searchInventory() {
    FILE* file = fopen(FILE_PATH, "r");
    if (!file) {
        printf("Error opening inventory file!\n");
        return;
    }

    char term[50];
    printf("Enter brand to search for: ");
    scanf("%49s", term);

    WaterHeater heater;
    int found = 0;
    printf("\nSearch results for \"%s\":\nBrand | Type | Serial Number | Quantity\n", term);
    while (fscanf(file, "%[^,],%[^,],%[^,],%d\n", heater.brand, heater.type, heater.serialNumber, &heater.quantity) != EOF) {
        if (containsIgnoreCase(heater.brand, term)) {
            printf("%s | %s | %s | %d\n", heater.brand, heater.type, heater.serialNumber, heater.quantity);
            found++;
        }
    }
    if (found == 0) {
        printf("No water heaters matched \"%s\".\n", term);
    }
    fclose(file);
}

void updateInventoryQuantity() {
    char serial[20];
    int newQuantity;
    printf("Enter serial number: ");
    scanf("%19s", serial);
    printf("Enter new quantity: ");
    if (scanf("%d", &newQuantity) != 1) {
        printf("Invalid quantity!\n");
        return;
    }
    if (newQuantity < 0) {
        printf("Quantity cannot be negative!\n");
        return;
    }

    FILE* file = fopen(FILE_PATH, "r");
    if (!file) {
        printf("Error opening inventory file!\n");
        return;
    }

    FILE* temp = fopen("data_temp.csv", "w");
    if (!temp) {
        printf("Error opening inventory file!\n");
        fclose(file);
        return;
    }

    WaterHeater heater;
    int found = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d\n", heater.brand, heater.type, heater.serialNumber, &heater.quantity) != EOF) {
        if (strcmp(heater.serialNumber, serial) == 0) {
            heater.quantity = newQuantity;
            found = 1;
        }
        fprintf(temp, "%s,%s,%s,%d\n", heater.brand, heater.type, heater.serialNumber, heater.quantity);
    }
    fclose(file);
    fclose(temp);

    if (!found) {
        remove("data_temp.csv");
        printf("No water heater found with serial number %s!\n", serial);
        return;
    }

    remove(FILE_PATH);
    rename("data_temp.csv", FILE_PATH);
    printf("Quantity updated successfully!\n");
}

void checkRestockingAlerts() {
    FILE* file = fopen(FILE_PATH, "r");
    if (!file) {
        printf("Error opening inventory file!\n");
        return;
    }

    WaterHeater heater;
    printf("⚠️ Restocking Alerts ⚠️\n");
    while (fscanf(file, "%[^,],%[^,],%[^,],%d\n", heater.brand, heater.type, heater.serialNumber, &heater.quantity) != EOF) {
        if (heater.quantity < RESTOCK_THRESHOLD) {
            printf("Low stock: %s (%s) - Only %d left!\n", heater.brand, heater.type, heater.quantity);
        }
    }
    fclose(file);
}

void loadInventory() {
    displayInventory();
}

void saveInventory() {
    printf("Inventory saved successfully.\n");
}