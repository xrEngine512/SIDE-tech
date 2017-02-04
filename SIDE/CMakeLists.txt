cmake_minimum_required(VERSION 3.5)
project(SIDE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(../external/novile ../libs/novile/build)

include_directories(../external/novile/src)

find_package(Qt5WebKitWidgets REQUIRED)
qt5_add_resources(SIDE_RCC_SRC SIDE.qrc)
qt5_wrap_ui(SIDE_UIC_HDR mainwindow.ui)

set(SOURCE_FILES main.cpp mainwindow.cpp)
add_executable(SIDE ${SOURCE_FILES} ${SIDE_RCC_SRC} ${SIDE_UIC_HDR})

target_link_libraries(SIDE novile)

qt5_use_modules(SIDE WebKitWidgets)
