// deserializer.h
#ifndef DESERIALIZER_H
#define DESERIALIZER_H

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
void print_items(const ItemArray* itemArray);

#endif // DESERIALIZER_H
