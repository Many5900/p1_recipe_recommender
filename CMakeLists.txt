cmake_minimum_required(VERSION 3.26)
project(p1_recipe_recommender C)

set(CMAKE_C_STANDARD 23)

# Add subdirectories for cJSON and curl
add_subdirectory(curl)
add_subdirectory(cJSON)

# Add executable
add_executable(p1_recipe_recommender main.c
        db/api_functions.h
        db/api_functions.c
        item/item_functions.h
        item/item_functions.c
        deserializer/deserializer.h
        deserializer/deserializer.c)

# Link libcurl and cJSON to executable
target_link_libraries(p1_recipe_recommender libcurl cjson)