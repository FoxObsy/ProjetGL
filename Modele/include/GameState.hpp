#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Matrix.hpp"
#include "Player.hpp"

class GameState{
	Matrix matrix;
	Player player;
	int nbr_target_free;
	bool end;
};

GameState(String file);
void event(int move);
bool getEnd();
Matrix getMatrix();
int getNbrTargetFree();

#endif