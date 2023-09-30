cmake_minimum_required(VERSION 3.5.0)

# get pybind11 cmake location by running pybind11 --cmakedir
execute_process(
COMMAND py -m pybind11 --cmakedir
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# find python, pybind11
find_package(Python COMPONENTS Interpreter Development Development.Module Development.Embed)
find_package(pybind11 CONFIG)


# add module
pybind11_add_module(JsonParser module.cpp)
target_link_libraries(JsonParser PRIVATE json)

# install module into python
install(TARGETS JsonParser DESTINATION ${CMAKE_SOURCE_DIR}/python)
