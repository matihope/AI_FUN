add_subdirectory(ai)
add_library(Game Test.cpp Test.hpp
        Scenes/MNISTImageViewer.cpp
        Scenes/MNISTImageViewer.hpp
        Scenes/idx/Reader.cpp
        Scenes/idx/Reader.hpp
        Scenes/Images.cpp
        Scenes/Images.hpp)
target_link_libraries(Game PRIVATE AI)
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
