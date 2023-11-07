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
        printf("\tID: %s\n", itemArray->items[i].id);
        printf("\tTitle: %s\n", itemArray->items[i].title);
        printf("\tExpire Date: %s\n", itemArray->items[i].expire_date);
        printf("\tQuantity: %d\n", itemArray->items[i].qty);
        printf("\tPrice: %d\n", itemArray->items[i].price);
        printf("\n");
    }
}

// Function til at dealokere mem
void free_items(ItemArray* itemArray) {
    if (itemArray != NULL) {
        for (int i = 0; i < itemArray->count; i++) {
            free(itemArray->items[i].expire_date);
            free(itemArray->items[i].id);
            free(itemArray->items[i].title);
        }
        free(itemArray->items);
    }
}