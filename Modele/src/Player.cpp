// #include "../include/Controls.hpp"
#include "../include/Player.hpp"


/* --- Constructeur --- */
Player::Player(int x, int y) : _x(x), _y(y), _moves(0)
{}



/* --- Getters / Setters --- */
int Player::getX() {
  return _x;
}
void Player::setX(int x) {
  _x = x;
}
int Player::getY() {
  return _y;
}
void Player::setY(int y) {
  _y = y;
}


int Player::getMoves() {
  return _moves;
}
void Player::incMoves() {
  _moves++;
}
void Player::resetMoves() {
  _moves = 0;
}

/* ------------------------- */

void Player::up() {
  _y++;
  /*
  _controls.up();
  _x = _controls.getX();
  _y = _controls.getY();
  */
}

void Player::down() {
  _y--;
  /*
  _controls.down();
  _x = _controls.getX();
  _y = _controls.getY();
  */
}

void Player::left() {
  _x--;
  /*
  _controls.left();
  _x = _controls.getX();
  _y = _controls.getY();
  */
}

void Player::right() {
  _x++;
  /*
  _controls.right();
  _x = _controls.getX();
  _y = _controls.getY();
  */
}
