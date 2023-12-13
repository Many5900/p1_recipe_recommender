#include <stdio.h>
#include <stdlib.h>
#include "../deserializer/deserializer.h"

void print_ingredients(const IngredientsArray_t* itemArray) {
    if (itemArray == NULL || itemArray->ingredients == NULL) {
        printf("No items to print.\n");
        return;
    }

    for (int i = 0; i < itemArray->count; i++) {
        printf("Item nr. %d\n", i + 1);
        printf("\tIngredient:  %s --- ID: %s\n", itemArray->ingredients[i].title, itemArray->ingredients[i].id);
        printf("\tQuantity:    %dg --- Price: %dDKK\n", itemArray->ingredients[i].qty, itemArray->ingredients[i].price);
        printf("\tExpire Date: %s --- Days left: %d\n", itemArray->ingredients[i].expire_date, itemArray->ingredients[i].days_before_expiration);
        printf("\n");
    }
}

// Function til at dealokere mem
void free_ingredients(IngredientsArray_t* itemArray) {
    if (itemArray != NULL) {
        for (int i = 0; i < itemArray->count; i++) {
            free(itemArray->ingredients[i].id);
            free(itemArray->ingredients[i].title);
            free(itemArray->ingredients[i].expire_date);
        }
        free(itemArray->ingredients);
    }
}

void print_stats(const StatsArray_t* statsArray) {
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
void free_stats(StatsArray_t* statsArray) {
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