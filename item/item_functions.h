//
// Created by Marc Nygaard on 01/11/2023.
//

#ifndef P1_RECIPE_RECOMMENDER_ITEM_FUNCTIONS_H
#define P1_RECIPE_RECOMMENDER_ITEM_FUNCTIONS_H
// const char *endpoint
char* db_items();
void db_add_item(const char *title, const char *expire_date, int qty, int price);
char* db_get_by_id(const char *id);
char* db_get_by_title(const char *title);
void db_delete_by_id(const char *id);
void db_delete_by_title(const char *title);
void db_update_qty(const char* id, int qty);
void db_update(const char* id, const char *title, const char *expire_date, int qty, int price);
void db_reload_items();
void db_transfer_expired_items();
void db_update_stats();
void db_reload();
int db_qty_of_item_by_title(const char *title);
#endif //P1_RECIPE_RECOMMENDER_ITEM_FUNCTIONS_H
