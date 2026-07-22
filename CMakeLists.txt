cmake_minimum_required(VERSION 4.40)
project(SegmentIntersection3D VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Основная библиотека
add_library(segment_intersection
    src/vector3d.cpp
    src/segment3d.cpp
    src/intersection.cpp
)
target_include_directories(segment_intersection PUBLIC include)

# Демонстрационное приложение
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE segment_intersection) 