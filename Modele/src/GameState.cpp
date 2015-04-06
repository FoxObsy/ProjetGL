/**
*	@title Boucle de jeu
*	@author Romain Tourrel
*/
#include "../include/GameState.hpp"
using namespace std;

void event(int move){
	    if(move == 1){
			if(matrix[player.getX()][player.getY()+1].isEmpty()){
				matrix[player.getX()][player.getY()].setEmpty(true);
				matrix[player.getX()][player.getY()].setPlayer(false);
				player.up();
				matrix[player.getX()][player.getY()].setEmpty(false);
				matrix[player.getX()][player.getY()].setPlayer(true);
			}
			else{
				if(matrix[player.getX()][player.getY()+1].hasBox()){
					if(matrix[player.getX()][player.getY()+1].isReachableFrom(Tile::Side::UP)){
						if(matrix[player.getX()][player.getY()+1].hasTarget(){
							nbr_target_free ++;
						}
						matrix[player.getX()][player.getY()].setEmpty(true);
						matrix[player.getX()][player.getY()].setPlayer(false);
						player.up();
						matrix[player.getX()][player.getY()].setEmpty(false);
						matrix[player.getX()][player.getY()].setPlayer(true);
						matrix[player.getX()][player.getY()+1].setEmpty(false);
						matrix[player.getX()][player.getY()+1].setBox(true);
						if(matrix[player.getX()][player.getY()+1].hasTarget()){
							nbr_target_free --;
						}
					}
				}
			}
		}

		//if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
		  if(move == 2){
			if(matrix[player.getX()][player.getY()-1].isEmpty()) {
				matrix[player.getX()][player.getY()].setEmpty(true);
				matrix[player.getX()][player.getY()].setPlayer(false);
				player.down();
				matrix[player.getX()][player.getY()].setEmpty(false);
				matrix[player.getX()][player.getY()].setPlayer(true);
			}
			else{
				if(matrix[player.getX()][player.getY()-1].hasBox()){
					if(matrix[player.getX()][player.getY()-1].isReachableFrom(Tile::Side::DOWN)){
						matrix[player.getX()][player.getY()].setEmpty(true);
						matrix[player.getX()][player.getY()].setPlayer(false);
						player.down();
						matrix[player.getX()][player.getY()].setEmpty(false);
						matrix[player.getX()][player.getY()].setPlayer(true);
						matrix[player.getX()][player.getY()-1].setEmpty(false);
						matrix[player.getX()][player.getY()-1].setBox(true);
						if(matrix[player.getX()][player.getY()-1].hasTarget()){
							nbr_target_free --;
						}
					}
				}
				
			}
		}

		//if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
		 if(move == 3){
			if(matrix[player.getX()+1][player.getY()].isEmpty()){
				matrix[player.getX()][player.getY()].setEmpty(true);
				matrix[player.getX()][player.getY()].setPlayer(false);
				player.right();
				matrix[player.getX()][player.getY()].setEmpty(false);
				matrix[player.getX()][player.getY()].setPlayer(true);
			}
			else{
				if(matrix[player.getX()+1][player.getY()].hasBox()){
					if(matrix[player.getX()+1][player.getY()].isReachableFrom(Tile::Side::RIGHT)){
						matrix[player.getX()][player.getY()].setEmpty(true);
						matrix[player.getX()][player.getY()].setPlayer(false);
						player.right();
						matrix[player.getX()][player.getY()].setEmpty(false);
						matrix[player.getX()][player.getY()].setPlayer(true);
						matrix[player.getX()+1][player.getY()].setEmpty(false);
						matrix[player.getX()+1][player.getY()].setBox(true);
						if(matrix[player.getX()+1][player.getY()].hasTarget()){
							nbr_target_free --;
						}
					}
				}
			}
				
			}
		}

		//if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
		  if(move == 4){	
			if(matrix[player.getX()-1][player.getY()].isEmpty()){
				matrix[player.getX()][player.getY()].setEmpty(true);
				matrix[player.getX()][player.getY()].setPlayer(false);	
				player.left();
				matrix[player.getX()][player.getY()].setEmpty(false);
				matrix[player.getX()][player.getY()].setPlayer(true);
			}
			else{
				if(matrix[player.getX()-1][player.getY()].hasBox()){
					if(matrix[player.getX()-1][player.getY()].isReachableFrom(Tile::Side::LEFT))
						matrix[player.getX()][player.getY()].setEmpty(true);
						matrix[player.getX()][player.getY()].setPlayer(false);	
						player.left();
						matrix[player.getX()][player.getY()].setEmpty(false);
						matrix[player.getX()][player.getY()].setPlayer(true);
						matrix[player.getX()-1][player.getY()].setEmpty(false);
						matrix[player.getX()-1][player.getY()].setBox(true);
						if(matrix[player.getX()-1][player.getY()].hasTarget()){
							nbr_target_free --;
						}
				}
				
			}
		}

		if (nbr_target_free == 0){
			end = true;
		}
}

bool getEnd(){
	return end;
}

Matrix getMatrix(){
	return matrix;
}

int getNbrTargetFree(){
	return nbt_target_free;
}
// Constructeur
GameState::GameState(String file)
{
	matrix = new Matrix(file);
	player = new Player(matrix.getPositionPlayerX(),matrix.getPositionPlayerY());
	nbr_target_free = matrix.getNbrTargetFree();
	end = false;
}

