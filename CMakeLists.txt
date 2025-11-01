# https://cmake.org/cmake/help/latest/release/index.html
cmake_minimum_required(VERSION 4.1)

project(
  untitled1 # ${CMAKE_PROJECT_NAME}
  VERSION 0.0.1
  LANGUAGES CXX)

# https://en.cppreference.com/w/cpp/23.html
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO 看是否能删掉
set(QT_FORCE_CMP0156_TO_VALUE NEW)

# https://doc-snapshots.qt.io/
find_package(Qt6 6.10 REQUIRED COMPONENTS WebEngineWidgets)

qt6_standard_project_setup(REQUIRES ${Qt6_VERSION_MAJOR}.${Qt6_VERSION_MINOR})

qt6_add_executable(${CMAKE_PROJECT_NAME} main.cpp ApplicationMain.h
                   ApplicationMain.cpp ApplicationMain.ui)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::WebEngineWidgets)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)
