add_subdirectory(ai)
add_library(Game
        Scenes/IdxTestImgRecognition/IdxImageViewer.cpp
        Scenes/IdxTestImgRecognition/IdxImageViewer.hpp
        idx/Reader.cpp
        idx/Reader.hpp
        Scenes/IdxTestImgRecognition/ImageClassifierScene.cpp
        Scenes/IdxTestImgRecognition/ImageClassifierScene.hpp
        Scenes/IdxTestImgRecognition/IdxDigitTrainer.cpp
        Scenes/IdxTestImgRecognition/IdxDigitTrainer.hpp
        Scenes/MainMenu.cpp
        Scenes/MainMenu.hpp
        Scenes/DigitDrawing/DrawBoard.cpp
        Scenes/DigitDrawing/DrawBoard.hpp
        Scenes/IdxTestImgRecognition/TestImageTransitions.cpp
        Scenes/IdxTestImgRecognition/TestImageTransitions.hpp
        Scenes/FlappyBird/FlappyLevel.cpp
        Scenes/FlappyBird/FlappyLevel.hpp
        Scenes/FlappyBird/FlappyPlayer.cpp
        Scenes/FlappyBird/FlappyPlayer.hpp
        Scenes/FlappyBird/FlappyController.cpp
        Scenes/FlappyBird/FlappyController.hpp
        Scenes/FlappyBird/FlappyGame.cpp
        Scenes/FlappyBird/FlappyGame.hpp
        Scenes/FlappyBird/FlappyKeyboardController.cpp
        Scenes/FlappyBird/FlappyKeyboardController.hpp
        Scenes/FlappyBird/FlappyRenderer.cpp
        Scenes/FlappyBird/FlappyRenderer.hpp)


target_link_libraries(Game PRIVATE AI)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
