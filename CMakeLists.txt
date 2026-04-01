cmake_minimum_required(VERSION 3.20)
project(cpplings LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

if(NOT (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU"))
  message(FATAL_ERROR "Only Clang and GCC are supported.")
endif()

set(SAN_FLAGS "-fsanitize=address,leak,undefined")
add_compile_options(${SAN_FLAGS})
add_link_options(${SAN_FLAGS})

add_compile_options(-Wall -Wextra -Wpedantic -Werror -g3)

include_directories(${CMAKE_SOURCE_DIR}/external/doctest)

file(GLOB_RECURSE EXERCISE_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/exercises/*.cpp"
)

enable_testing()

foreach(ex_file ${EXERCISE_FILES})
    get_filename_component(ex_name ${ex_file} NAME_WE)

    add_executable(${ex_name} ${ex_file})
    target_include_directories(${ex_name} PRIVATE ${CMAKE_SOURCE_DIR}/include)

    target_compile_definitions(${ex_name} PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)

    add_test(NAME ${ex_name} COMMAND ${ex_name})
endforeach()
