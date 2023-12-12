// Items_parser.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"
#include "deserializer.h"

ItemArray_t deserialize_items(const char *json_string) {
    const cJSON *json_array = cJSON_Parse(json_string);
    if (json_array == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error in JSON before: %s\n", error_ptr);
        }
        return (ItemArray_t){NULL, 0};
    }

    int array_size = cJSON_GetArraySize(json_array);
    Items_t *items = malloc(array_size * sizeof(Items_t));

    if (items == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for items\n");
        cJSON_Delete(json_array);
        return (ItemArray_t){NULL, 0};
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

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "start_qty");
        items[i].start_qty = temp ? temp->valueint : 0;
    }

    cJSON_Delete(json_array);
    return (ItemArray_t){items, array_size};
}



StatsArray_t deserialize_stats(const char *json_string) {
    const cJSON *json_array = cJSON_Parse(json_string);
    if (json_array == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error in JSON before: %s\n", error_ptr);
        }
        return (StatsArray_t){NULL, 0};
    }

    int array_size = cJSON_GetArraySize(json_array);
    Stats_t *items = malloc(array_size * sizeof(Stats_t));

    if (items == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for items\n");
        cJSON_Delete(json_array);
        return (StatsArray_t){NULL, 0};
    }

    for (int i = 0; i < array_size; i++) {
        cJSON *json_item = cJSON_GetArrayItem(json_array, i);
        cJSON *temp;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "expire_date");
        items[i].expire_date = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "id");
        items[i].id = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "price");
        items[i].price = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "qty");
        items[i].qty = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "start_qty");
        items[i].start_qty = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "title");
        items[i].title = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "week");
        items[i].week = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "year");
        items[i].year = temp ? strdup(temp->valuestring) : NULL;
    }

    cJSON_Delete(json_array);
    return (StatsArray_t){items, array_size};
}





UsedItemsArray_t deserialize_used_items(const char *json_string) {
    const cJSON *json_array = cJSON_Parse(json_string);
    if (json_array == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error in JSON before: %s\n", error_ptr);
        }
        return (UsedItemsArray_t){NULL, 0};
    }

    int array_size = cJSON_GetArraySize(json_array);
    UsedItems_t *items = malloc(array_size * sizeof(UsedItems_t));

    if (items == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for items\n");
        cJSON_Delete(json_array);
        return (UsedItemsArray_t){NULL, 0};
    }

    for (int i = 0; i < array_size; i++) {
        cJSON *json_item = cJSON_GetArrayItem(json_array, i);
        cJSON *temp;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "title");
        items[i].title = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "expire_date");
        items[i].expire_date = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "id");
        items[i].id = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "price");
        items[i].price = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "qty");
        items[i].qty = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "start_qty");
        items[i].start_qty = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "week_of_year");
        items[i].week_of_year = temp ? temp->valueint : 0;
    }

    cJSON_Delete(json_array);
    return (UsedItemsArray_t){items, array_size};
}






NowArray_t deserialize_now(const char *json_string) {
    const cJSON *json_array = cJSON_Parse(json_string);
    if (json_array == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error in JSON before: %s\n", error_ptr);
        }
        return (NowArray_t){NULL, 0};
    }

    int array_size = cJSON_GetArraySize(json_array);
    Now_t *items = malloc(array_size * sizeof(Now_t));

    if (items == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for items\n");
        cJSON_Delete(json_array);
        return (NowArray_t){NULL, 0};
    }

    for (int i = 0; i < array_size; i++) {
        cJSON *json_item = cJSON_GetArrayItem(json_array, i);
        cJSON *temp;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "id");
        items[i].id = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "day");
        items[i].day = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "week");
        items[i].week = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "month");
        items[i].month = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "year");
        items[i].year = temp ? temp->valueint : 0;
    }

    cJSON_Delete(json_array);
    return (NowArray_t){items, array_size};
}







RecipesArray_t deserialize_recipes(const char *json_string) {
    const cJSON *json = cJSON_Parse(json_string);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return (RecipesArray_t){NULL, 0};
    }

    int recipe_count = cJSON_GetArraySize(json);
    Recipe_t *recipes = malloc(recipe_count * sizeof(Recipe_t));
    if (recipes == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for recipes\n");
        cJSON_Delete(json);
        return (RecipesArray_t){NULL, 0};
    }

    for (int i = 0; i < recipe_count; i++) {
        cJSON *json_recipe = cJSON_GetArrayItem(json, i);
        cJSON *temp;

        temp = cJSON_GetObjectItemCaseSensitive(json_recipe, "id");
        if (temp) strncpy(recipes[i].id, temp->valuestring, sizeof(recipes[i].id));

        temp = cJSON_GetObjectItemCaseSensitive(json_recipe, "text");
        if (temp) strncpy(recipes[i].text, temp->valuestring, sizeof(recipes[i].text));

        temp = cJSON_GetObjectItemCaseSensitive(json_recipe, "title");
        if (temp) strncpy(recipes[i].title, temp->valuestring, sizeof(recipes[i].title));

        temp = cJSON_GetObjectItemCaseSensitive(json_recipe, "arr_size");
        if (temp) recipes[i].arr_size = temp->valueint;

        cJSON *json_items = cJSON_GetObjectItemCaseSensitive(json_recipe, "items");
        int item_count = cJSON_GetArraySize(json_items);
        for (int j = 0; j < item_count; j++) {
            cJSON *json_item = cJSON_GetArrayItem(json_items, j);
            cJSON *json_item_name = cJSON_GetObjectItemCaseSensitive(json_item, "item");
            cJSON *json_item_qty = cJSON_GetObjectItemCaseSensitive(json_item, "qty");

            if (json_item_name) strncpy(recipes[i].items[j].ingredient, json_item_name->valuestring, sizeof(recipes[i].items[j].ingredient));
            if (json_item_qty) recipes[i].items[j].qty = json_item_qty->valueint;
        }
    }

    cJSON_Delete(json);
    return (RecipesArray_t){recipes, recipe_count};
}