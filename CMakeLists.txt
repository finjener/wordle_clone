cmake_minimum_required(VERSION 3.14)

project(WordleMVC VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Quick REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(src)

install(TARGETS wordle
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES WORDS DESTINATION ${CMAKE_INSTALL_BINDIR}) 