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

#include <irrKlang.h>
#include "controls.h"

#include "include/GameState.hpp"

#define PI glm::pi<float>()

char keyOnce[GLFW_KEY_LAST + 1];
#define glfwGetKeyOnce(WINDOW, KEY)			\
  (glfwGetKey(WINDOW, KEY) ?				\
   (keyOnce[KEY] ? false : (keyOnce[KEY] = true)) :	\
   (keyOnce[KEY] = false))

using namespace irrklang;

float radius = 10.0f;
float speed = 0.05f;
float horizontalAngle = -PI/2;
float verticalAngle = PI/2 - speed;

glm::mat4 computeMatricesFromInputs(GLFWwindow* window){
  
  // Controls
  if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
    if(verticalAngle < PI/2 - speed) 
      verticalAngle += speed;
  }
  if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
    if(verticalAngle > 0.0f) 
      verticalAngle -= speed;
  }
  if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
    horizontalAngle += speed;
  }
  if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
    horizontalAngle -= speed;
  }

  glm::vec3 position = glm::vec3(radius * sin(horizontalAngle) * cos(verticalAngle),
				 radius * sin(verticalAngle),
				 radius * cos(horizontalAngle) * cos(verticalAngle));

  // Camera matrix
  glm::mat4 View = glm::lookAt(
			       position+glm::vec3(0,1,0),
			       glm::vec3(0,0,0), 
			       glm::vec3(0,1,0)
			       );

  return View;
}


int direction = 1; //1->haut 2->bas 3->droite 4->gauche 
glm::vec3 rot, transl;
glm::vec3 postion = glm::vec3(0.0f);

glm::mat4 moveRobot(GLFWwindow* window, GameState &gameState, glm::mat4 ModelMatrixRobot, int &moves,ISoundEngine* engine, ISoundSource* caisse, ISoundSource* pas){
  int sound;
  int* oldPosition = gameState.getMatrix().getPositionPlayer();
  if(glfwGetKeyOnce(window, GLFW_KEY_DOWN) == GLFW_PRESS){
    switch(direction){
    case 1: //haut
      rot = glm::vec3(0.0f);
      transl = glm::vec3(-1.0f,0.0f,0.0f);
      break;
    case 4: //gauche
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
    direction = 1;
    moves++;
    sound = gameState.event(1);
    int* newPosition = gameState.getMatrix().getPositionPlayer();
    std::cout << newPosition[0] << " - " << newPosition[1] << std::endl;
    std::cout << oldPosition[0] << " - " << oldPosition[1] << std::endl;
    if(newPosition[0] - oldPosition[0] || newPosition[1] - oldPosition[1]){
      ModelMatrixRobot = glm::translate(ModelMatrixRobot, transl) * glm::toMat4(glm::quat(rot));
    }
    else{
      ModelMatrixRobot = ModelMatrixRobot * glm::toMat4(glm::quat(rot));
    }
    gameState.getMatrix().AffMatrix();
  }

  if(glfwGetKeyOnce(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
    switch(direction){
    case 1: //haut
      rot = glm::vec3(0.0f,PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,1.0f);
      break;
    case 4: //gauche
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
    direction = 4;
    moves++;
    sound = gameState.event(4);
    int* newPosition = gameState.getMatrix().getPositionPlayer();
    std::cout << newPosition[0] << " - " << newPosition[1] << std::endl;
    std::cout << oldPosition[0] << " - " << oldPosition[1] << std::endl;
    if(newPosition[0] - oldPosition[0] || newPosition[1] - oldPosition[1]){
      ModelMatrixRobot = glm::translate(ModelMatrixRobot, transl) * glm::toMat4(glm::quat(rot));
    }
    else{
      ModelMatrixRobot = ModelMatrixRobot * glm::toMat4(glm::quat(rot));
    }
    gameState.getMatrix().AffMatrix();
  }

  if(glfwGetKeyOnce(window, GLFW_KEY_UP) == GLFW_PRESS){
    switch(direction){
    case 1: //haut
      rot = glm::vec3(0.0f,PI,0.0f);
      transl = glm::vec3(1.0f,0.0f,0.0f);
      break;
    case 4: //gauche
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
    moves++;
    sound = gameState.event(2);
    int* newPosition = gameState.getMatrix().getPositionPlayer();
    std::cout << newPosition[0] << " - " << newPosition[1] << std::endl;
    std::cout << oldPosition[0] << " - " << oldPosition[1] << std::endl;
    if(newPosition[0] - oldPosition[0] || newPosition[1] - oldPosition[1]){
      ModelMatrixRobot = glm::translate(ModelMatrixRobot, transl) * glm::toMat4(glm::quat(rot));
    }
    else{
      ModelMatrixRobot = ModelMatrixRobot * glm::toMat4(glm::quat(rot));
    }
    gameState.getMatrix().AffMatrix();
  }

  if(glfwGetKeyOnce(window, GLFW_KEY_LEFT) == GLFW_PRESS){
    switch(direction){
    case 1: //haut
      rot = glm::vec3(0.0f,-PI/2,0.0f);
      transl = glm::vec3(0.0f,0.0f,-1.0f);
      break;
    case 4: //gauche
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
    moves++;
    sound = gameState.event(3);
    int* newPosition = gameState.getMatrix().getPositionPlayer();
    std::cout << newPosition[0] << " - " << newPosition[1] << std::endl;
    std::cout << oldPosition[0] << " - " << oldPosition[1] << std::endl;
    if(newPosition[0] - oldPosition[0] || newPosition[1] - oldPosition[1]){
      ModelMatrixRobot = glm::translate(ModelMatrixRobot, transl) * glm::toMat4(glm::quat(rot));
    }
    else{
      ModelMatrixRobot = ModelMatrixRobot * glm::toMat4(glm::quat(rot));
    }
    gameState.getMatrix().AffMatrix();
  }
  /*
    if(glfwGetKeyOnce(window, GLFW_KEY_F) == GLFW_PRESS){
    ModelMatrixRobot = glm::translate(ModelMatrixRobot, glm::vec3(0.0f,1.0f,0.0f));
    }

    if(glfwGetKeyOnce(window, GLFW_KEY_R) == GLFW_PRESS){
    ModelMatrixRobot = glm::translate(ModelMatrixRobot, glm::vec3(0.0f,-1.0f,0.0f));
    }
  */
    if(sound == 1){
     engine->play2D(pas,false);
  }

  if(sound == 2){
     engine->play2D(caisse,false);
  }
  return ModelMatrixRobot;
}
