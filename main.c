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

    return 0;
}
