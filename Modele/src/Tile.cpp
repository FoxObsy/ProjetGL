#include "../include/Tile.hpp"
#include <iostream>

using namespace std;


// Setters et getters tile Up,left,right,down
// ------------------------------------------

// UP
void Tile::setTileUp(Tile* t){
  _tileUp = t;
}
Tile* Tile::tileUp(){
  return _tileUp;
}

// DOWN
void Tile::setTileDown(Tile* t) {
  _tileDown = t;
}
Tile* Tile::tileDown() {
  return _tileDown;
}

// LEFT
void Tile::setTileLeft(Tile* t) {
  _tileLeft = t;
}
Tile* Tile::tileLeft() {
  return _tileLeft;
}

// RIGHT
void Tile::setTileRight(Tile* t) {
  _tileRight = t;
}
Tile* Tile::tileRight() {
  return _tileRight;
}

/* --------------------------------------- */


// Constructeur
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
{}





// Setters / Getters
// -----------------

// empty?
void Tile::setEmpty(bool b) {
  _isEmpty = b;
  if (b==true) { setReachable(); } // inutile
}
bool Tile::isEmpty() {
  return _isEmpty;
}

// Border
void Tile::setBorder(bool b) {
  _isBorder = b;
  _isReachable = !b; // inutile
  _isEmpty = !b;
}
bool Tile::isBorder() {
  return _isBorder;
}

// Target
void Tile::setTarget(bool b) {
  _hasTarget = b;
}
bool Tile::hasTarget() {
  return _hasTarget;
}

// Player
void Tile::setPlayer(bool b) {
  _hasPlayer = b;
  _isEmpty = !b;
}
bool Tile::hasPlayer() {
  return _hasPlayer;
}

// Box
void Tile::setBox(bool b) {
  _hasBox = b;
  _isEmpty = !b;
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
  cout << "Side = " << side <<endl;
  cout << "=> Case atteignable?" << endl;
  if (isBorder() ) { 
    // setUnreachable();
    cout << "    NON ! Il y a un bord !" << endl;
    return false;
  }

  else {

    if (hasBox()) {
      
    cout << "    Attention, caisse !" << endl;
      switch (side) {
      cout << "side?" << endl;
      case LEFT :
      cout << "possible par la gauche?" << endl;
	if (tileRight()->hasBox() || tileRight()->isBorder()) {
    cout << "       Impossible par la gauche ! " << endl;
	  // setUnreachable();
	  return false;
	}
	break;
	
      case RIGHT :
      cout << "possible par la droite?" << endl;
	if (tileLeft()->hasBox() || tileLeft()->isBorder()) {

    cout << "       Impossible par la droite !" << endl;
	  // setUnreachable();
	  return false;
	}
	break;

      case UP :
      cout << "possible par le haut?" << endl;
	if (tileDown()->hasBox() || tileDown()->isBorder()) {
    cout << "       Impossible par le haut !" << endl;
    // setUnreachable();
	  return false;
	}
	break;
	
      case DOWN :
      cout << "possible par le bas?" << endl;
	if (tileUp()->hasBox() || tileUp()->isBorder()) {
    cout << "       Impossible par le bas !" << endl;
	  // setUnreachable();
	  return false;
	}
	break;

      } // end switch
    } // end if
  } // end else

    cout << " OUI !" << endl;
  return true; // isReachable();
}

