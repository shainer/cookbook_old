cmake_minimum_required(VERSION 2.8)
project(cookbook)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(mainwindow mainwindow.cpp recipe.cpp recipestorage.cpp addrecipedialog.cpp)
target_link_libraries (mainwindow Qt5::Widgets)

add_executable(cookbook main.cpp)
target_link_libraries (cookbook mainwindow)
