add_subdirectory(ai)
add_library(Game Test.cpp Test.hpp
        Scenes/idxImageViewer.cpp
        Scenes/idxImageViewer.hpp
        idx/Reader.cpp
        idx/Reader.hpp
        Scenes/ImageClassifier.cpp
        Scenes/ImageClassifier.hpp)
target_link_libraries(Game PRIVATE AI)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
