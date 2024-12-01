add_subdirectory(Move)
add_subdirectory(Bounce)
add_subdirectory(Triangle)

set_target_properties(
    Move
    Bounce
    Triangle
    PROPERTIES FOLDER "Chapter02"
)