add_library(AI NeuralNetwork.cpp NeuralNetwork.hpp
        Base/ActivatingFunction.cpp
        Base/ActivatingFunction.hpp)
target_include_directories(AI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
