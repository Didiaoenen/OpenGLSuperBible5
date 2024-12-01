add_subdirectory(Grass)
add_subdirectory(Flocking)
add_subdirectory(SbmViewer)
add_subdirectory(Instancing)

set_target_properties(
    Grass
    Flocking
    SbmViewer
    Instancing
    PROPERTIES FOLDER "Chapter12"
)