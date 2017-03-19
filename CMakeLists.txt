cmake_minimum_required(VERSION 3.6)
project(robonav)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules)

set(SOURCE_FILES
        Source/Parsers/FileParser.cpp
        Source/Search/Environment.cpp
        Source/Search/SearchMethod.cpp
        Source/Visualizer/VisualizerApp.cpp
        Source/Visualizer/Color.cpp
        Source/Visualizer/GraphicsDriver.cpp
        Source/Visualizer/Window.cpp)

add_subdirectory(Deps/SDL2-2.0.5)
add_subdirectory(Deps/Path)

FIND_PACKAGE(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(Deps/Path)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC Source Deps/Skyrocket/Source)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} skyrocket_path)

add_executable(tests ${SOURCE_FILES} Tests/Tests.cpp)
target_include_directories(tests PUBLIC Source Tests)
