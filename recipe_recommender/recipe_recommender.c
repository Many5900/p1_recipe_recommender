//
// Created by Marc Nygaard on 11/12/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../item/item_functions.h"
#include "../stats/stats.h"

/*************************
***** Read JSON file *****
*************************/
/* DESCRIPTION:
 * Function that opens a local JSON file at the given path, and converts it into a string
 */
char* read_json_file(const char* file_path) {
    // Open the file
    FILE *file = fopen(file_path, "r"); // Opens the JSON file at the given path
    if (file == NULL) { // Error handling to make sure that the file exists/could be located
        perror("Error opening file");
        return NULL;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents
    char *string = malloc(file_size + 1);
    if (string == NULL) { // Error handling to make sure that the memory could be allocated
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

/*************************************
***** is_ingredient_in_inventory *****
*************************************/
/* DESCRIPTION:
 * Check if an ingredient is available / present in the inventory
 */
int is_ingredient_in_inventory(const char* search_ingredient, IngredientsArray_t all_ingredients_in_inventory) {
    /*
     * Two strings can't be directly compared in C,
     * so to compare two strings the function, strcmp (String Compare) can be used
     */
    for (int idx = 0; idx < all_ingredients_in_inventory.count; idx++) { // Iterate over all ingredients in inventory
        const char* ingredients = all_ingredients_in_inventory.ingredients[idx].title; // Extract the ingredient at the current index

        // Check if the ingredient at the current index is the ingredients that we are searching for
        if (strcmp(ingredients, search_ingredient) == 0) {
            return 1; // Return 1 (true) --- The ingredient is present in the inventory
        }
    }

    return 0; // Return 0 (false) --- The ingredient is NOT present in the inventory
}

/********************************
***** multiplication_factor *****
********************************/
/* DESCRIPTION:
 * Get the factor that an ingredient should be multiplied with based on amount of days left the ingredient has before expiring
 */
int multiplication_factor(int days_left_before_expiring) {
    switch (days_left_before_expiring) {
        case 0: // 0 days left
            return 100000000; // 100.000.000 as the factor
        case 1: // 1 day left
            return 1000000; // 1.000.000 as the factor
        case 2: // 2 days left
            return 10000; // 10.000 as the factor
        case 3: // 3 days left
            return 100; // 100 as the factor
        default: // Default return value
            return 1;
    }
}

/*****************************************
***** calculate_score_for_ingredient *****
*****************************************/
/* DESCRIPTION:
 * Give the ingredient a score based on the price of the ingredient & how many days there is left before the ingredient expires
 *
 * NOTE!
 * It is assumed that before this function runs,
 * that there is a sufficient quantity of the given ingredient in the inventory!
 */
double calculate_score_for_ingredient(const char* ingredient_name, int qty_needed_for_recipe) {
    int qty_left = qty_needed_for_recipe;
    double total_score = 0.0;

    // Fetch all ingrediets with the same "ingredient name" and deserailize it into IngredientsArray_t
    const char* all_ingredients_of_same_name_json = db_get_ingredient_by_name(ingredient_name);
    IngredientsArray_t all_ingredients_of_same_name = deserialize_ingredients(all_ingredients_of_same_name_json);

    // Iterate over all ingredients of the same name one by one
    for (int idx = 0; idx < all_ingredients_of_same_name.count; idx++) {
        // Get the quantity for the ingredient at the current index
        int ingredient_qty = all_ingredients_of_same_name.ingredients[idx].qty;

        // Get the cost / price for the ingredient at the current index
        int ingredient_price = all_ingredients_of_same_name.ingredients[idx].price;

        // Get the amount of days that is left, before the ingredient expires at the current index
        int days_left_before_expiring = all_ingredients_of_same_name.ingredients[idx].days_before_expiration;

        // Get the multiplication factor based on how many days there is left before the ingredient expires (at the current index)
        double factor = multiplication_factor(days_left_before_expiring);



        // If the qty_left is zero, meaning the score for the ingredent is complete, then return the total_score
        if (qty_left == 0) {
            return (double)total_score;
        }

        // If the ingredient quantity needed(qty_left) is greater than ingredient_qty then
        if (qty_left > ingredient_qty) {
            // Calculate the score
            double score = ingredient_price * factor;

            // Add the score to the total score
            total_score += score;

            // Subtract the ingredient quantity from the quantity that is still needed (qty_left) in order to make a complete score
            qty_left -= ingredient_qty;

        } else { // The quantity needed(qty_left) is less than the quantity of the current ingredient, so now we only need a fraction of the ingredient price
            // Get the fraction that is stil needed of the current ingredient
            double qty_fraction_of_ingredient_needed = (double)qty_left / ingredient_qty;

            // Calculate the score
            double score = qty_fraction_of_ingredient_needed * ingredient_price * factor;

            // Add the score to the total score
            total_score += score;

            qty_left = 0; // The quantity needed has been satisfied so set qty_left to zero in order to return the total score for the ingredient
        }
    }

    return (double)total_score; // Return the score for the given ingredient
};

/***********************************************
***** total_qty_of_ingredient_in_inventory *****
***********************************************/
/* DESCRIPTION:
 * Get the total quantity of an ingredient in the inventory
 */
int total_qty_of_ingredient_in_inventory(const char* ingredient_name) {
    // Initialize the total quantity to zero
    int total_qty = 0;

    // Fetch all ingrediets with the same "ingredient name" and deserailize it into IngredientsArray_t
    const char* all_ingredients_of_same_name_json = db_get_ingredient_by_name(ingredient_name);
    IngredientsArray_t all_ingredients_of_same_name = deserialize_ingredients(all_ingredients_of_same_name_json);

    // Iterate over all ingredients of the same name and add up their quantity
    for (int idx = 0; idx < all_ingredients_of_same_name.count; idx++) {
        total_qty += all_ingredients_of_same_name.ingredients[idx].qty; // Add the quantity of the ingredient (at the current index) to the total_qty
    }

    return total_qty; // Return the total quantity
}

/************************************************
***** is_there_sufficient_qty_of_ingredient *****
************************************************/
/* DESCRIPTION:
 * Checks for a sufficient quantity of the given ingredient in the inventory (in order to satisfy the quantity need in a given recipe)
 */
int is_there_sufficient_qty_of_ingredient(int people_in_household, const char* ingredient_name, int recipe_ingredient_qty_needed) {
    // Get the total avaiable quantity of the ingredient in the inventory
    int total_qty = total_qty_of_ingredient_in_inventory(ingredient_name);

    // Get the quantity that is needed in order to make the recipe
    int sufficient_qty = people_in_household * recipe_ingredient_qty_needed;

    // Check if the quantity needed in order to make the recipe is less than or equal to the total quantity of the ingredient that is available in the inventory
    if (sufficient_qty <= total_qty) {
        return 1; // Return 1 (true) --- There is a sufficient quantity
    }

    return 0; // Return 0 (false) --- There is NOT a sufficient quantity
};

/**********************
***** RecipeScore *****
**********************/
/* DESCRIPTION:
 * RecipeScore struct that has two fields, one that stores the title of the recipe, and another that stores the score for the recipe
 */
typedef struct {
    char recipe_title[200];
    double recipe_score;
} RecipeScore;

/********************************
***** compare_recipe_scores *****
********************************/
/* DESCRIPTION:
 * comparison function needed in order for qsort to know how to sort the recipe RecipeScore
 *
 * NOTE:
 * Sorts so that the highest score is at the start and the lowest score at the end (Descending order)
 */
int compare_recipe_scores(const void *a, const void *b) {
    const RecipeScore *recipeA = (const RecipeScore *)a;
    const RecipeScore *recipeB = (const RecipeScore *)b;

    // For descending order, compare B with A
    if (recipeB->recipe_score > recipeA->recipe_score) return 1;
    if (recipeB->recipe_score < recipeA->recipe_score) return -1;
    return 0;
}

/***************************************************
***** alter_score_to_range_zero_to_one_hundred *****
***************************************************/
/* DESCRIPTION:
 * Converts the "original score" to a more convenient score (0 - 100) that is easier to grasp
 */
double alter_score_to_range_zero_to_one_hundred(double upper_score, double lower_score, double score) {
    // Error handling - check if the given score is out of bound
    if (score < lower_score || score > upper_score) {
        printf("Number is out of bounds.\n");
        return -1; // Indicating an error
    }

    // Return the new score that is on a range from 0 to 100 - (lower_score to upper_score)
    return (score - lower_score) / (upper_score - lower_score) * 100;
}

/********************************
***** find_recipe_and_print *****
********************************/
/* DESCRIPTION:
 * Given an array of recipes, the function finds the recipe with the given search_title in the database and prints it
 */
void find_recipe_and_print(char* recipe_to_be_printed, RecipesArray_t all_recipes, double score_in_range_zero_to_one_hundred, double original_score, int people_in_household, int index) {
    // Iterate over all recipes in the database
    for (int idx = 0; idx < all_recipes.count; idx++) {

        // Check if the recipe at the current index is the one that should be printed
        if (strcmp(all_recipes.recipe[idx].title, recipe_to_be_printed) == 0) {
            // Print the recipe
            printf("\n\n\nRecipe nr. %d. --- score: %.2lf", index, score_in_range_zero_to_one_hundred);
            printf(" ( Original score: %.2lf ) ", original_score);

            printf("\nTitle: %s ", all_recipes.recipe[idx].title);
            printf("\nHow to:\n\t%s", all_recipes.recipe[idx].text);

            printf("\nIngredients needed:\n");
            // Iterate over the ingredients in the recipe and print them one by one
            for (int j = 0; j < all_recipes.recipe[idx].arr_size; j++) {
                // Initialize an empty string
                char temp[6] = "";

                // Check if there is a sufficient quantity of the ingredient within the inventory
                int is_sufficient = is_there_sufficient_qty_of_ingredient(people_in_household, all_recipes.recipe[idx].items[j].ingredient, all_recipes.recipe[idx].items[j].qty);

                if (is_sufficient) {
                    strcpy(temp, "[✓]"); // Print [✓] infront of the ingredient if there is a sufficient quantity
                } else {
                    strcpy(temp, "[✗]"); // Print [✗] infront of the ingredient if there is NOT a sufficient quantity
                }

                // Print the ingredient
                printf("\t%s %s - %dg\n", temp, all_recipes.recipe[idx].items[j].ingredient, all_recipes.recipe[idx].items[j].qty * people_in_household);
            }
        }
    }
}

/*************************
***** use_ingredient *****
*************************/
/* DESCRIPTION:
 * Function that prompts the user what ingredient they wish to use, and the quantity they wish to use
 */
void use_ingredient() {
    char ingredient_name[100]; // Char array to store the ingredient name
    char quantityStr[10]; // Char array to store the quantity as a string
    int quantity;         // Variable to store the converted quantity

    while (1) { // Infinite loop
        // Ask the user for the ingredient
        printf("\nEnter the ingredient you wish to use: ");

        // Get the ingredient that the user typed
        scanf("%99s", ingredient_name); // Read up to 99 characters to avoid buffer overflow

        // Ask the user for the quantity
        printf("Enter the quantity: ");

        // Get the quanity that the user typed
        scanf("%9s", quantityStr); // Read up to 9 characters

        // Convert the quantity string to an integer
        quantity = atoi(quantityStr);

        // Error handeling - a quantity of zeor is not a valid quanityt
        if (quantity < 1) {
            printf("\nThat is not a valid quantity... Try again...\n");

            continue; // Continue at the top of the loop, so that the user can try again
        }

        // Check if the quantity that the user wishes to use is available in the inventory
        if (is_there_sufficient_qty_of_ingredient(1, ingredient_name, quantity)) {
            // Prompte the user that the quantity that hey wish to use has been used
            printf("\n%dg of %s has been used...\n", quantity, ingredient_name);

            // Use the ingredient withing the database
            db_use_ingredient(ingredient_name, quantity);

            break; // The ingredient has been used, break out of the infinite loop
        } else { // Error handling - The quantity that the user wanted to use is not present within the inventory
            printf("\nNot enough %s in your inventory... Try again...\n", ingredient_name);

            continue; // Continue at the top of the loop, so that the user can try again
        }
    }
}

/*****************************
***** recipe_recommender *****
*****************************/
/* DESCRIPTION:
 * Get the 8 best recipes that should be recommended to the user
 */
void recipe_recommender(int people_in_household) {
    // Fetch all recipes and deseralize it into RecipesArray_t
    const char* recipes_json = read_json_file("../recipes.json");
    RecipesArray_t all_recipes = deserialize_recipes(recipes_json);

    // Fetch all ingredients from the inventory and deserialize it into IngredientsArray_t
    const char* ingredients = db_ingredients();
    IngredientsArray_t all_ingredients_in_inventory = deserialize_ingredients(ingredients);

    // Get the number of recipes
    int number_of_recipes = all_recipes.count;

    // Initialize a new variale
    RecipeScore *recipes_with_score; // deklere en ny array af datatypen RecipeScore

    // Allocate memory for n RecipeScore structs
    recipes_with_score = (RecipeScore *)malloc(number_of_recipes * sizeof(RecipeScore)); // Allocate memory

    // Initialize an empty string
    char empty_string[200];

    // Initialize an empty instance of the struct RecipeScore
    RecipeScore empty_recipe;
    empty_recipe.recipe_score = 0;
    strcpy(empty_recipe.recipe_title, empty_string);

    // Copy n amount of empty RecipeScore structs into recipes_with_score
    for (int n = 0; n < number_of_recipes; n++) {
        strcpy(recipes_with_score[n].recipe_title, empty_recipe.recipe_title);
        recipes_with_score[n].recipe_score = empty_recipe.recipe_score;
    }

    // Iterate over all recipes one by one
    for (int idx = 0; idx < all_recipes.count; idx++) {
        // Initialize a variable for total score for the current recipe at the current index
        double total_score_for_recipe = 0.0;

        // Go into the ingredient list withing the recipe and iterate over them one by one
        for (int jdx = 0; jdx < all_recipes.recipe[idx].arr_size; jdx++) {
            // Get the ingredient_name
            const char* ingredient_name = all_recipes.recipe[idx].items[jdx].ingredient;

            // Check if the infredient_name is in the inventory
            if (is_ingredient_in_inventory(ingredient_name, all_ingredients_in_inventory)) {
                // Quantity need of the given ingredient in order to make the recipe
                int qty_needed_for_recipe = all_recipes.recipe[idx].items[jdx].qty * people_in_household;

                // Check if there is a sufficient quantity of the given ingredient in order to make the recipe
                if (is_there_sufficient_qty_of_ingredient(people_in_household, ingredient_name, qty_needed_for_recipe)) {
                    // Calcualte the score for the given ingredient
                    double ingredient_score = calculate_score_for_ingredient(ingredient_name, qty_needed_for_recipe);

                    // Add the score to the total score for recipe
                    total_score_for_recipe += ingredient_score;
                }
            }
        }

        // Copy the new recipe title and score into recipes_with_score
        strcpy(recipes_with_score[idx].recipe_title, all_recipes.recipe[idx].title);
        recipes_with_score[idx].recipe_score = total_score_for_recipe;
    }

    // Sort recipes_with_score using qsort
    qsort(recipes_with_score, number_of_recipes, sizeof(RecipeScore), compare_recipe_scores);

    // Initialize a new empty RecipeScore array for the top 8 recipes
    RecipeScore top_8_recipes[8];

    // Copying the first 8 elements of recipes_with_score into top_8_recipes
    memcpy(top_8_recipes, recipes_with_score, 8 * sizeof(RecipeScore));

    // Iterate over top 8 recipes
    for(int idx = 0; idx < 8; idx++) {
        // Get the upper and lower score for the top 8 recipes
        double recipe_number_one = top_8_recipes[0].recipe_score;
        double recipe_number_eight = top_8_recipes[7].recipe_score;

        // Get the new score between 0 and 100
        double score_in_range_zero_to_one_hundred = alter_score_to_range_zero_to_one_hundred(recipe_number_one, recipe_number_eight, top_8_recipes[idx].recipe_score);

        // Print the recipe one by one
        find_recipe_and_print(top_8_recipes[idx].recipe_title, all_recipes, score_in_range_zero_to_one_hundred, top_8_recipes[idx].recipe_score, people_in_household, idx + 1);
    }
}