cmake_minimum_required(VERSION 3.28)

set(PROJNAME numberCalc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(${PROJNAME} LANGUAGES C CXX)

add_compile_options(
        -std=c++20
        -Wall -Wextra -Wshadow -pedantic -pedantic-errors 
)

add_executable(${PROJNAME})

target_sources(${PROJNAME}
    PUBLIC 
    numberCalc.cxx
    Token.cxx
    Parser.cxx
    Logger.cxx
)

