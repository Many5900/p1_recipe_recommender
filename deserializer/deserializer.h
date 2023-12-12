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
} Items_t;

typedef struct {
    Items_t* items;
    int count;
} ItemArray_t;

ItemArray_t deserialize_items(const char *json_string);
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
} Stats_t;

typedef struct {
    Stats_t* stats;
    int count;
} StatsArray_t;

StatsArray_t deserialize_stats(const char *json_string);

// Used items
typedef struct {
    char* title;
    char* id;
    int price;
    int qty;
    int start_qty;
    char* expire_date;
    int week_of_year;
} UsedItems_t;

typedef struct {
    UsedItems_t* used_item;
    int count;
} UsedItemsArray_t;

UsedItemsArray_t deserialize_used_items(const char *json_string);



// Now
typedef struct {
    char* id;
    int day;
    int week;
    int month;
    int year;
} Now_t;

typedef struct {
    Now_t* now;
    int count;
} NowArray_t;

NowArray_t deserialize_now(const char *json_string);




// Recipes
// Define a structure for a recipe item
typedef struct {
    char ingredient[100];
    int qty;
} RecipeItem_t;

// Define a structure for a recipe
typedef struct {
    int arr_size;
    char id[100];
    RecipeItem_t items[20]; // Assuming maximum of 20 items per recipe
    char text[2000];
    char title[250];
} Recipe_t;

typedef struct {
    Recipe_t* recipe;
    int count;
} RecipesArray_t;

RecipesArray_t deserialize_recipes(const char *json_string);

#endif // DESERIALIZER_H
