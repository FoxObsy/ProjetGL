#include "Controls.hpp"
#include "Player.hpp"


/* --- Constructeur --- */
public Player::Player(int x, int y) : _x(x), _y(y)
{}



/* --- Getters / Setters --- */

public void Player::up() {
  Controls::up();
  _x=Controls::getX();
  _y=Controls::getY();
}

public void Player::down() {
  Controls::down();
  _x=Controls::getX();
  _y=Controls::getY();
}

public void Player::left() {
  Controls::left();
  _x=Controls::getX();
  _y=Controls::getY();
}

public void Player::right() {
  Controls::right();
  _x=Controls::getX();
  _y=Controls::getY();
}
