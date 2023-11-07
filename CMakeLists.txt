cmake_minimum_required(VERSION 3.26)
project(p1_recipe_recommender C)

set(CMAKE_C_STANDARD 23)

# Include FetchContent module
include(FetchContent)

# Declare the external dependency for libcurl
FetchContent_Declare(
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG        curl-7_76_1 # Use the appropriate tag or commit
)

# Declare the external dependency for cJSON
FetchContent_Declare(
        cJSON
        GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
        GIT_TAG        v1.7.14 # Use the appropriate tag or commit, make sure it's compatible
)

# Download and make the declared content available
FetchContent_MakeAvailable(curl cJSON)

# Add your executable
add_executable(p1_recipe_recommender main.c
        db/api_functions.h
        db/api_functions.c
        item/item_functions.h
        item/item_functions.c
        deserializer/deserializer.h
        deserializer/deserializer.c)

# Link libcurl and cJSON to your executable
target_link_libraries(p1_recipe_recommender libcurl cJSON)
