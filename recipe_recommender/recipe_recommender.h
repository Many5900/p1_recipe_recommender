//
// Created by Marc Nygaard on 11/12/2023.
//

#ifndef P1_RECIPE_RECOMMENDER_RECIPE_RECOMMENDER_H
#define P1_RECIPE_RECOMMENDER_RECIPE_RECOMMENDER_H

#include "../deserializer/deserializer.h"

char* read_json_file(const char* file_path);
int check_for_title_in_db(const char* title, IngredientsArray_t items_into_struct);
int expiration_value(int days_left);
double rank_item_title(const char* title, int qty_to_subtract);
int qty_of_item_by_title(const char* title);
int is_there_sufficient_qty(int people_in_household, const char* title, int recipe_item_qty);
int compare_recipe_scores(const void *a, const void *b);
double calculate_percentage(double upperBound, double lowerBound, double number);
void find_recipe_and_print(char* title, RecipesArray_t recipes, double percentageScore, int people_in_household, int num);
void top_8_recipes(int people_in_household);

void db_use_ingredient(const char* title, int qty);
void use_ingredient();


#endif //P1_RECIPE_RECOMMENDER_RECIPE_RECOMMENDER_H
