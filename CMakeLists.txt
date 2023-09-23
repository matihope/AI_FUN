cmake_minimum_required(VERSION 3.25)

project(AI_FUN VERSION 0.1)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# dependencies
add_subdirectory(dependencies)

link_libraries(sfml-graphics sfml-window sfml-system sfml-audio)
link_libraries(nlohmann_json::nlohmann_json)

# Engine
add_subdirectory(Engine)
link_libraries(Engine)

# Game source code
add_subdirectory(src)
link_libraries(Game)

add_executable(${PROJECT_NAME} main.cpp)
