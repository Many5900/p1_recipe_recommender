// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item/item_functions.h"
#include "stats/stats.h"
#include "deserializer/deserializer.h"
#include "menu/menu.h"
#include "menu/logic/menu_logic.h"
#include "recipe_recommender/recipe_recommender.h"





int main() {
    db_reload();
    //useIngredient("milk", 200);

    //db_add_used_item("milk", 50, 13, 1000);
    //db_use_item("milk", 50);

    navigateterminal();

    return 0;
};