/**
 *	@title Boucle de jeu
 *	@author Romain Tourrel
 */
#include "../include/GameState.hpp"
using namespace std;

void GameState::event(int move){
  if(move == 1){
    if(((matrix.getMatrix())[player.getX()][player.getY()+1]).isEmpty()){
      ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(true);
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
      player.up();
      ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(false);
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
      player.incMoves();
    }
    else{
      if(((matrix.getMatrix())[player.getX()][player.getY()+1]).hasBox()){
	if(((matrix.getMatrix())[player.getX()][player.getY()+1]).isReachableFrom(Tile::Side::UP)){
	  if(((matrix.getMatrix())[player.getX()][player.getY()+1]).hasTarget()){
	    nbr_target_free ++;
	  }
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(true);
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
	  player.up();
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(false);
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
    ((matrix.getMatrix())[player.getX()][player.getY()]).setBox(false);
	  ((matrix.getMatrix())[player.getX()][player.getY()+1]).setEmpty(false);
	  ((matrix.getMatrix())[player.getX()][player.getY()+1]).setBox(true);
	  player.incMoves();
	  if(((matrix.getMatrix())[player.getX()][player.getY()+1]).hasTarget()){
	    nbr_target_free --;
	  }
	}
      }
    }
  }

  //if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
  if(move == 2){
    if(((matrix.getMatrix())[player.getX()][player.getY()-1]).isEmpty()) {
      ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(true);
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
      player.down();
      ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(false);
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
      player.incMoves();
    }
    else{
      if(((matrix.getMatrix())[player.getX()][player.getY()-1]).hasBox()){
	if(((matrix.getMatrix())[player.getX()][player.getY()-1]).isReachableFrom(Tile::Side::DOWN)){
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(true);
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
	  player.down();
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(false);
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
    ((matrix.getMatrix())[player.getX()][player.getY()]).setBox(false);
	  ((matrix.getMatrix())[player.getX()][player.getY()-1]).setEmpty(false);
	  ((matrix.getMatrix())[player.getX()][player.getY()-1]).setBox(true);
	  player.incMoves();
	  if(((matrix.getMatrix())[player.getX()][player.getY()-1]).hasTarget()){
	    nbr_target_free --;
	  }
	}
      }
				
    }
  }

  //if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
  if(move == 3){
    if(((matrix.getMatrix())[player.getX()+1][player.getY()]).isEmpty()){
      ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(true);
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
      player.right();
      ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(false);
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);

      player.incMoves();
    }
    else{
      if(((matrix.getMatrix())[player.getX()+1][player.getY()]).hasBox()){
	if(((matrix.getMatrix())[player.getX()+1][player.getY()]).isReachableFrom(Tile::Side::RIGHT)){
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(true);
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
	  player.right();
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(false);
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
    ((matrix.getMatrix())[player.getX()][player.getY()]).setBox(false);
	  ((matrix.getMatrix())[player.getX()+1][player.getY()]).setEmpty(false);
	  ((matrix.getMatrix())[player.getX()+1][player.getY()]).setBox(true);
	  player.incMoves();
	  if(((matrix.getMatrix())[player.getX()+1][player.getY()]).hasTarget()){
	    nbr_target_free --;
	  }
	}
      }
    }
				
  }


  //if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
  if(move == 4){	
    if(((matrix.getMatrix())[player.getX()-1][player.getY()]).isEmpty()){
      ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(true);
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);	
      player.left();
      ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(false);
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
      player.incMoves();
    }
    else{
      if(((matrix.getMatrix())[player.getX()-1][player.getY()]).hasBox()){
	if(((matrix.getMatrix())[player.getX()-1][player.getY()]).isReachableFrom(Tile::Side::LEFT))
	  ((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(true);
	((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);	
	player.left();
	((matrix.getMatrix())[player.getX()][player.getY()]).setEmpty(false);
	((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
  ((matrix.getMatrix())[player.getX()][player.getY()]).setBox(false);
	((matrix.getMatrix())[player.getX()-1][player.getY()]).setEmpty(false);
	((matrix.getMatrix())[player.getX()-1][player.getY()]).setBox(true);
	player.incMoves();
	if(((matrix.getMatrix())[player.getX()-1][player.getY()]).hasTarget()){
	  nbr_target_free --;
	}
      }
				
    }
  }

  if (nbr_target_free == 0){
    end = true;
  }
}

bool GameState::getEnd(){
  return end;
}

Matrix GameState::getMatrix(){
  return matrix;
}

void GameState::initNbrTargetFree(){
  int nb;
  for(int i = 0; i<matrix.getRow();i++){
    for(int j = 0; j<matrix.getColumn();j++){
      if(matrix.getMatrix()[i][j].hasTarget() && !matrix.getMatrix()[i][j].hasBox()){
	nbr_target_free++;
      }
    }
  }
}
// Constructeur
GameState::GameState(string file)
{
  matrix.setMap(file);
  int * positionPlayer = matrix.getPositionPlayer();
  player.setX(positionPlayer[0]);
  player.setY(positionPlayer[1]);
  nbr_target_free = 0;
  initNbrTargetFree();
  end = false;
}

