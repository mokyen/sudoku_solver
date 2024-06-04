cmake_minimum_required(VERSION 3.5)

#Note that the compiler version and standard are important, as the version
#of cmake may not work with the compiled gtest. The chosen versions are
#x86-64 gcc 13.1 with flag -std=c++20

project(shapes)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(the_executable
    Cell.cpp
    # test_Cell.cpp
    CellView.cpp
    # test_CellView.cpp
    GridHelpers.cpp
    # test_GridHelpers.cpp
    Grid.cpp
    test_Grid.cpp
    PuzzleLoading.cpp
    test_PuzzleLoading.cpp
    )

target_link_libraries(the_executable PRIVATE gtest gmock gtest_main)
target_include_directories (the_executable
    PRIVATE
    .
)

