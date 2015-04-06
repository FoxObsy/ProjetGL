#include "../include/GameState.hpp"
using namespace std;

int main(int argc, char* argv[]){
	
GameState gameState = new GameState("../ressources/map1.txt");
OpenGLView openGLView = new OpenGLView(gameState.getMatrix());
int event;
// 1 pour haut, 2 pour bas, 3 pour droite, 4 pour gauche, 5 pour echap, 6 pour aide, 7 pour pause
while(!gameState.getEnd()){
	event = openGLView.getEvent();
	if (event > 0 && event < 5){
	gameState.event(event);
	openGLView.update(gameState);
	}


}
return 0;

}
