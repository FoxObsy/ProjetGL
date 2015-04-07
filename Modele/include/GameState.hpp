#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Matrix.hpp"
#include "Player.hpp"
#include "Tile.hpp"

class GameState{

private:	
  Matrix matrix;
  Player player;
  int nbr_target_free;
  bool end;

public:
  GameState(std::string file);
  void event(int move);
  bool getEnd();
  Matrix getMatrix();
  void initNbrTargetFree();

};

#endif
