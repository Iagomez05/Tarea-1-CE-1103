cmake_minimum_required(VERSION 3.28)
project(Generator)

set(CMAKE_CXX_STANDARD 23)

add_executable(Generator main.cpp
        PagedArray.cpp
        PagedArray.h
        SortingAlgorithm.cpp
        SortingAlgorithm.h
        QuickSort.cpp
        QuickSort.h
        InsertionSort.cpp
        InsertionSort.h
        BubbleSort.cpp
        BubbleSort.h
)
