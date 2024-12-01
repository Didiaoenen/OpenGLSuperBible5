add_subdirectory(HDR_Msaa)
add_subdirectory(HDR_Bloom)
add_subdirectory(HDR_Imaging)

set_target_properties(
    HDR_Msaa
    HDR_Bloom
    HDR_Imaging
    PROPERTIES FOLDER "Chapter09"
)