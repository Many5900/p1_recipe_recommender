// deserializer.h
#ifndef DESERIALIZER_H
#define DESERIALIZER_H

typedef struct {
    char* expire_date;
    char* id;
    char* title;
    int qty;
    int price;
} Product;

Product* parse_products(const char *json_string);

#endif // DESERIALIZER_H
