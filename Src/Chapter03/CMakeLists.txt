add_subdirectory(Scissor)
add_subdirectory(GeoTest)
add_subdirectory(Smoother)
add_subdirectory(Blending)
add_subdirectory(Primitives)

set_target_properties(
    Scissor
    GeoTest
    Smoother
    Blending
    Primitives
    PROPERTIES FOLDER "Chapter03"
)