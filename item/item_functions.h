//
// Created by Marc Nygaard on 01/11/2023.
//

#ifndef P1_RECIPE_RECOMMENDER_ITEM_FUNCTIONS_H
#define P1_RECIPE_RECOMMENDER_ITEM_FUNCTIONS_H

char* db_ingredients();
void db_add_item(const char *title, const char *expire_date, int qty, int price);
char* db_get_by_id(const char *id);
char* db_get_ingredient_by_name(const char *ingredient_name);
void db_delete_by_id(const char *id);
void db_delete_by_title(const char *title);
void db_update_qty(const char* id, int qty);
void db_update(const char* id, const char *title, const char *expire_date, int qty, int price);
void db_reload_items();
void db_transfer_expired_items();
void db_update_stats();
void db_reload();
int db_qty_of_item_by_title(const char *title);
char* db_stats();
char* db_used_ingredients();
void db_add_used_item(const char *title, int qty, int price, int start_qty);

void db_use_item(const char* title, int qty);




void db_use_ingredient(const char* title, int qty);


int now_day();
int now_week();
int now_month();
int now_year();

char* db_recipes();
#endif //P1_RECIPE_RECOMMENDER_ITEM_FUNCTIONS_H
