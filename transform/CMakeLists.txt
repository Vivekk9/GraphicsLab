get_filename_component(EXERCISENAME ${CMAKE_CURRENT_LIST_DIR} NAME)
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE SHADERS "*.glsl")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

add_executable(${EXERCISENAME} ${SOURCES} ${HEADERS} ${SHADERS})
if(WIN32)
        target_link_libraries(${EXERCISENAME} "legacy_stdio_definitions.lib")
endif()
target_link_libraries(${EXERCISENAME} ${COMMON_LIBS})

#--- data need to be copied to run folder
file(COPY ${PROJECT_SOURCE_DIR}/transform/Textures/earth.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY ${PROJECT_SOURCE_DIR}/transform/Textures/sun.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY ${PROJECT_SOURCE_DIR}/transform/Textures/moon.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)

file(COPY ${PROJECT_SOURCE_DIR}/transform/Shaders/Quad_vshader.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY ${PROJECT_SOURCE_DIR}/transform/Shaders/Quad_fshader.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
