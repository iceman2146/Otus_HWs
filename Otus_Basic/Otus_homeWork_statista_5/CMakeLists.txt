cmake_minimum_required(VERSION 3.5)

project(Statist)

add_executable(statistics 
main.cpp
src/mean.cpp
src/std.cpp
src/min.cpp
src/max.cpp
src/procentil90.cpp
src/procentil95.cpp
)

target_include_directories(statistics PRIVATE include)
set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(statistics PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(statistics PRIVATE
        /EHsc
        /W4
        /WX
    )
endif()
