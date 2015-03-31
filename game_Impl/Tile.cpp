#include "Tile.hh"
#include <iostream>

using namespace std;


// A FAIRE : Setters et getters tile Up,left,right,down




// Constructeur
Tile::Tile() : _isEmpty(true), _isBorder(false), _hasPlayer(false), _isTarget(false), _hasBox(false), _isAccessible(true)
{}





// Setters / Getters

// Box
void Tile::setBox(bool b) {
  _hasBox = b;
}	   
bool Tile::hasBox() {
  return _hasBox;
}

// Player
void Tile::setPlayer(bool b) {
  _hasPlayer = b;
}
bool Tile::hasPlayer() {
  return _hasPlayer;
}

// Target
void Tile::setTarget(bool b) {
  _isTarget = b;
}
bool Tile::hasTarget() {
  return _hasTarget;
}

// Border
void Tile::setBorder(bool b) {
  _isBorder = b;
}
bool Tile::isBorder() {
  return _isBorder;
}

// empty?
void Tile::setEmpty(bool b) {
  _isEmpty = b;
}
bool Tile::isEmpty(bool b) {
  return _isEmpty;
}



/* ----- Accessibilité ----- */
/* _________________________ */

bool Tile:setAccessible() {
  _accessible=true;
}	
bool Tile:setInaccessible() {
  _accessible=false;
}

bool Tile::isAccessible() {
  return _accessible;
}

// side : coté ou se situe le personnage par rapport à la case
bool Tile::isAccessibleFrom(enum side) {
  if (this.isBorder() ) { setInaccessible(); }
  else {
    if (this.hasBox()) {
      
      switch (side) {
      
      case LEFT :
	if (this->tileRight.hasBox() || this->tileRight.isBorder()) {
	  setInaccessible();
	}
	break;
	
      case RIGHT :
	if (this->tileLeft.hasBox() || this->tileLeft.isBorder()) {
	  setInaccessible();
	}
	break;

      case UP :
	if (this->tileDown.hasBox() || this->tileDown.isBorder()) {
	  setInaccessible();
	}
	break;
	
      case DOWN :
	if (this->tileUp.hasBox() || this->tileUp.isBorder()) {
	  setInaccessible();
	}
	break;

      } // end switch
    } // end if
  } // end else

  return isAccessible();
}





