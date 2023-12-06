// main.c
#include <stdio.h>
#include <stdlib.h>

#include "item/item_functions.h"
#include "stats/stats.h"
#include "deserializer/deserializer.h"
#include "menu/menu.h"

char* read_json_file(const char* file_path) {
    // Open the file
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents
    char *string = malloc(file_size + 1);
    if (string == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    // Read file into string
    fread(string, 1, file_size, file);
    string[file_size] = '\0'; // Null-terminate the string

    // Close the file
    fclose(file);

    return string;
}

int main() {
    const char *json_string = read_json_file("../recipes.json");

    RecipesArray recipes = deserialize_recipes(json_string);

    for (int idx = 0; idx < recipes.count; idx++) {
        printf("id: %s\n", recipes.recipe[idx].id);
        printf("title: %s\n", recipes.recipe[idx].title);
        printf("text: %s\n", recipes.recipe[idx].text);
        printf("arr_size: %d\n", recipes.recipe[idx].arr_size);

        for (int j = 0; j < recipes.recipe[idx].arr_size; j++) {
            printf("%s : ", recipes.recipe[idx].items[j].ingredient);
            printf("%dg \n", recipes.recipe[idx].items[j].qty);
        }

        printf("\n");
    }
    printf("%s", json_string);



    //db_reload();

    //navigateterminal();
    return 0;
};