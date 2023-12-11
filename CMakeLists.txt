cmake_minimum_required(VERSION 3.27)
project(advent_of_code_cpp)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/day*)
foreach(subdir ${SUBDIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()
