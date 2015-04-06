#include "../include/Tile.hpp"
#include <iostream>

using namespace std;


// Setters et getters tile Up,left,right,down
// ------------------------------------------

// UP
<<<<<<< HEAD
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
=======
void Tile::setTileUp(Tile & t) {
  _tileUp = &t;
}
Tile & Tile::tileUp() {
  return *_tileUp;
}

// DOWN
void Tile::setTileDown(Tile & t) {
  _tileDown = &t;
}
Tile & Tile::tileDown() {
  return *_tileDown;
}

// LEFT
void Tile::setTileLeft(Tile & t) {
  _tileLeft = &t;
}
Tile & Tile::tileLeft() {
  return *_tileLeft;
}

// RIGHT
void Tile::setTileRight(Tile & t) {
  _tileRight = &t;
}
Tile & Tile::tileRight() {
  return *_tileRight;
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc
}

/* --------------------------------------- */


// Constructeur
<<<<<<< HEAD
Tile::Tile() : _isEmpty(true), _isBorder(false), _hasPlayer(false), _isTarget(false), _hasBox(false), _isReachable(true)
=======
Tile::Tile() : _isEmpty(true), 
	       _isBorder(false), 
	       _hasPlayer(false), 
	       _hasTarget(false), 
	       _hasBox(false), 
	       _isReachable(true), // inutile
	       _tileUp(0),
	       _tileDown(0),
	       _tileLeft(0),
	       _tileRight(0)	       
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc
{}





// Setters / Getters
// -----------------

// empty?
void Tile::setEmpty(bool b) {
  _isEmpty = b;
  if (b==true) { setReachable(); } // inutile
}
<<<<<<< HEAD
bool Tile::isEmpty(bool b) {
=======
bool Tile::isEmpty() {
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc
  return _isEmpty;
}

// Border
void Tile::setBorder(bool b) {
  _isBorder = b;
  _isReachable = !b; // inutile
}
bool Tile::isBorder() {
  return _isBorder;
}

// Target
void Tile::setTarget(bool b) {
<<<<<<< HEAD
  _isTarget = b;
=======
  _hasTarget = b;
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc
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


/* Méthodes inutiles, seule isReachableFrom est utilisée */

void Tile::setReachable() {
  _isReachable=true;
}	
void Tile::setUnreachable() {
  _isReachable=false;
}

bool Tile::isReachable() {
  return _isReachable;
}
/* ----------------------------------------------------- */


// side : coté ou se situe le personnage par rapport à la case
bool Tile::isReachableFrom(Tile::Side side) {

<<<<<<< HEAD
  if (this.isBorder() ) { 
=======
  if (isBorder() ) { 
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc
    // setUnreachable(); 
    return false;
  }

  else {

<<<<<<< HEAD
    if (this.hasBox()) {
=======
    if (hasBox()) {
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc
      
      switch (side) {
      
      case LEFT :
	if (this->tileRight().hasBox() || this->tileRight().isBorder()) {
	  // setUnreachable();
	  return false;
	}
	break;
	
      case RIGHT :
	if (this->tileLeft().hasBox() || this->tileLeft().isBorder()) {
	  // setUnreachable();
	  return false;
	}
	break;

      case UP :
	if (this->tileDown().hasBox() || this->tileDown().isBorder()) {
	  // setUnreachable();
	  return false;
	}
	break;
	
      case DOWN :
	if (this->tileUp().hasBox() || this->tileUp().isBorder()) {
	  // setUnreachable();
	  return false;
	}
	break;

      } // end switch
    } // end if
  } // end else

  return true; // isReachable();
}





