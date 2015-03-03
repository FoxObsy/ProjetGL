
### Creating an executable
add_executable(minimal minimal.cpp)
target_link_libraries(minimal utils ${GL_LIBRARIES} ${APPLE_FRAMEWORKS} ${GLFW3_STATIC_LIBRARIES} ${ASSIMP_LIBRARIES})
