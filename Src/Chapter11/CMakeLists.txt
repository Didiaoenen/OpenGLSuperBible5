add_subdirectory(Julia)
add_subdirectory(GSCulling)
add_subdirectory(GSExplode)
add_subdirectory(GSNormals)
add_subdirectory(Convolution)
add_subdirectory(Perspective2)
add_subdirectory(GSTessellate)

set_target_properties(
    Julia
    GSCulling
    GSExplode
    GSNormals
    Convolution
    Perspective2
    GSTessellate
    PROPERTIES FOLDER "Chapter11"
)