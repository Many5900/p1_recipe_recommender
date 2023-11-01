// main.c
#include "db/api_functions.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Use the api function to print the whole HTTP response to stdout
    printf("Calling api function...\n");
    api("/items");

    // Use the api_json function to get just the JSON part of the response
    printf("\nCalling api_json function...\n");
    char *json_response = api_json("/items");

    if (json_response != NULL) {
        printf("JSON Response:\n%s\n", json_response);
        free(json_response); // It's important to free the memory to prevent leaks
    } else {
        printf("No JSON response received or an error occurred.\n");
    }

    return 0;
}
