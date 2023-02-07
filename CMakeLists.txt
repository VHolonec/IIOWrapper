cmake_minimum_required(VERSION 3.5)

project(IIOWrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(libiio REQUIRE)

add_executable(IIOWrapper main.cpp)

target_link_libraries(IIOWrapper  iio)

install(TARGETS IIOWrapper
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
