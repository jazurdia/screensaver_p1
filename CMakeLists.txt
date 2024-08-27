cmake_minimum_required(VERSION 3.28)
project(screensaver_p1 C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "C:/coding/CP/SDL2-devel-2.30.6-mingw/SDL2-2.30.6/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(screensaver_p1 src/main.c)


target_link_libraries(screensaver_p1 ${SDL2_LIBRARY})

