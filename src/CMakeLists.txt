add_subdirectory(AI)
add_library(Game Test.cpp Test.hpp)
target_link_libraries(Game PRIVATE AI)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
