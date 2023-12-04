//
// Created by Marc Nygaard on 04/12/2023.
//
#include <stdio.h>
#include <ctype.h>
#include "../../time/time_and_date.h"
#include "../../item/item_functions.h"
#include "../../deserializer/deserializer.h"
#include "../../print/print.h"



/*************************************
***** space & convertToLowerCase *****
*************************************/

void space() {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void convertToLowerCase(char str[]) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}





/****************************
***** ITEM add & delete *****
****************************/

void add_item(char title[], char expiration_date[], int *qty, int *price) {
    int i = 0;
    printf("Enter item name: ");
    scanf("%s", title);
    convertToLowerCase(title);

    printf("Enter quantity of item: ");
    scanf("%d", qty);
    printf("Enter expiration date of item (format : dd-mm-yyyy): ");
    scanf("%s", expiration_date);
    //printf(expiration_date);

    // Check if the item is expired
    int days_difference = calculateDaysDifference(convertToDate(expiration_date));

    printf("Enter price of item (in danish kr): ");
    scanf("%d", price);

    db_add_item(title, expiration_date, *qty, *price);
}

void delete_item() {
    char id[26];
    space();
    printf("Enter item id: ");
    scanf("%s", id);

    // Get the item with the specified ID
    const char *json_string = db_get_by_id(id);
    ItemArray itemArray = deserialize_items(json_string);
    print_items(&itemArray);
    free_items(&itemArray);

    // Are U sure?
    printf("Are you shure you want to delete the item above?\n");
    printf("[1] Yes\n");
    printf("[2] No\n");

    while (1) {
        char confirm;
        scanf("%c", &confirm);
        if (confirm == '1') {
            db_delete_by_id(id);
            space();
            break;
        } else if (confirm == '2') {
            space();
            break;
        }
    }
}