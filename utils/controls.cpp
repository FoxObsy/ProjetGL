#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "controls.h"

#define PI glm::pi<float>()

float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;
float radius = 10.0f;
float speed = 0.05f;

glm::mat4 computeMatricesFromInputs(GLFWwindow* window){
  
  // Controls
  if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
    if(verticalAngle < PI/2 - speed) 
      verticalAngle += speed;
  }
  if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
    if(verticalAngle > 0.0f) 
      verticalAngle -= speed;
  }
  if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
    horizontalAngle += speed;
  }
  if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
    horizontalAngle -= speed;
  }

  glm::vec3 position = glm::vec3(radius * sin(horizontalAngle) * cos(verticalAngle),
				 radius * sin(verticalAngle),
				 radius * cos(horizontalAngle) * cos(verticalAngle));

  // Camera matrix
  glm::mat4 View = glm::lookAt(
			       position,
			       glm::vec3(0,0,0), 
			       glm::vec3(0,1,0)
			       );

  return View;
}
