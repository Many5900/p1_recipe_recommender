cmake_minimum_required(VERSION 3.26)
project(p1_recipe_recommender C)

set(CMAKE_C_STANDARD 23)

# Add subdirectories for cJSON and curl
add_subdirectory(curl)
add_subdirectory(cJSON)

# Add your executable
add_executable(p1_recipe_recommender main.c
        db/api_functions.h
        db/api_functions.c
        item/item_functions.h
        item/item_functions.c
        deserializer/deserializer.h
        deserializer/deserializer.c)

# Link libcurl and cJSON to your executable
# Make sure to use the correct target names for libcurl and cJSON. These target names
# are defined in the CMakeLists.txt of the respective libraries. For example, it might
# be 'libcurl' or just 'curl' depending on how it's set up in the curl CMakeLists.txt.
# target_link_libraries(p1_recipe_recommender curl cJSON)


# Link libcurl and cJSON to your executable
target_link_libraries(p1_recipe_recommender libcurl cjson)
