#ifndef CONTROLS_H
#define CONTROLS_H

#include "include/GameState.hpp"
#include <irrKlang.h>

glm::mat4 computeMatricesFromInputs(GLFWwindow* window);
glm::mat4 moveRobot(GLFWwindow* window, GameState &gameState, glm::mat4 ModelMatrixRobot, int &moves, irrklang::ISoundEngine* engine,irrklang::ISoundSource* caisse, irrklang::ISoundSource* pas);
void initParameters();

#endif

