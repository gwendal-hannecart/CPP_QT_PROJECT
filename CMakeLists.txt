cmake_minimum_required(VERSION 3.10)
project(CPP_QT_TPminiprojet)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_FLAGS "-O2")

find_package(Qt5Widgets CONFIG REQUIRED)

file (GLOB_RECURSE sourceCode src/*.cpp src/*.h )

add_executable(CPP_QT_TPminiprojet ${sourceCode})

target_link_libraries(CPP_QT_TPminiprojet Qt5::Widgets)

