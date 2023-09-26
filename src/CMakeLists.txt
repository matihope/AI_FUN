add_subdirectory(ai)
add_library(Game Test.cpp Test.hpp
        Scenes/IdxTestImgRecognition/IdxImageViewer.cpp
        Scenes/IdxTestImgRecognition/IdxImageViewer.hpp
        idx/Reader.cpp
        idx/Reader.hpp
        Scenes/IdxTestImgRecognition/ImageClassifierScene.cpp
        Scenes/IdxTestImgRecognition/ImageClassifierScene.hpp
        IdxDigitTrainer.cpp
        IdxDigitTrainer.hpp
        Scenes/MainMenu.cpp
        Scenes/MainMenu.hpp
        Scenes/DigitDrawing/DrawBoard.cpp
        Scenes/DigitDrawing/DrawBoard.hpp
        Scenes/IdxTestImgRecognition/TestImageTransitions.cpp
        Scenes/IdxTestImgRecognition/TestImageTransitions.hpp)
target_link_libraries(Game PRIVATE AI)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
