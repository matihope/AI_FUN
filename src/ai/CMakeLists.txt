add_library(AI Base/NeuralNetwork.cpp Base/NeuralNetwork.hpp
        Base/ActivatingFunction.cpp
        Base/ActivatingFunction.hpp
        Base/CostFunction.cpp
        Base/CostFunction.hpp
        Base/Layer.cpp
        Base/Layer.hpp
        Coaches/NeuralNetworkCoach.cpp
        Coaches/NeuralNetworkCoach.hpp
        Base/NeuralNetworkCalculationState.cpp
        Base/NeuralNetworkCalculationState.hpp
        Coaches/LayerGradient.cpp
        Coaches/LayerGradient.hpp
)
target_include_directories(AI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
