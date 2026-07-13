cmake_minimum_required(VERSION 3.20)
project(cpplings LANGUAGES CXX)

find_package(Git QUIET)

set(DOCTEST_DIR "${CMAKE_SOURCE_DIR}/submodules/doctest")

if(GIT_FOUND AND EXISTS "${CMAKE_SOURCE_DIR}/.gitmodules")
    file(GLOB DOCTEST_CONTENTS "${DOCTEST_DIR}/*")

    if(NOT DOCTEST_CONTENTS)
        message(STATUS "submodules/doctest is empty, updating submodules...")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT
        )
        if(NOT GIT_SUBMOD_RESULT EQUAL 0)
            message(FATAL_ERROR "git submodule update failed: ${GIT_SUBMOD_RESULT}")
        endif()
    endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

if(NOT (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU"))
    message(FATAL_ERROR "Only Clang and GCC are supported.")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64|i[3-6]86)$")
    set(SAN_FLAGS "-fsanitize=address,undefined,leak")
else()
    set(SAN_FLAGS "-fsanitize=address,undefined")
endif()

file(GLOB_RECURSE EXERCISE_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/exercises/*.cpp"
)

enable_testing()

foreach(ex_file ${EXERCISE_FILES})
    get_filename_component(ex_name ${ex_file} NAME_WE)

    add_executable(${ex_name} ${ex_file})
    target_compile_features(${ex_name} PUBLIC cxx_std_23)
    target_compile_options(
        ${ex_name}
        PUBLIC  ${SAN_FLAGS}
        PRIVATE -Wall -Wextra -Wpedantic -g3
    )
    target_include_directories(
        ${ex_name}
        PUBLIC  ${CMAKE_SOURCE_DIR}/submodules/doctest
        PRIVATE ${CMAKE_SOURCE_DIR}/include
    )
    target_compile_definitions(${ex_name} PRIVATE DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN)
    target_link_options(${ex_name} PUBLIC ${SAN_FLAGS})

    add_test(NAME ${ex_name} COMMAND ${ex_name})
endforeach()
