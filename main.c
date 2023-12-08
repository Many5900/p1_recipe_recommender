// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item/item_functions.h"
#include "stats/stats.h"
#include "deserializer/deserializer.h"
#include "menu/menu.h"
#include "menu/logic/menu_logic.h"

char* read_json_file(const char* file_path) {
    // Open the file
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents
    char *string = malloc(file_size + 1);
    if (string == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    // Read file into string
    fread(string, 1, file_size, file);
    string[file_size] = '\0'; // Null-terminate the string

    // Close the file
    fclose(file);

    return string;
}


int check_for_title_in_db(const char* title, ItemArray items_into_struct) {


    /* strcmp() bruges til at sammenligne to strings,
     * da man ikke direkte kan semmenligne dem på følgende måde
     * string == string
     */
    for (int idx = 0; idx < items_into_struct.count; idx++) {
        const char* item_title = items_into_struct.items[idx].title;

        if (strcmp(item_title, title) == 0) {
            return 1;
        }
    }
    return 0;
}




int expiration_value(int days_left) {
    switch (days_left) {
        case 0: // 0 dage - Sille ;D
            return 100000000;
        case 1: // 1 dag - Sille ;D
            return 1000000;
        case 2: // 2 dage - Sille ;D
            return 10000;
        case 3: // 3 dage - Sille ;D
            return 100;
        default: // Default - Sille ;D
            return 1;
    }
}







double rank_item_title(const char* title, int qty_to_subtract) {
    int qty_left = qty_to_subtract;
    double total_rank = 0.0;

    // Henter alle ingridienter med bestemt title/navn
    const char* items = db_get_by_title(title);
    ItemArray items_by_title_into_struct = deserialize_items(items);

    // looper igennem alle items af samme titel
    for (int idx = 0; idx < items_by_title_into_struct.count; idx++) {
        int qty_for_item = items_by_title_into_struct.items[idx].qty;
        if (qty_left == 0) {
            return total_rank;
        }

        if (qty_left > qty_for_item) {
            // gange op med dage tilbage (værdi)
            int days_left = items_by_title_into_struct.items[idx].days_before_expiration;
            double value = expiration_value(days_left);

            total_rank = total_rank + (items_by_title_into_struct.items[idx].price * value);
            qty_left = qty_left - items_by_title_into_struct.items[idx].qty;
        } else {
            // gange op med dage tilbage (værdi)
            int days_left = items_by_title_into_struct.items[idx].days_before_expiration;
            double value = expiration_value(days_left);

            double rank = (((double)items_by_title_into_struct.items[idx].price / items_by_title_into_struct.items[idx].qty) * qty_left) * value;
            total_rank = total_rank + rank;
            qty_left = 0;
        }
    }

    return total_rank;
};




int qty_of_item_by_title(const char* title) {
    int total_qty = 0;

    // summere mænger af alle items af samme titel
    // Henter alle items og laver dem om til item struckts
    const char* items = db_get_by_title(title);
    ItemArray items_by_title_into_struct = deserialize_items(items);

    for (int idx = 0; idx < items_by_title_into_struct.count; idx++) {
        total_qty = total_qty + items_by_title_into_struct.items[idx].qty;
    }

    return total_qty;
}






int is_there_sufficient_qty(int people_in_household, const char* title, int recipe_item_qty) {
    int total_qty = qty_of_item_by_title(title);
    int sufficient_qty = people_in_household * recipe_item_qty;

    if (sufficient_qty <= total_qty) {
        return 1;
    }

    return 0;
};







// Define a structure for a recipe
typedef struct {
    int arr_size;  // Number of items in the recipe
    char id[100];
    RecipeItem items[20]; // Assuming a maximum of 20 items per recipe
    char text[2000];
    char title[250];
} RecipeNew;


RecipeNew add_recipe_score_to_final_recipe_score(int arr_size, char* id, char* title, char* text, RecipeItem recipeItem) {
    RecipeNew recipe;
    strcpy(recipe.id, id);
    strcpy(recipe.title, title);
    strcpy(recipe.text, text);
    recipe.arr_size = arr_size;  // Assuming adding only one item for now

    for (int idx = 0, )
    recipe.items[0] = recipeItem;  // Copy the item into the first position of the array

    return recipe;
}














int main() {
    /*
    const char *json_string = read_json_file("../recipes.json");

    RecipesArray recipes = deserialize_recipes(json_string);

    for (int idx = 0; idx < recipes.count; idx++) {
        printf("id: %s\n", recipes.recipe[idx].id);
        printf("title: %s\n", recipes.recipe[idx].title);
        printf("text: %s\n", recipes.recipe[idx].text);
        printf("arr_size: %d\n", recipes.recipe[idx].arr_size);

        for (int j = 0; j < recipes.recipe[idx].arr_size; j++) {
            printf("%s : ", recipes.recipe[idx].items[j].ingredient);
            printf("%dg \n", recipes.recipe[idx].items[j].qty);
        }

        printf("\n");
    }



    printf("%s", json_string);

*/












    //db_reload();

    //navigateterminal();

    // Henter alle recipes og laver dem om til recipe structs
    const char* recipes_json = read_json_file("../recipes.json");
    RecipesArray recipes_into_struct = deserialize_recipes(recipes_json);

    // Henter alle items og laver dem om til item struckts
    const char* items = db_items();
    ItemArray items_into_struct = deserialize_items(items);





    Recipes finalRecipeScore[sizeof(Recipes) * recipes_into_struct.count + 100];







    for (int idx = 0; idx < recipes_into_struct.count; idx++) { // looper igennem opskrifterne
        double total_score_for_recipe = 0.0;

        for (int jdx = 0; jdx < recipes_into_struct.recipe[idx].arr_size; jdx++) { // looper igennem ingredienserne i opskriften jdx = item_in_recipe
            printf("%s\n", recipes_into_struct.recipe[idx].items[jdx].ingredient); //

            const char* ingredient = recipes_into_struct.recipe[idx].items[jdx].ingredient;

            // Check om den givende ingrediens(item) er i databasens inventory

            int people_in_household = 1;

            // Først tjekke om der er en "item" i inventory med den givende titel
            if (check_for_title_in_db(ingredient, items_into_struct)) {
                // Så tjekker vi om qty i inventory er mere eller lig med mængde der skal bruge til opskriften
                if (is_there_sufficient_qty(people_in_household, ingredient, recipes_into_struct.recipe[idx].items[jdx].qty)) {


                    // Dette er mængden der skal bruges for at kunne lave den givende opskrift.
                    int qty_needed_for_recipe = recipes_into_struct.recipe[idx].items[jdx].qty * people_in_household;


                    double item_score = rank_item_title(ingredient, qty_needed_for_recipe);
                    total_score_for_recipe = total_score_for_recipe + item_score;


                    printf("%lf\n", item_score);

                    // Her udregnes score for hver item og derefter summer af alle items
                    //double score_for_item = rank_item_title(ingredient, people_in_household * qty_needed_for_recipe);
                    //total_score_for_items = total_score_for_items + score_for_item;
                }

                // calculate_ingredient_score();
            };

        }
        printf("%lf \n", total_score_for_recipe);
    }
    printf("%s", recipes_json);

    //space();
    return 0;
};