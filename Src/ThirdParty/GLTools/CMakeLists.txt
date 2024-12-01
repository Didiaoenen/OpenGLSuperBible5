project(GLTools)

set(TARGET GLTools)

set(HDRS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(GLTOOLS_HDRS
	"${HDRS_DIR}/GLBatchBase.h"
	"${HDRS_DIR}/GLBatch.h"
	"${HDRS_DIR}/GLFrame.h"
	"${HDRS_DIR}/GLFrustum.h"
	"${HDRS_DIR}/GLGeometryTransform.h"
	"${HDRS_DIR}/GLMatrixStack.h"
	"${HDRS_DIR}/GLShaderManager.h"
	"${HDRS_DIR}/GLTools.h"
	"${HDRS_DIR}/GLTriangleBatch.h"
	"${HDRS_DIR}/math3d.h"
	"${HDRS_DIR}/StopWatch.h"

	"${HDRS_DIR}/GL/glew.h"
	"${HDRS_DIR}/GL/glxew.h"
	"${HDRS_DIR}/GL/wglew.h"
)

set(GLTOOLS_SRCS
	"${SRCS_DIR}/GLBatch.cpp"
	"${SRCS_DIR}/GLShaderManager.cpp"
	"${SRCS_DIR}/GLTools.cpp"
	"${SRCS_DIR}/GLTriangleBatch.cpp"
	"${SRCS_DIR}/math3d.cpp"

	"${SRCS_DIR}/glew.c"
	"${SRCS_DIR}/glewinfo.c"
	"${SRCS_DIR}/visualinfo.c"
)

add_library(${TARGET} STATIC ${GLTOOLS_HDRS} ${GLTOOLS_SRCS})

target_include_directories(${TARGET} PUBLIC ${HDRS_DIR})

set_target_properties(${TARGET} PROPERTIES FOLDER "Third-party")

set_target_properties(${TARGET} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")