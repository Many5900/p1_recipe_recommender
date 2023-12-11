//
// Created by Marc Nygaard on 11/12/2023.
//

#ifndef P1_RECIPE_RECOMMENDER_RECIPE_RECOMMENDER_H
#define P1_RECIPE_RECOMMENDER_RECIPE_RECOMMENDER_H

#include "../deserializer/deserializer.h"

char* read_json_file(const char* file_path);
int check_for_title_in_db(const char* title, ItemArray items_into_struct);
int expiration_value(int days_left);
double rank_item_title(const char* title, int qty_to_subtract);
int qty_of_item_by_title(const char* title);
int is_there_sufficient_qty(int people_in_household, const char* title, int recipe_item_qty);
int compareRecipeScores(const void *a, const void *b);
double calculatePercentage(double upperBound, double lowerBound, double number);
void findRecipeAndPrint(char* title, RecipesArray recipes, double percentageScore, int people_in_household, int num);
void recipeRecommender(int people_in_household);


#endif //P1_RECIPE_RECOMMENDER_RECIPE_RECOMMENDER_H
