#include "../include/GameState.hpp"
using namespace std;

int main(int argc, char* argv[]){
	
GameState gameState = new GameState("../ressources/map1.txt");
OpenGLView openGLView = new OpenGLView(gameState.getMatrix());
int event;
// 1 pour haut, 2 pour bas, 3 pour droite, 4 pour gauche
while(!gameState.getEnd()){
	event = openGLView.getEvent();
	gameState.event(event);
	openGLView.update(gameState);
}







return 0;

}
