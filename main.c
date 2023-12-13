// main.c
#include "item/item_functions.h"
#include "stats/stats.h"
#include "menu/menu.h"

int main() {
    // Go through all ingredients in the database and update their 'days left' and more...
    db_reload();
    // 3. 2. 1. Start the program!
    application();
    return 0;
};