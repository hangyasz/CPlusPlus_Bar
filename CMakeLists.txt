cmake_minimum_required(VERSION 3.28)
project(hazzi_lion)
add_compile_options(-Wall -Wextra )
add_compile_definitions(MEMTRACE)
set(CMAKE_CXX_STANDARD 11)

add_executable(hazzi_lion main.cpp
        Ital.cpp
        Ital.h
        koktle.cpp
        koktle.h
        italok_kezel.cpp
        memtrace.h
        memtrace.cpp
        bevitel_kezel.cpp
        bevitel_kezel.h
        faljkezel.cpp
        faljkezel.h
        gtest_lite.h
        string5.h
        string5.cpp
        fugvenyek.hpp
)
