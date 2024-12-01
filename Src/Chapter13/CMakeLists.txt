add_subdirectory(Block_Redux)
add_subdirectory(Sphere_World_Redux)

set_target_properties(
    Block_Redux
    Sphere_World_Redux
    PROPERTIES FOLDER "Chapter13"
)