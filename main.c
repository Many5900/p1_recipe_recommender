// main.c
#include "item/item_functions.h"
#include "stats/stats.h"
#include "menu/menu.h"

int main() {
    db_reload();

    navigateterminal();
    return 0;
};