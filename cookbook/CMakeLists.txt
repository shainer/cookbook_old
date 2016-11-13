cmake_minimum_required(VERSION 2.8)
project(cookbook)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (COOKBOOK_UI mainwindow.ui addrecipedialog.ui viewrecipedialog.ui)

qt5_wrap_ui (COOKBOOK_UI_MOC  ${COOKBOOK_UI})

add_library(mainwindow mainwindow.cpp recipe.cpp recipestorage.cpp addrecipedialog.cpp viewrecipedialog.cpp ${COOKBOOK_UI_MOC})
target_link_libraries (mainwindow Qt5::Widgets)

add_executable(cookbook main.cpp)
target_link_libraries (cookbook mainwindow)
