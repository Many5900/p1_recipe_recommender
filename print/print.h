// print.h
#ifndef PRINT_H
#define PRINT_H

#include "../deserializer/deserializer.h"

void print_items(const ItemArray* itemArray);
void free_items(ItemArray* itemArray);

void print_stats(const StatsArray* statsArray);
void free_stats(StatsArray* statsArray);

#endif // PRINT_H
