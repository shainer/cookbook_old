cmake_minimum_required(VERSION 2.8)
project(cookbook)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )

find_package(Qt5Widgets)
find_package(Sqlite REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (COOKBOOK_UI_FILES
     ui/mainwindow.ui
     ui/addrecipedialog.ui
     ui/viewrecipedialog.ui)

qt5_wrap_ui (COOKBOOK_UI  ${COOKBOOK_UI_FILES})

set (SOURCE_FILES
    src/recipe.cpp
    src/addrecipedialog.cpp
    src/viewrecipedialog.cpp
    src/mainwindow.cpp
    src/tags.cpp
    src/storage/recipestorage.cpp
    src/storage/recipedatabasestorage.cpp)

add_library(libcookbook ${SOURCE_FILES} ${COOKBOOK_UI})
target_link_libraries (libcookbook Qt5::Widgets)

add_executable(cookbook src/main.cpp)
target_link_libraries (cookbook libcookbook ${SQLITE_LIBRARIES})
