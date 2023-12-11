// deserializer.h
#ifndef DESERIALIZER_H
#define DESERIALIZER_H

// Items
typedef struct {
    char* expire_date;
    int days_before_expiration;
    char* id;
    char* title;
    int qty;
    int price;
    int start_qty;
} Items;

typedef struct {
    Items* items;
    int count;
} ItemArray;

ItemArray deserialize_items(const char *json_string);
//void print_items(const ItemArray* itemArray);

// Stats
typedef struct {
    char* expire_date;
    char* id;
    int price;
    int qty;
    int start_qty;
    char* title;
    int week;
    char* year;
} Stats;

typedef struct {
    Stats* stats;
    int count;
} StatsArray;

StatsArray deserialize_stats(const char *json_string);

// Used items
typedef struct {
    char* title;
    char* id;
    int price;
    int qty;
    int start_qty;
    char* expire_date;
    int week_of_year;
} UsedItems;

typedef struct {
    UsedItems* used_item;
    int count;
} UsedItemsArray;

UsedItemsArray deserialize_used_items(const char *json_string);



// Now
typedef struct {
    char* id;
    int day;
    int week;
    int month;
    int year;
} Now;

typedef struct {
    Now* now;
    int count;
} NowArray;

NowArray deserialize_now(const char *json_string);




// Recipes
// Define a structure for a recipe item
typedef struct {
    char ingredient[100];
    int qty;
} RecipeItem;

// Define a structure for a recipe
typedef struct {
    int arr_size;
    char id[100];
    RecipeItem items[20]; // Assuming maximum of 20 items per recipe
    char text[2000];
    char title[250];
} Recipe;

typedef struct {
    Recipe* recipe;
    int count;
} RecipesArray;

RecipesArray deserialize_recipes(const char *json_string);

#endif // DESERIALIZER_H
