cmake_minimum_required(VERSION 3.5.0)

# compile json module
add_library(json)
target_sources(json PRIVATE
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    "json.parser.ixx"
    "json.tokenizer.ixx"
    "json.tokenizer_v2.ixx"
    "json.string.ixx"
    "json.tokenizerStates.ixx" 
    "json.array.ixx"
)
