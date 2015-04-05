#include "Tile.hh"
#include <iostream>

using namespace std;


// Setters et getters tile Up,left,right,down
// ------------------------------------------

// UP
void Tile::setTileUp(const Tile & t) {
  _tileUp = t;
}
Tile Tile::tileUp() {
  return _tileUp;
}

// DOWN
void Tile::setTileDown(const Tile & t) {
  _tileDown = t;
}
Tile Tile::tileDown() {
  return _tileDown;
}

// LEFT
void Tile::setTileLeft(const Tile & t) {
  _tileLeft = t;
}
Tile Tile::tileLeft() {
  return _tileLeft;
}

// RIGHT
void Tile::setTileRight(const Tile & t) {
  _tileRight = t;
}
Tile Tile::tileRight() {
  return _tileRight;
}

/* --------------------------------------- */


// Constructeur
Tile::Tile() : _isEmpty(true), _isBorder(false), _hasPlayer(false), _isTarget(false), _hasBox(false), _isReachable(true)
{}





// Setters / Getters
// -----------------

// empty?
void Tile::setEmpty(bool b) {
  _isEmpty = b;
}
bool Tile::isEmpty(bool b) {
  return _isEmpty;
}

// Border
void Tile::setBorder(bool b) {
  _isBorder = b;
}
bool Tile::isBorder() {
  return _isBorder;
}

// Target
void Tile::setTarget(bool b) {
  _isTarget = b;
}
bool Tile::hasTarget() {
  return _hasTarget;
}

// Player
void Tile::setPlayer(bool b) {
  _hasPlayer = b;
}
bool Tile::hasPlayer() {
  return _hasPlayer;
}

// Box
void Tile::setBox(bool b) {
  _hasBox = b;
}	   
bool Tile::hasBox() {
  return _hasBox;
}


/* ----- Accessibilité ----- */
/* _________________________ */

void Tile::setReachable() {
  _accessible=true;
}	
void Tile::setUnreachable() {
  _accessible=false;
}

bool Tile::isReachable() {
  return _accessible;
}

// side : coté ou se situe le personnage par rapport à la case
bool Tile::isReachableFrom(Tile::Side side) {

  if (this.isBorder() ) { setUnreachable(); }

  else {

    if (this.hasBox()) {
      
      switch (side) {
      
      case LEFT :
	if (this->tileRight().hasBox() || this->tileRight().isBorder()) {
	  setUnreachable();
	}
	break;
	
      case RIGHT :
	if (this->tileLeft().hasBox() || this->tileLeft().isBorder()) {
	  setUnreachable();
	}
	break;

      case UP :
	if (this->tileDown().hasBox() || this->tileDown().isBorder()) {
	  setUnreachable();
	}
	break;
	
      case DOWN :
	if (this->tileUp().hasBox() || this->tileUp().isBorder()) {
	  setUnreachable();
	}
	break;

      } // end switch
    } // end if
  } // end else

  return isReachable();
}





