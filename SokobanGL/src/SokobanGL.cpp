using namespace std;

int main(int argc, char* argv[]){

	/* Initialisation de la partie */
	
	Matrice matrice = new Matrice(10,10);
	Joueur joueur = new Personnage(0,2);
	int nbr_cible = matrice.getNbrCible();

	GLFWwindow* window = glfwGetCurrentContext();
  	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	boolean fin = false;
	while(!fin){
		if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			if(matrice[joueur.getX()][joueur.getY()+1].isAccessible()){
			joueur.up();
			}
		}

		if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			if(matrice[joueur.getX()][joueur.getY()-1].isAccessible()) {
			joueur.down();
			}
		}

		if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			if(matrice[joueur.getX()+1][joueur.getY()].isAccessible()){
			joueur.right();
			}
		}

		if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			if(matrice[joueur.getX()-1][joueur.getY()+1].isAccessible()){
			joueur.left();
			}
		}
	}

return 0;
}