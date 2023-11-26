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

#endif // DESERIALIZER_H
