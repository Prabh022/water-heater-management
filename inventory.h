#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct {
    char brand[20];
    char type[10];
    char serialNumber[20]; // Manual entry required  
    int quantity;
} WaterHeater;

void addWaterHeater();
void displayInventory();
void checkRestockingAlerts();
void loadInventory();
void saveInventory();

#endif