add_subdirectory(Dissolve)
add_subdirectory(ADSPhong)
add_subdirectory(Triangle2)
add_subdirectory(ADSGouraud)
add_subdirectory(FlatShader)
add_subdirectory(LitTexture)
add_subdirectory(ToonShader)
add_subdirectory(DiffuseLight)
add_subdirectory(ShadedTriangle)
add_subdirectory(ProvokingVertex)
add_subdirectory(TexturedTriangle)

set_target_properties(
    Dissolve    
    ADSPhong
    Triangle2
    ADSGouraud
    FlatShader
    LitTexture
    ToonShader
    DiffuseLight
    ShadedTriangle
    ProvokingVertex
    TexturedTriangle
    PROPERTIES FOLDER "Chapter06"
)