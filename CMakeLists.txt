cmake_minimum_required(VERSION 3.6)
project(robonav)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        Source/Parsers/FileParser.cpp
        Source/Containers/Environment.cpp
        Source/Containers/Graph.cpp
        Source/Search/Uninformed.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC Source)

add_executable(tests ${SOURCE_FILES} Tests/UninformedTests.cpp)
target_include_directories(tests PUBLIC Source Tests)
