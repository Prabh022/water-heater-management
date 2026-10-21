#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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