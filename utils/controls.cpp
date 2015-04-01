#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "controls.h"

#define PI glm::pi<float>()

char keyOnce[GLFW_KEY_LAST + 1];
#define glfwGetKeyOnce(WINDOW, KEY)             \
    (glfwGetKey(WINDOW, KEY) ?              \
     (keyOnce[KEY] ? false : (keyOnce[KEY] = true)) :   \
     (keyOnce[KEY] = false))

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


int direction = 0; //0->haut 1->gauche 2->bas 3->droite
glm::vec3 rot, transl;

glm::mat4 moveRobot(GLFWwindow* window, glm::mat4 ModelMatrixRobot){

  if(glfwGetKeyOnce(window, GLFW_KEY_W) == GLFW_PRESS){ //Haut;
    switch(direction){
    case 0: //haut
      rot = glm::vec3(0.0f);
      transl = glm::vec3(-1.0f,0.0f,0.0f);
      break;
    case 1: //gauche
      rot = glm::vec3(0.0f,-PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,-1.0f);
      break;
    case 2: //bas
      rot = glm::vec3(0.0f,PI,0.0f);
      transl = glm::vec3(1.0f,0.0f,0.0f);
      break;
    case 3: //droite
      rot = glm::vec3(0.0f,PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,1.0f);
      break;
    }
    direction = 0;
    ModelMatrixRobot = glm::translate(ModelMatrixRobot, transl) * glm::toMat4(glm::quat(rot));
  }

  if(glfwGetKeyOnce(window, GLFW_KEY_A) == GLFW_PRESS){ //Gauche
    switch(direction){
    case 0: //haut
      rot = glm::vec3(0.0f,PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,1.0f);
      break;
    case 1: //gauche
      rot = glm::vec3(0.0f);
      transl = glm::vec3(-1.0f,0.0f,0.0f);
      break;
    case 2: //bas
      rot = glm::vec3(0.0f,-PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,-1.0f);
      break;
    case 3: //droite
      rot = glm::vec3(0.0f,PI,0.0f);
      transl = glm::vec3(1.0f,0.0f,0.0f);
      break;
    }
    direction = 1;
    ModelMatrixRobot = glm::translate(ModelMatrixRobot, transl) * glm::toMat4(glm::quat(rot));
  }

  if(glfwGetKeyOnce(window, GLFW_KEY_S) == GLFW_PRESS){ //Bas
    switch(direction){
    case 0: //haut
      rot = glm::vec3(0.0f,PI,0.0f);
      transl = glm::vec3(1.0f,0.0f,0.0f);
      break;
    case 1: //gauche
      rot = glm::vec3(0.0f,PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,1.0f);
      break;
    case 2: //bas
      rot = glm::vec3(0.0f);
      transl = glm::vec3(-1.0f,0.0f,0.0f);
      break;
    case 3: //droite
      rot = glm::vec3(0.0f,-PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,-1.0f);
      break;
    }
    direction = 2;
    ModelMatrixRobot = glm::translate(ModelMatrixRobot, transl) * glm::toMat4(glm::quat(rot));
  }

  if(glfwGetKeyOnce(window, GLFW_KEY_D) == GLFW_PRESS){ //Droite
    switch(direction){
    case 0: //haut
      rot = glm::vec3(0.0f,-PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,-1.0f);
      break;
    case 1: //gauche
      rot = glm::vec3(0.0f,PI,0.0f);
      transl = glm::vec3(1.0f,0.0f,0.0f);
      break;
    case 2: //bas
      rot = glm::vec3(0.0f,PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,1.0f);
      break;
    case 3: //droite
      rot = glm::vec3(0.0f);
      transl = glm::vec3(-1.0f,0.0f,0.0f);
      break;
    }
    direction = 3;
    ModelMatrixRobot = glm::translate(ModelMatrixRobot, transl) * glm::toMat4(glm::quat(rot));
  }

  if(glfwGetKeyOnce(window, GLFW_KEY_F) == GLFW_PRESS){
    ModelMatrixRobot = glm::translate(ModelMatrixRobot, glm::vec3(0.0f,1.0f,0.0f));
  }

  if(glfwGetKeyOnce(window, GLFW_KEY_R) == GLFW_PRESS){
    ModelMatrixRobot = glm::translate(ModelMatrixRobot, glm::vec3(0.0f,-1.0f,0.0f));
  }

  return ModelMatrixRobot;
}
