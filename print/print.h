// print.h
#ifndef PRINT_H
#define PRINT_H

#include "../deserializer/deserializer.h"

void print_ingredients(const IngredientsArray_t* ingredients_array);
void free_ingredients(IngredientsArray_t* ingredients_array);

void print_stats(const StatsArray_t* statsArray);
void free_stats(StatsArray_t* statsArray);

#endif // PRINT_H
