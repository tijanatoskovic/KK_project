cmake_minimum_required(VERSION 3.15)
project(DCEPlugin)

find_package(LLVM 14 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 17 CACHE STRING "")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(DeadCodeElimination MODULE DeadCodeElimination.cpp)

llvm_map_components_to_libnames(llvm_libs
    Support
    Core
    IRReader
    Passes
)

target_link_libraries(DeadCodeElimination PRIVATE ${llvm_libs})

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tests_out)

file(GLOB TEST_FILES "${CMAKE_SOURCE_DIR}/tests/*.ll")

set(TEST_OUTPUTS)

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME)
    add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/tests_out/${TEST_NAME}
        COMMAND ${CMAKE_COMMAND} -E echo "Processing ${TEST_NAME}"
        COMMAND ${LLVM_TOOLS_BINARY_DIR}/opt
             -load-pass-plugin=${CMAKE_BINARY_DIR}/DeadCodeElimination.so
             -passes=dce-simple
             -S ${TEST_FILE}
             -o ${CMAKE_BINARY_DIR}/tests_out/${TEST_NAME}
        DEPENDS DeadCodeElimination ${TEST_FILE}
        COMMENT "Running DCE on ${TEST_NAME}"
    )
    list(APPEND TEST_OUTPUTS ${CMAKE_BINARY_DIR}/tests_out/${TEST_NAME})
endforeach()

add_custom_target(run_tests ALL DEPENDS ${TEST_OUTPUTS})
