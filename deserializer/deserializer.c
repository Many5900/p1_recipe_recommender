// Items_parser.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"
#include "deserializer.h"

ItemArray deserialize_items(const char *json_string) {
    const cJSON *json_array = cJSON_Parse(json_string);
    if (json_array == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error in JSON before: %s\n", error_ptr);
        }
        return (ItemArray){NULL, 0};
    }

    int array_size = cJSON_GetArraySize(json_array);
    Items *items = malloc(array_size * sizeof(Items));

    if (items == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for items\n");
        cJSON_Delete(json_array);
        return (ItemArray){NULL, 0};
    }

    for (int i = 0; i < array_size; i++) {
        cJSON *json_item = cJSON_GetArrayItem(json_array, i);
        cJSON *temp;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "days_before_expiration");
        items[i].days_before_expiration = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "expire_date");
        items[i].expire_date = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "id");
        items[i].id = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "title");
        items[i].title = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "qty");
        items[i].qty = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "price");
        items[i].price = temp ? temp->valueint : 0;
    }

    cJSON_Delete(json_array);
    return (ItemArray){items, array_size};
}
