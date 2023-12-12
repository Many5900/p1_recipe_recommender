// print.h
#ifndef PRINT_H
#define PRINT_H

#include "../deserializer/deserializer.h"

void print_items(const ItemArray_t* itemArray);
void free_items(ItemArray_t* itemArray);

void print_stats(const StatsArray_t* statsArray);
void free_stats(StatsArray_t* statsArray);

#endif // PRINT_H
