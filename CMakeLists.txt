cmake_minimum_required (VERSION 3.15)
project(zcurve)

find_package(Boost)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()


# Include all files in include
file(GLOB include_files
    "include/*.h"
    "include/*.hpp"
)
message(${include_files})
add_executable(zcurve src/test.cpp ${include_files})

target_include_directories(zcurve PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)