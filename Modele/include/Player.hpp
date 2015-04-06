#ifndef PLAYER_H
#define PLAYER_H

// class Controls;


class Player {
  
private:
  int _x;
  int _y;
  int _moves;
  // Controls _controls;



public:

  // Constructeurs
  Player(int x=0, int y=0);

  /* --- Getters / Setters --- */

  // X
  int getX();
  void setX(int x);

  // Y
  int getY();
  void setY(int y);

  // Moves
  int getMoves();
  void incMoves();
  void resetMoves();
  
  /* ------------------------ */

  // Méthodes de déplacement
  void up();
  void down();
  void left();
  void right();
  
};

#endif
