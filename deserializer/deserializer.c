// Items_parser.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"
#include "deserializer.h"

/**********************************
***** deserialize_ingredients *****
**********************************/
/* DESCRIPTION:
 * Function to deserailize ingredients from JSON into structs of type IngredientsArray_t
 */
IngredientsArray_t deserialize_ingredients(const char *json_string) {
    const cJSON *json_array = cJSON_Parse(json_string);
    if (json_array == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error in JSON before: %s\n", error_ptr);
        }
        return (IngredientsArray_t){NULL, 0};
    }

    int array_size = cJSON_GetArraySize(json_array);
    Ingredient_t *ingredient = malloc(array_size * sizeof(Ingredient_t));

    if (ingredient == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for items\n");
        cJSON_Delete(json_array);
        return (IngredientsArray_t){NULL, 0};
    }

    for (int i = 0; i < array_size; i++) {
        cJSON *json_item = cJSON_GetArrayItem(json_array, i);
        cJSON *temp;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "days_before_expiration");
        ingredient[i].days_before_expiration = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "expire_date");
        ingredient[i].expire_date = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "id");
        ingredient[i].id = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "title");
        ingredient[i].title = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "qty");
        ingredient[i].qty = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "price");
        ingredient[i].price = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "start_qty");
        ingredient[i].start_qty = temp ? temp->valueint : 0;
    }

    cJSON_Delete(json_array);
    return (IngredientsArray_t){ingredient, array_size};
}

/****************************
***** deserialize_stats *****
****************************/
/* DESCRIPTION:
 * Function to deserailize stats from JSON into structs of type StatsArray_t
 */
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

/***************************************
***** deserialize_used_ingredients *****
***************************************/
/* DESCRIPTION:
 * Function to deserailize used ingredients from JSON into structs of type UsedIngredientsArray_t
 */
UsedIngredientsArray_t deserialize_used_ingredients(const char *json_string) {
    const cJSON *json_array = cJSON_Parse(json_string);
    if (json_array == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error in JSON before: %s\n", error_ptr);
        }
        return (UsedIngredientsArray_t){NULL, 0};
    }

    int array_size = cJSON_GetArraySize(json_array);
    UsedIngredient_t *used_ingredient = malloc(array_size * sizeof(UsedIngredient_t));

    if (used_ingredient == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for items\n");
        cJSON_Delete(json_array);
        return (UsedIngredientsArray_t){NULL, 0};
    }

    for (int i = 0; i < array_size; i++) {
        cJSON *json_item = cJSON_GetArrayItem(json_array, i);
        cJSON *temp;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "title");
        used_ingredient[i].title = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "expire_date");
        used_ingredient[i].expire_date = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "id");
        used_ingredient[i].id = temp ? strdup(temp->valuestring) : NULL;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "price");
        used_ingredient[i].price = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "qty");
        used_ingredient[i].qty = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "start_qty");
        used_ingredient[i].start_qty = temp ? temp->valueint : 0;

        temp = cJSON_GetObjectItemCaseSensitive(json_item, "week_of_year");
        used_ingredient[i].week_of_year = temp ? temp->valueint : 0;
    }

    cJSON_Delete(json_array);
    return (UsedIngredientsArray_t){used_ingredient, array_size};
}

/**************************
***** deserialize_now *****
**************************/
/* DESCRIPTION:
 * Function to deserailize "now" from JSON into structs of type NowArray_t
 */
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

/******************************
***** deserialize_recipes *****
******************************/
/* DESCRIPTION:
 * Function to deserailize recipes from JSON into structs of type RecipesArray_t
 */
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