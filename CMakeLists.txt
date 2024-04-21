cmake_minimum_required(VERSION 3.28)
project(hazzi_lion)

set(CMAKE_CXX_STANDARD 11)

add_executable(hazzi_lion main.cpp
        Ital.cpp
        Ital.h
        koktle.cpp
        koktle.h
        italok_kezel.cpp
        memtrace.h
        memtrace.cpp
        string_kezez.cpp
        string_kezez.h
        faljkezel.cpp
        faljkezel.h
)
