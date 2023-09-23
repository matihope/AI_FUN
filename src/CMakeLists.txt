add_subdirectory(ai)
add_library(Game Test.cpp Test.hpp
        Scenes/IdxImageViewer.cpp
        Scenes/IdxImageViewer.hpp
        idx/Reader.cpp
        idx/Reader.hpp
        Scenes/ImageClassifierScene.cpp
        Scenes/ImageClassifierScene.hpp
        IdxDigitTrainer.cpp
        IdxDigitTrainer.hpp)
target_link_libraries(Game PRIVATE AI)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
