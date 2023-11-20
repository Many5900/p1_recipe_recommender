// main.c
#include "api/api_functions.h"
#include "item/item_functions.h"
#include "deserializer/deserializer.h"
#include "print/print.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    const char *json_string = items();

    ItemArray itemArray = deserialize_items(json_string);
    print_items(&itemArray);
    free_items(&itemArray);





    // char* items();
    // To fetch all items as JSON data

    // void add_item(const char *title, const char *expire_date, int qty, int price);
    // Add one item to the DB
    //add_item("milk", "15-11-2023", 1000, 13);

    // char* get_by_id(const char *id);
    // Get a single item by its ID

    // char* get_by_title(const char *title);
    // Get multiple item of the same title

    // void delete_by_id(const char *id);
    // Delete a single item by its ID
    //delete_by_id("item:");

    // void delete_by_title(const char *title);
    // Delete all items of the same title

    // void update_qty(const char* id, int qty);
    // Update qty for one item by its ID

    // void update(const char* id, const char *title, const char *expire_date, int qty, int price);
    // Update all params for one item by its ID




    return 0;
}
