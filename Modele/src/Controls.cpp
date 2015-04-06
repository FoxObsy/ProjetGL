
#include "../include/Controls.hpp"

Controls::Controls(int x, int y) : _x(x), _y(y)
{}



int Controls::getX() { return _x; }
int Controls::getY() { return _y; }
void Controls::setX(int x){ _x=x; }
void Controls::setY(int y){ _y=y; }



void Controls::up() {
  _y++;
}

void Controls::down() {
  _y--;
}

void Controls::left() {
  _x--;
}

void Controls::right() {
  _x++;
}
