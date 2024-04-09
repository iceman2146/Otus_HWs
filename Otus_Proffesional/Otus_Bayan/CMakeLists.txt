cmake_minimum_required(VERSION 3.26)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(bayan VERSION ${PROJECT_VESRION})
configure_file(version.h.in version.h) 
find_package( Boost COMPONENTS chrono filesystem program_options regex REQUIRED )
set(EXEC_NAME ${CMAKE_PROJECT_NAME})
set(LIB_NAME ${CMAKE_PROJECT_NAME}_lib)



include_directories(${Boost_INCLUDE_DIR} )
include_directories(include)

set(CMAKE_CXX_STANDARD 11)

include_directories( ${Boost_INCLUDE_DIR} )



include_directories("include/")
include_directories("include/filter")
include_directories("include/scanner")
set(SRC_PATH "src/")


add_executable(${EXEC_NAME} 
  ${SRC_PATH}/bayan.cpp
)

add_library(${LIB_NAME} 
  ${SRC_PATH}/parser.cpp  
  ${SRC_PATH}/scanner/files.cpp
  ${SRC_PATH}/scanner/duplicated.cpp 
)

set_target_properties(${EXEC_NAME} ${LIB_NAME}  PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
)

target_include_directories(${EXEC_NAME} 
  PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${LIB_NAME}
  ${Boost_LIBRARIES}
)

target_link_libraries(${EXEC_NAME} PRIVATE
  ${LIB_NAME} 
)

add_definitions(-D_SCL_SECURE_NO_WARNINGS)

install(TARGETS bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)
include (CPack)