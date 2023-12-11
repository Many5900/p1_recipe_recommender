cmake_minimum_required(VERSION 3.26)
project(p1_recipe_recommender C)

set(CMAKE_C_STANDARD 23)

# Add subdirectories for cJSON and curl
add_subdirectory(curl)
add_subdirectory(cJSON)

# Add executable
add_executable(p1_recipe_recommender main.c
        api/api_functions.h
        api/api_functions.c
        item/item_functions.h
        item/item_functions.c
        deserializer/deserializer.h
        deserializer/deserializer.c
        print/print.c
        print/print.h
        time/time_and_date.h
        time/time_and_date.h
        time/time_and_date.c
        time/time_and_date.c
        stats/stats.h
        stats/stats.h
        stats/stats.c
        stats/stats.c
        menu/menu.h
        menu/menu.h
        menu/menu.c
        menu/menu.c
        menu/logic/menu_logic.h
        menu/logic/menu_logic.h
        menu/logic/menu_logic.c
        menu/logic/menu_logic.c
        recipe_recommender/recipe_recommender.h
        recipe_recommender/recipe_recommender.h
        recipe_recommender/recipe_recommender.c
        recipe_recommender/recipe_recommender.c)

# Link libcurl and cJSON to executable
target_link_libraries(p1_recipe_recommender libcurl cjson)