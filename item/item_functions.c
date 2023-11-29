//
// Created by Marc Nygaard on 01/11/2023.
//

#include "../api/api_functions.h"
#include "../deserializer/deserializer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function to get all items from db. REMEBER TO FREE THE MEM WITH free()
 * */

// /items
char* db_items() {
    const char *endpoint = "/items";
    return api_json(endpoint);
}

/*
 * Function to add an item to db
 * */

// /add_item
void db_add_item(const char *title, const char *expire_date, int qty, int price) {
    char numStrQty[21];
    char numStrPrice[21];

    // Convert the ints to strings
    sprintf(numStrQty, "%d", qty);
    sprintf(numStrPrice, "%d", price);

    // Calculate the total length needed for the final concatenated string
    // Plus 1 for the null terminator at the end
    int totalLength = strlen("/add_item?title=") + strlen(title) +
                      strlen("&expire_date=") + strlen(expire_date) +
                      strlen("&qty=") + strlen(numStrQty) +
                      strlen("&price=") + strlen(numStrPrice) + 1;

    // Allocate memory for the concatenated string
    char* concatenatedString = malloc(totalLength);
    if (concatenatedString == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); } // Check for error

    // Concatenated string
    sprintf(concatenatedString, "/add_item?title=%s&expire_date=%s&qty=%s&price=%s",
            title, expire_date, numStrQty, numStrPrice);

    //printf(expire_date);

    const char *endpoint = concatenatedString;

    //printf(endpoint);
    api_json(endpoint); // original api()

    // printf("%s", endpoint);

    free(concatenatedString);
}



// /get_by_id
char* db_get_by_id(const char *id) {
    int totalLength = strlen("/get_by_id?id=") + strlen(id) + 1;

    // Allocate memory for the concatenated string
    char* concatenatedString = malloc(totalLength);
    if (concatenatedString == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); } // Check for error

    // Concatenated string
    sprintf(concatenatedString, "/get_by_id?id=%s",
            id);

    const char *endpoint = concatenatedString;
    return api_json(endpoint);
}



// /get_by_title
char* db_get_by_title(const char *title) {
    int totalLength = strlen("/get_by_title?title=") + strlen(title) + 1;

    // Allocate memory for the concatenated string
    char* concatenatedString = malloc(totalLength);
    if (concatenatedString == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); } // Check for error

    // Concatenated string
    sprintf(concatenatedString, "/get_by_title?title=%s",
            title);

    const char *endpoint = concatenatedString;
    return api_json(endpoint);
}



// /delete_by_id
void db_delete_by_id(const char *id) {
    int totalLength = strlen("/delete_by_title?title=") + strlen(id) + 1;

    // Allocate memory for the concatenated string
    char* concatenatedString = malloc(totalLength);
    if (concatenatedString == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); } // Check for error

    // Concatenated string
    sprintf(concatenatedString, "/delete_by_id?id=%s",
            id);

    const char *endpoint = concatenatedString;
    api_json(endpoint);

    free(concatenatedString);
}



// /delete_by_title
void db_delete_by_title(const char *title) {
    int totalLength = strlen("/delete_by_title?title=") + strlen(title) + 1;

    // Allocate memory for the concatenated string
    char* concatenatedString = malloc(totalLength);
    if (concatenatedString == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); } // Check for error

    // Concatenated string
    sprintf(concatenatedString, "/delete_by_title?title=%s",
            title);

    const char *endpoint = concatenatedString;
    api(endpoint);

    free(concatenatedString);
}



// /update_qty
void db_update_qty(const char* id, int qty) {
    char numStrQty[21];

    // Convert the ints to strings
    sprintf(numStrQty, "%d", qty);

    // Calculate the total length needed for the final concatenated string
    // Plus 1 for the null terminator at the end
    int totalLength = strlen("/update_qty?id=") + strlen(id) +
                      strlen("&qty=") + strlen(numStrQty) + 1;

    // Allocate memory for the concatenated string
    char* concatenatedString = malloc(totalLength);
    if (concatenatedString == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); } // Check for error

    // Concatenated string
    sprintf(concatenatedString, "/update_qty?id=%s&qty=%s",
            id, numStrQty);

    const char *endpoint = concatenatedString;
    api(endpoint);

    // printf("%s", endpoint);

    free(concatenatedString);
}



