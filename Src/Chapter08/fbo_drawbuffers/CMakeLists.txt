
project(FBO_DrawBuffers CXX)

set(TARGET FBO_DrawBuffers)

find_package(GLUT REQUIRED)

# set(HDR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# set(HDRS
#     ${HDR_DIR}/Base/FTransform.h
# )

set(SRCS
    ${SRC_DIR}/fbo_drawbuffers.cpp
)

add_executable(${TARGET} ${SRCS})

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_target_properties(${TARGET} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

# target_include_directories(${TARGET} PUBLIC ${HDR_DIR})

target_link_libraries(${TARGET} PRIVATE Ninja GLTools GLUT::GLUT)

set_target_properties(${TARGET} PROPERTIES VS_GLOBAL_VcpkgEnabled true)