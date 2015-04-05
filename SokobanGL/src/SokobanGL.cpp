/**
*	@title Boucle de jeu
*	@author Romain Tourrel
*/

using namespace std;

int main(int argc, char* argv[]){

	/* Initialisation de la partie */
	
	Matrix matrix = new Matrix(10,10);
	Player player = new Personnage(0,2);
	int nbr_target_free = matrice.getNbrTargetFree();

	GLFWwindow* window = glfwGetCurrentContext();
  	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	boolean end = false;
	while(!end){
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			if(matrix[player.getX()][player.getY()+1].isEmpty()){
				matrix[player.getX()][player.getY()].setEmpty(true);
				matrix[player.getX()][player.getY()].setPlayer(false);
				player.up();
				matrix[player.getX()][player.getY()].setEmpty(false);
				matrix[player.getX()][player.getY()].setPlayer(true);
			}
			else{
				if(matrix[player.getX()][player.getY()+1].hasBox()){
					if(matrix[player.getX()][player.getY()+1].isAccessibleFrom(side::UP)){
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

		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			if(matrice[player.getX()][player.getY()-1].isEmpty()) {
				matrix[player.getX()][player.getY()].setEmpty(true);
				matrix[player.getX()][player.getY()].setPlayer(false);
				player.down();
				matrix[player.getX()][player.getY()].setEmpty(false);
				matrix[player.getX()][player.getY()].setPlayer(true);
			}
			else{
				if(matrix[player.getX()][player.getY()-1].hasBox()){
					if(matrix[player.getX()][player.getY()-1].isAccessibleFrom(side::DOWN)){
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

		if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			if(matrice[player.getX()+1][player.getY()].isEmpty()){
				matrix[player.getX()][player.getY()].setEmpty(true);
				matrix[player.getX()][player.getY()].setPlayer(false);
				player.right();
				matrix[player.getX()][player.getY()].setEmpty(false);
				matrix[player.getX()][player.getY()].setPlayer(true);
			}
			else{
				if(matrix[player.getX()+1][player.getY()].hasBox()){
					if(matrix[player.getX()+1][player.getY()].isAccessibleFrom(side::RIGHT)){
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

		if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			if(matrice[player.getX()-1][player.getY()].isEmpty()){
				matrix[player.getX()][player.getY()].setEmpty(true);
				matrix[player.getX()][player.getY()].setPlayer(false);	
				player.left();
				matrix[player.getX()][player.getY()].setEmpty(false);
				matrix[player.getX()][player.getY()].setPlayer(true);
			}
			else{
				if(matrix[player.getX()-1][player.getY()].hasBox()){
					if(matrix[player.getX()-1][player.getY()].isAccessibleFrom(side::LEFT))
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

return 0;
}