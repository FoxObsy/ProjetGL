#ifndef CONTROLS_H
#define CONTROLS_H

#include "include/GameState.hpp"

glm::mat4 computeMatricesFromInputs(GLFWwindow* window);
glm::mat4 moveRobot(GLFWwindow* window, GameState &gameState, glm::mat4 ModelMatrixRobot, int &moves);

#endif

