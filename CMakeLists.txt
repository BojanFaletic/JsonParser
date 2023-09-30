cmake_minimum_required(VERSION 3.5.0)
project(JsonParser VERSION 0.1.0 LANGUAGES CXX)

# activate cxx modules based on cmake version
# 3.26.4-msvc4
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
# 3.27.3
#set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
message( STATUS "CMAKE_VERSION: " ${CMAKE_VERSION} )


# get pybind11 cmake location by running pybind11 --cmakedir
execute_process(
COMMAND py -m pybind11 --cmakedir
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# find python, pybind11
find_package(Python COMPONENTS Interpreter Development Development.Module Development.Embed)
find_package(pybind11 CONFIG)

# set c++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# compile json module
add_library(json)
target_sources(json PRIVATE
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    "src/json.parser.ixx"
)

# add module
pybind11_add_module(JsonParser module.cpp)
target_link_libraries(JsonParser PRIVATE json)

# install module into python
install(TARGETS JsonParser DESTINATION ${CMAKE_SOURCE_DIR}/python)


# add test
add_executable(JsonParserTest "test/test.cpp")
target_link_libraries(JsonParserTest PRIVATE json)