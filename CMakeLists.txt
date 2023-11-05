cmake_minimum_required(VERSION 3.26)
project(p1_recipe_recommender C)

set(CMAKE_C_STANDARD 23)

# Include FetchContent module
include(FetchContent)

# Declare the external dependency (libcurl in this case)
FetchContent_Declare(
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG        curl-7_76_1 # Use the appropriate tag or commit
)

# Download and make the declared content available
FetchContent_MakeAvailable(curl)

# Add your executable
add_executable(p1_recipe_recommender main.c
        db/api_functions.h
        db/api_functions.c
        item/item_functions.h
        item/item_functions.c)

# Link libcurl to your executable
target_link_libraries(p1_recipe_recommender libcurl)
