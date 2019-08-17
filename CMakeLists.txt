cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

message("Hello")

project(sudoku)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE 
    "*.h"
    "*.cpp"
)

set(SOURCE_EXE sudoku.cpp SudokuElement.cpp SudokuField.cpp SudokuFieldManager.cpp)

add_executable(sudoku ${SOURCE_EXE})