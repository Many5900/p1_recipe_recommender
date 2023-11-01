cmake_minimum_required(VERSION 3.26)
project(p1_recipe_recommender C)

set(CMAKE_C_STANDARD 23)

add_executable(p1_recipe_recommender main.c
        db/api_functions.h
        db/api_functions.c
        item/item_functions.h
        item/item_functions.c)
