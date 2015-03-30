
### Creating an executable
add_executable(TP0 glfwMinimal.cpp)
target_link_libraries(TP0 utils ${GL_LIBRARIES} ${APPLE_FRAMEWORKS}  ${GLFW3_STATIC_LIBRARIES} ${ASSIMP_LIBRARIES})
