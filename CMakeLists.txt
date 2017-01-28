cmake_minimum_required(VERSION 3.5)
project(SIDE-tech)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(libs/novile libs/novile/build)

include_directories(libs/novile/src)
link_directories(libs/*/build)

find_package(Qt5WebKitWidgets REQUIRED)
qt5_add_resources(SIDE_TECH_RCC_SRC SIDE-tech.qrc)
qt5_wrap_ui(SIDE_TECH_UIC_HDR mainwindow.ui)

set(SOURCE_FILES main.cpp mainwindow.cpp)
add_executable(SIDE-tech ${SOURCE_FILES} ${SIDE_TECH_RCC_SRC} ${SIDE_TECH_UIC_HDR})

target_link_libraries(SIDE-tech novile)

qt5_use_modules(SIDE-tech WebKitWidgets)
