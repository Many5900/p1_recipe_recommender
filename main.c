// main.c
#include "db/api_functions.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Calling api function...\n");
    api("/add_item?title=choko&qty=2525&expire_date=10-12-2023");





    printf("\nCalling api_json function...\n");
    char *json_response = api_json("/items");

    if (json_response != NULL) {
        printf("JSON Response:\n%s\n", json_response);
        free(json_response);
    } else {
        printf("No JSON response... Hvad så nu?..\n");
    }

    return 0;
}
