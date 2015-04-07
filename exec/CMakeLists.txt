
### Creating an executable
add_executable(myproject myproject.cpp)
target_link_libraries(myproject utils ${GL_LIBRARIES} ${APPLE_FRAMEWORKS}  ${GLFW3_STATIC_LIBRARIES} ${ASSIMP_LIBRARIES})
