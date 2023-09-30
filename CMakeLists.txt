cmake_minimum_required(VERSION 3.5.0)
project(JsonParser VERSION 0.1.0 LANGUAGES CXX)

# activate cxx modules based on cmake version
# 3.26.4-msvc4
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
# 3.27.3
#set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")

set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
message( STATUS "CMAKE_VERSION: " ${CMAKE_VERSION} )

# set c++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC include std. library

# build library
add_subdirectory(src)

# include directories module
add_subdirectory(module)
add_subdirectory(tests)
