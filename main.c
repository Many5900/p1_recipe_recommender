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
    navigateterminal();

    return 0;
};