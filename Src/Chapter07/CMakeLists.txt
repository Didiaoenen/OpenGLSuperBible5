add_subdirectory(CubeMapped)
add_subdirectory(MultiTexture)
add_subdirectory(NormalMapped)
add_subdirectory(PointSprites)
add_subdirectory(SphereMapped)
add_subdirectory(TextureArrays)
add_subdirectory(TextureRect)

set_target_properties(
    CubeMapped
    MultiTexture
    NormalMapped
    PointSprites
    SphereMapped
    TextureArrays
    TextureRect
    PROPERTIES FOLDER "Chapter07"
)