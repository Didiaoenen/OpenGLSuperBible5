add_subdirectory(Move2)
add_subdirectory(Objects)
add_subdirectory(Perspective)
add_subdirectory(OrthoGraphic)
add_subdirectory(SphereWorld)
add_subdirectory(SphereWorld2)
add_subdirectory(SphereWorld3)
add_subdirectory(SphereWorld4)
add_subdirectory(ModelViewProjection)

set_target_properties(
    Move2
    Objects
    Perspective
    OrthoGraphic
    SphereWorld
    SphereWorld2
    SphereWorld3
    SphereWorld4
    ModelViewProjection
    PROPERTIES FOLDER "Chapter04"
)