cmake_minimum_required(VERSION 3.6)
project(search)

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
        Source/Visualizer/PathRenderer.cpp
        Source/Visualizer/GraphicsDriver.cpp
        Source/Visualizer/Window.cpp)

if (WIN32)
    LINK_DIRECTORIES(Deps/SDL2-2.0.5/Win32/lib/x86
        Deps/SDL2_ttf-2.0.14/Win32/lib/x86)

    include_directories(Deps/SDL2_ttf-2.0.14/Win32/include)
    include_directories(Deps/SDL2-2.0.5/Win32/include)
else()
    LINK_DIRECTORIES(Deps/SDL2-2.0.5/macOS
            Deps/SDL2_ttf-2.0.14/macOS)
endif()


add_subdirectory(Deps/Path)
include_directories(Deps/Path)
include_directories(Deps/catch)
include_directories(Source)

# Main project
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${VISUALIZER_SOURCE} Source/Main.cpp)
target_link_libraries(${PROJECT_NAME} skyrocket_path)

# Tests
add_executable(tests ${SOURCE_FILES} Tests/Tests.cpp)
target_include_directories(tests PUBLIC Tests)
target_link_libraries(tests skyrocket_path)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/Resources/SOURCECODEPRO.ttf"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

# Win32
if (WIN32)
    target_link_libraries(${PROJECT_NAME} SDL2_ttf)

    target_link_libraries(${PROJECT_NAME} SDL2)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/Deps/SDL2_ttf-2.0.14/Win32/lib/x86/SDL2_ttf.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/Deps/SDL2_ttf-2.0.14/Win32/lib/x86/zlib1.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/Deps/SDL2_ttf-2.0.14/Win32/lib/x86/libfreetype-6.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/Deps/SDL2-2.0.5/Win32/lib/x86/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    ) 
else()
    include_directories(Deps/SDL2_ttf-2.0.14/macOS/SDL2_ttf.framework/Headers)
    target_link_libraries(${PROJECT_NAME} SDL2_ttf)

    include_directories(Deps/SDL2-2.0.5/macOS/SDL2.framework/Headers)
    target_link_libraries(${PROJECT_NAME} SDL2)
endif()
