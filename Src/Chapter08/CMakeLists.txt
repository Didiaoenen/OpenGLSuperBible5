add_subdirectory(PIX_Buffs)
add_subdirectory(FBO_Textures)
add_subdirectory(FBO_DrawBuffers)

set_target_properties(
    PIX_Buffs
    FBO_Textures
    FBO_DrawBuffers
    PROPERTIES FOLDER "Chapter08"
)