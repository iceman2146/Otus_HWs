cmake_minimum_required(VERSION 3.5)
project(ContainerPRJ)

add_executable(main 
main.cpp
src/Sequence.cpp
src/ForwardList.cpp
src/List.cpp
)

target_include_directories(main PRIVATE include)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
    CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(main PRIVATE 
        -g
        -Wall
        -Wextra
        -Werror
        -pedantic
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(main PRIVATE
        #/EHa
        #/W4
        #/WX
    )
endif()
set_target_properties(main PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
