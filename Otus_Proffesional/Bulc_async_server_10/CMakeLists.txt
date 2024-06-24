cmake_minimum_required(VERSION 3.26.0)
project(Bulk_server VERSION 0.1.0 LANGUAGES C CXX)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})


find_package(Boost COMPONENTS system thread chrono REQUIRED)
find_package(Threads REQUIRED)

#configure_file(version.h.in version.h) 


include(CTest)
enable_testing()
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(client ${SOURCE_FILES})

set_target_properties(client PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON)

target_link_libraries(client
        ${Boost_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
        ws2_32 wsock32)
target_include_directories(client PRIVATE ${Boost_INCLUDE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)
