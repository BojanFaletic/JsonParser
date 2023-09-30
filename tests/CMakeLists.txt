cmake_minimum_required(VERSION 3.5.0)

# add test
add_executable(JsonParserTest "test.cpp")
target_link_libraries(JsonParserTest PRIVATE json)

# copy test.json to build directory
configure_file(test.json test.json COPYONLY)

