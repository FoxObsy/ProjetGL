#include "../include/Controls.hpp"
#include "../include/Player.hpp"


/* --- Constructeur --- */
Player::Player(int x, int y) : _x(x), _y(y)
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


void Player::up() {
  Controls::up();
  _x=Controls::getX();
  _y=Controls::getY();
}

void Player::down() {
  Controls::down();
  _x=Controls::getX();
  _y=Controls::getY();
}

void Player::left() {
  Controls::left();
  _x=Controls::getX();
  _y=Controls::getY();
}

void Player::right() {
  Controls::right();
  _x=Controls::getX();
  _y=Controls::getY();
}
