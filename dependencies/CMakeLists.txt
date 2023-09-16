# Huge thanks to https://github.com/eliasdaler for the base script!

include(FetchContent)

set(SFML_VERSION 2.6.0)
set(IMGUI_VERSION 1.89.9)
set(NLOHMANN_JSON_VERSION 3.11.2)
set(IMGUI_SFML_VERSION 2.6)

# It's nice to get stripped-down release zips instead of cloning
# a repo and checking out a tag
FetchContent_Declare(
        SFML
        URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)

FetchContent_Declare(
        imgui
        URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)

FetchContent_Declare(
        imgui-sfml
        URL "https://github.com/SFML/imgui-sfml/archive/v${IMGUI_SFML_VERSION}.zip"
)

FetchContent_Declare(
        json
        URL "https://github.com/nlohmann/json/archive/v${NLOHMANN_JSON_VERSION}.zip"
)

## finally, let's build

# SFML
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(sfml)

# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)
FetchContent_MakeAvailable(imgui-sfml)

# nlohmann-json
FetchContent_MakeAvailable(json)
