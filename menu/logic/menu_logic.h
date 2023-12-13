//
// Created by Marc Nygaard on 04/12/2023.
//

#ifndef P1_RECIPE_RECOMMENDER_MENU_LOGIC_H
#define P1_RECIPE_RECOMMENDER_MENU_LOGIC_H

void space();
void convert_to_lower_case(char str[]);
void add_ingredient_to_inventory(char title[], char expiration_date[], int *qty, int *price);
void delete_ingredient();

#endif //P1_RECIPE_RECOMMENDER_MENU_LOGIC_H
