//
// Created by Marc Nygaard on 01/11/2023.
//

#ifndef P1_RECIPE_RECOMMENDER_ITEM_FUNCTIONS_H
#define P1_RECIPE_RECOMMENDER_ITEM_FUNCTIONS_H
// const char *endpoint
char* items();
void add_item(const char *title, const char *expire_date, int qty, int price);
char* get_by_id(const char *id);
char* get_by_title(const char *title);
void delete_by_id(const char *id);
void delete_by_title(const char *title);
void update_qty(const char* id, int qty);
void update(const char* id, const char *title, const char *expire_date, int qty, int price);

#endif //P1_RECIPE_RECOMMENDER_ITEM_FUNCTIONS_H
