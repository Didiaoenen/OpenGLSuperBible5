add_subdirectory(Tunnel)
add_subdirectory(Pyramid)
add_subdirectory(Anisotropic)
add_subdirectory(SphereWorld5)

set_target_properties(
    Tunnel
    Pyramid
    Anisotropic
    SphereWorld5
    PROPERTIES FOLDER "Chapter05"
)