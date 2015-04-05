
#include "Controls.hpp"



public Controles::Controles(int x, int y) : _x(x), _y(y)
{}



public int Controles::getX() { return _x; }
public int Controles::getY() { return _y; }
public void Controles::setX(int x){ _x=x; }
public void Controles::setY(int y){ _y=y; }



public void Controles::up() {
  _y++;
}

public void Controles::down() {
  _y--;
}

public void Controles::left() {
  _x--;
}

public void Controles::right() {
  _x++;
}
