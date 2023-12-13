// deserializer.h
#ifndef DESERIALIZER_H
#define DESERIALIZER_H

/****************************
***** Ingredient struct *****
****************************/
// Ingredient_t
typedef struct {
    char* expire_date;
    int days_before_expiration;
    char* id;
    char* title;
    int qty;
    int price;
    int start_qty;
} Ingredient_t;

// IngredientsArray_t
typedef struct {
    Ingredient_t* ingredients;
    int count;
} IngredientsArray_t;

// IngredientsArray_t
IngredientsArray_t deserialize_ingredients(const char *json_string);

/***********************
***** stats struct *****
***********************/
// Stats_t
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

// StatsArray_t
typedef struct {
    Stats_t* stats;
    int count;
} StatsArray_t;

// StatsArray_t
StatsArray_t deserialize_stats(const char *json_string);

/*********************************
***** used ingredient struct *****
*********************************/
// UsedIngredient_t
typedef struct {
    char* title;
    char* id;
    int price;
    int qty;
    int start_qty;
    char* expire_date;
    int week_of_year;
} UsedIngredient_t;

// UsedIngredientsArray_t
typedef struct {
    UsedIngredient_t* used_item;
    int count;
} UsedIngredientsArray_t;

// UsedIngredientsArray_t
UsedIngredientsArray_t deserialize_used_ingredients(const char *json_string);

/*********************
***** now struct *****
*********************/
// Now_t
typedef struct {
    char* id;
    int day;
    int week;
    int month;
    int year;
} Now_t;

// NowArray_t
typedef struct {
    Now_t* now;
    int count;
} NowArray_t;

// NowArray_t
NowArray_t deserialize_now(const char *json_string);

/***********************************
***** recipe ingredient struct *****
***********************************/
// RecipeItem_t
typedef struct {
    char ingredient[100];
    int qty;
} RecipeIngredient_t;

// Define a structure for a recipe
typedef struct {
    int arr_size;
    char id[100];
    RecipeIngredient_t items[20]; // Assuming maximum of 20 items per recipe
    char text[2000];
    char title[250];
} Recipe_t;

typedef struct {
    Recipe_t* recipe;
    int count;
} RecipesArray_t;

RecipesArray_t deserialize_recipes(const char *json_string);

#endif // DESERIALIZER_H
