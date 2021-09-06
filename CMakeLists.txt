cmake_minimum_required(VERSION 3.10)
project(qCrosshair)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH})
set(Qt5_DIR ${Qt5_DIR})

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(qCrosshair main.cpp src/qdot.h src/qdot.cpp src/crosshair.h src/crosshair.cpp src/dots.h src/qdot.ui dots.qrc icon.qrc)
target_link_libraries(qCrosshair
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )