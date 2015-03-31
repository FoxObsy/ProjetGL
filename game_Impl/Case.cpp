#include "Case.hh"
#include <stdio>

use namespace std;


// side : coté ou se situe le personnage par rapport à la case
public bool Case::isAccessibleFrom(enum side) {
  if (this.isBorder() ) { setInaccessible(); }
  else {
    if (this.hasBox()) {
      switch (side) {
      
      case LEFT :
	if (this->rightCase.hasBox() || this->rightCase.isBorder()) {
	  setAccessible();
	}
	break;
	
      case RIGHT :
	


      }
	
    }
  }

  return _accessible;
}
