
add_compile_definitions("DEBUG=$<CONFIG:Debug>")
set(ENGINE_SOURCES
        Game/Game.cpp
        GUI/Label.cpp
        GUI/Button.cpp
        JsonBridge/JsonBridge.cpp
        CollisionComponent/CollisionComponent.cpp
        CollisionShape/CollisionShape.cpp
        ResourceManager/ResourceManager.cpp
        WorldEntity/WorldEntity.cpp
        Clickable/Clickable.cpp
        SpriteBatch/SpriteBatch.cpp SpriteBatch/SpriteBatch.hpp SpriteBatch/QuickSprite.cpp SpriteBatch/QuickSprite.hpp
        Nodes/RectShape.cpp
        Nodes/RectShape.hpp
        Nodes/CircleShape.cpp
        Nodes/CircleShape.hpp
        Nodes/RayShape.cpp
        Nodes/RayShape.hpp
        WorldEntity/BoxyWorldEntity.cpp
        WorldEntity/BoxyWorldEntity.hpp
        Math/Vector2f.cpp
        Math/Vector2f.hpp
        Math/Geometry.cpp
        Math/Geometry.hpp
        Math/Base.cpp
        Math/Base.hpp
        Math/Matrix.cpp
        Math/Matrix.hpp
)

add_library(Engine ${ENGINE_SOURCES})
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
