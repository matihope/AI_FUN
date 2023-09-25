add_subdirectory(ai)
add_library(Game Test.cpp Test.hpp
        Scenes/MnistTestImgRecognition/IdxImageViewer.cpp
        Scenes/MnistTestImgRecognition/IdxImageViewer.hpp
        idx/Reader.cpp
        idx/Reader.hpp
        Scenes/MnistTestImgRecognition/ImageClassifierScene.cpp
        Scenes/MnistTestImgRecognition/ImageClassifierScene.hpp
        IdxDigitTrainer.cpp
        IdxDigitTrainer.hpp
        Scenes/MainMenu.cpp
        Scenes/MainMenu.hpp
        Scenes/DigitDrawing/DrawBoard.cpp
        Scenes/DigitDrawing/DrawBoard.hpp)
target_link_libraries(Game PRIVATE AI)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
