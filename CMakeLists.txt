cmake_minimum_required(VERSION 3.6)
project(robonav)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules)

set(SOURCE_FILES
        Source/Parsers/FileParser.cpp
        Source/Parsers/CLIParser.cpp
        Source/Search/Core/Environment.cpp
        Source/Search/Core/SearchMethod.cpp)

# Add search methods
set(SOURCE_FILES ${SOURCE_FILES}
        Source/Search/Methods/BreadthFirst.cpp
        Source/Search/Methods/DepthFirst.cpp
        Source/Search/Methods/GreedyBestFirst.cpp
        Source/Search/Methods/AStar.cpp
        Source/Search/Methods/IDS.cpp
        Source/Search/Methods/IDAStar.cpp)

# Visualizer source
set(VISUALIZER_SOURCE
        Source/Visualizer/VisualizerApp.cpp
        Source/Visualizer/Text.cpp
        Source/Visualizer/Color.cpp
        Source/Visualizer/PathVisualizer.cpp
        Source/Visualizer/GraphicsDriver.cpp
        Source/Visualizer/Window.cpp)

LINK_DIRECTORIES(Deps)

add_subdirectory(Deps/Path)

include_directories(Deps/SDL2-2.0.5/include)
include_directories(Deps/Path)

# Main project
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${VISUALIZER_SOURCE} Source/Main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC Source Deps/Skyrocket/Source)
target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} skyrocket_path)

# Tests
add_executable(tests ${SOURCE_FILES} Tests/Tests.cpp)
target_include_directories(tests PUBLIC Source Tests Deps/Skyrocket/Source)
target_link_libraries(tests SDL2)
target_link_libraries(tests skyrocket_path)

# Standalone visualizer
add_executable(robovisualizer ${SOURCE_FILES} ${VISUALIZER_SOURCE} Source/VisualizerMain.cpp)
target_include_directories(robovisualizer PUBLIC Source Deps/Skyrocket/Source)
target_link_libraries(robovisualizer SDL2)
target_link_libraries(robovisualizer skyrocket_path)

# Win32
if (WIN32)
    include_directories(Deps/SDL2_ttf-2.0.14/Win32/include)
    target_link_libraries(robovisualizer SDL2_ttf.lib)
    target_link_libraries(${PROJECT_NAME} SDL2_ttf.lib)
else()
    include_directories(Deps/SDL2_ttf-2.0.14/macOS/SDL2_ttf.framework/Headers)
    target_link_libraries(robovisualizer SDL2_ttf)
    target_link_libraries(${PROJECT_NAME} SDL2_ttf)
endif()
