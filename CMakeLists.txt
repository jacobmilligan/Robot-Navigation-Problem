cmake_minimum_required(VERSION 3.6)
project(robonav)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Source/Parsers/FileParser.cpp
        Source/Search/Environment.cpp
        Source/Search/SearchMethod.cpp
        Source/Visualizer/App.cpp)

add_subdirectory(Deps/Skyrocket)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cpp)
target_link_libraries(${PROJECT_NAME} skyrocket)
target_include_directories(${PROJECT_NAME} PUBLIC Source Deps/Skyrocket/Source)

add_executable(tests ${SOURCE_FILES} Tests/Tests.cpp)
target_include_directories(tests PUBLIC Source Tests)
