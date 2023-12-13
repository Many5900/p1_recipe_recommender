//
// Created by Marc Nygaard on 11/12/2023.
//

#ifndef P1_RECIPE_RECOMMENDER_RECIPE_RECOMMENDER_H
#define P1_RECIPE_RECOMMENDER_RECIPE_RECOMMENDER_H

#include "../deserializer/deserializer.h"

char* read_json_file(const char* file_path);
int is_ingredient_in_inventory(const char* search_ingredient, IngredientsArray_t all_ingredients_in_inventory);
int multiplication_factor(int days_left);
double calculate_score_for_ingredient(const char* ingredient_name, int qty_needed);
int total_qty_of_ingredient_in_inventory(const char* title);
int is_there_sufficient_qty(int people_in_household, const char* title, int recipe_item_qty);
int compare_recipe_scores(const void *a, const void *b);
double alter_score_to_range_zero_to_one_hundred(double upper_score, double lower_score, double score);
void find_recipe_and_print(char* search_recipe_title, RecipesArray_t all_recipes, double score_in_range_zero_to_one_hundred, double original_score, int people_in_household, int index);
void recipe_recommender(int people_in_household);

void db_use_ingredient(const char* title, int qty);
void use_ingredient();


#endif //P1_RECIPE_RECOMMENDER_RECIPE_RECOMMENDER_H
