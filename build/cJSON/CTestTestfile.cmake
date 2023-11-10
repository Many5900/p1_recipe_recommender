# CMake generated Testfile for 
# Source directory: /Users/marcnygaard/CLionProjects/p1_recipe_recommender/cJSON
# Build directory: /Users/marcnygaard/CLionProjects/p1_recipe_recommender/build/cJSON
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "/Users/marcnygaard/CLionProjects/p1_recipe_recommender/build/cJSON/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/marcnygaard/CLionProjects/p1_recipe_recommender/cJSON/CMakeLists.txt;252;add_test;/Users/marcnygaard/CLionProjects/p1_recipe_recommender/cJSON/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
