#include <stdio.h>
#include <stdlib.h>
#include "../deserializer/deserializer.h"

void print_items(const ItemArray* itemArray) {
    if (itemArray == NULL || itemArray->items == NULL) {
        printf("No items to print.\n");
        return;
    }

    for (int i = 0; i < itemArray->count; i++) {
        printf("Item %d:\n", i + 1);
        printf("\tID:            %s\n", itemArray->items[i].id);
        printf("\tTitle:         %s\n", itemArray->items[i].title);
        printf("\tExpire Date:   %s\n", itemArray->items[i].expire_date);
        printf("\tDays left:     %d\n", itemArray->items[i].days_before_expiration);
        printf("\tQuantity (g):  %d\n", itemArray->items[i].qty);
        printf("\tPrice (DKK):   %d\n", itemArray->items[i].price);
        printf("\n");
    }
}

// Function til at dealokere mem
void free_items(ItemArray* itemArray) {
    if (itemArray != NULL) {
        for (int i = 0; i < itemArray->count; i++) {
            free(itemArray->items[i].id);
            free(itemArray->items[i].title);
            free(itemArray->items[i].expire_date);
        }
        free(itemArray->items);
    }
}

void print_stats(const StatsArray* statsArray) {
    if (statsArray == NULL || statsArray->stats == NULL) {
        printf("No items to print.\n");
        return;
    }

    for (int i = 0; i < statsArray->count; i++) {
        printf("Stats %d:\n", i + 1);
        printf("\tID:                  %s\n", statsArray->stats[i].id);
        printf("\tTitle:               %s\n", statsArray->stats[i].title);
        printf("\tExpire Date:         %s\n", statsArray->stats[i].expire_date);
        printf("\tQuantity (g):        %d\n", statsArray->stats[i].qty);
        printf("\tStart quantity (g):  %d\n", statsArray->stats[i].start_qty);
        printf("\tPrice (DKK):         %d\n", statsArray->stats[i].price);
        printf("\tWeek:                %d\n", statsArray->stats[i].week);
        printf("\tYear:                %s\n", statsArray->stats[i].year);

        printf("\n");
    }
}

// Function til at dealokere mem
void free_stats(StatsArray* statsArray) {
    if (statsArray != NULL) {
        for (int i = 0; i < statsArray->count; i++) {
            free(statsArray->stats[i].id);
            free(statsArray->stats[i].title);
            free(statsArray->stats[i].expire_date);
            free(statsArray->stats[i].year);

        }
        free(statsArray->stats);
    }
}