// /update
void db_update(const char* id, const char *title, const char *expire_date, int qty, int price) {
    char numStrQty[21];
    char numStrPrice[21];

    // Convert the ints to strings
    sprintf(numStrQty, "%d", qty);
    sprintf(numStrPrice, "%d", price);

    // Calculate the total length needed for the final concatenated string
    // Plus 1 for the null terminator at the end
    int totalLength = strlen("/update?id=") + strlen(id) +
                      strlen("&title=") + strlen(title) +
                      strlen("&expire_date=") + strlen(expire_date) +
                      strlen("&qty=") + strlen(numStrQty) +
                      strlen("&price=") + strlen(numStrPrice) + 1;

    // Allocate memory for the concatenated string
    char* concatenatedString = malloc(totalLength);
    if (concatenatedString == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); } // Check for error

    // Concatenated string
    sprintf(concatenatedString, "/update?id=%s&title=%s&expire_date=%s&qty=%s&price=%s",
            id, title, expire_date, numStrQty, numStrPrice);

    const char *endpoint = concatenatedString;
    api(endpoint);

    // printf("%s", endpoint);

    free(concatenatedString);
}



// DB STATE
void db_reload_items() {
    api("/reload_items");
}

void db_transfer_expired_items() {
    api("/transfer_expired_items");
}

void db_update_stats() {
    api("/update_stats");
}

void db_reload() {
    // Make sure every state in the db is up-to-date
    db_reload_items();              // STEP 1
    db_transfer_expired_items();    // STEP 2
    db_update_stats();              // STEP 3
}



// /qty_of_item_by_title
int db_qty_of_item_by_title(const char *title) {
    int totalLength = strlen("/qty_of_item_by_title?title=") + strlen(title) + 1;

    // Allocate memory for the concatenated string
    char* concatenatedString = malloc(totalLength);
    if (concatenatedString == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); } // Check for error

    // Concatenated string
    sprintf(concatenatedString, "/qty_of_item_by_title?title=%s",
            title);

    const char *endpoint = concatenatedString;

    // RETURN and convert the json(string) to an integer
    return atoi(api_json(endpoint));
}



// /Stats
char* db_stats() {
    const char *endpoint = "/get_stats";
    return api_json(endpoint);
}

char* db_used_items() {
    const char *endpoint = "/get_used_items";
    return api_json(endpoint);
}



// Create Used Item
void db_add_used_item(const char *title, const char *expire_date, int qty, int price, int start_qty) {
    char numStrQty[21];
    char numStrStartQty[21];
    char numStrPrice[21];

    // Convert the ints to strings
    sprintf(numStrQty, "%d", qty);
    sprintf(numStrStartQty, "%d", start_qty);
    sprintf(numStrPrice, "%d", price);

    // Calculate the total length needed for the final concatenated string
    // Plus 1 for the null terminator at the end
    int totalLength = strlen("/create_used_item?title=") + strlen(title) +
                      strlen("&expire_date=") + strlen(expire_date) +
                      strlen("&qty=") + strlen(numStrQty) +
                      strlen("&start_qty=") + strlen(numStrStartQty) +
                      strlen("&price=") + strlen(numStrPrice) + 1;

    // Allocate memory for the concatenated string
    char* concatenatedString = malloc(totalLength);
    if (concatenatedString == NULL) { fprintf(stderr, "Failed to allocate memory.\n"); } // Check for error

    // Concatenated string
    sprintf(concatenatedString, "/create_used_item?title=%s&expire_date=%s&qty=%s&price=%s&start_qty=%s",
            title, expire_date, numStrQty, numStrPrice, numStrStartQty);

    printf(concatenatedString);

    const char *endpoint = concatenatedString;

    //printf(endpoint);
    api_json(endpoint); // original api()

    // printf("%s", endpoint);

    free(concatenatedString);
}














// /Stats
char* db_now() {
    const char *endpoint = "/get_now";
    return api_json(endpoint);
}


int now_day() {
    const char *json_string = db_now();
    // Print den "rå" data til konsollen
    printf("%s \n\n", json_string);
    // Deserializer den "rå" data, så I kan arbejde med det!
    NowArray nowArray = deserialize_now(json_string);
    // Retuner dags dag
    return nowArray.now[0].day;
}

int now_week() {
    const char *json_string = db_now();
    // Print den "rå" data til konsollen
    printf("%s \n\n", json_string);
    // Deserializer den "rå" data, så I kan arbejde med det!
    NowArray nowArray = deserialize_now(json_string);
    // Retuner dags dag
    return nowArray.now[0].week;
}

int now_month() {
    const char *json_string = db_now();
    // Print den "rå" data til konsollen
    printf("%s \n\n", json_string);
    // Deserializer den "rå" data, så I kan arbejde med det!
    NowArray nowArray = deserialize_now(json_string);
    // Retuner dags dag
    return nowArray.now[0].month;
}

int now_year() {
    const char *json_string = db_now();
    // Print den "rå" data til konsollen
    printf("%s \n\n", json_string);
    // Deserializer den "rå" data, så I kan arbejde med det!
    NowArray nowArray = deserialize_now(json_string);
    // Retuner dags dag
    return nowArray.now[0].year;
}