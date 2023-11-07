// main.c
#include "api/api_functions.h"
#include "item/item_functions.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Calling api function...\n");
    //api("/add_item?title=choko&qty=2525&expire_date=10-12-2023&price=233");





    printf("\nCalling api_json function...\n");
    char *json_response = items();
    printf("TEST");

    if (json_response != NULL) {
        printf("JSON Response:\n%s\n", json_response);
        free(json_response);
    } else {
        printf("No JSON response... Hvad så nu?..\n");
    }

    //add_item("vandmand", "Neste_uge", 50, 200);
    // api("/add_item?title=vandmand&expire_date=N%C3%A6ste_uge&qty=50&price=200");

    char* res = get_by_title("majsmel");
    printf("%s", res);
    return 0;
}
