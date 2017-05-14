project(POCChatbot)
cmake_minimum_required(VERSION 2.8)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake/modules/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   #for executables

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -g -pthread -ldl")

include_directories("include")

file(GLOB_RECURSE source_files "src/*.cpp")
file(GLOB_RECURSE header_files "include/*.hpp" "include/ext/*.hpp" "include/ext/*.hpp")

add_executable(${PROJECT_NAME} ${header_files} ${source_files})

target_compile_definitions(${PROJECT_NAME} PRIVATE CHAISCRIPT_NO_THREADS=1)
