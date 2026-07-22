cmake_minimum_required(VERSION 4.4.0)
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

# Подключение тестов
option(BUILD_TESTS "Build unit tests" ON)
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest QUIET)
    # Скачивание GTest при необходимости
    if(NOT GTest_FOUND)
        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG main
        )
        FetchContent_MakeAvailable(googletest)
    endif()
    add_subdirectory(tests)
endif()