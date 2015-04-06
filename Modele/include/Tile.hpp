#ifndef TILE_H
#define TILE_H

class Tile {

  bool _isEmpty;
  bool _isBorder;
<<<<<<< HEAD
  bool _isTarget;
=======
  bool _hasTarget;
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc
  bool _hasPlayer;
  bool _hasBox;
  bool _isReachable; // avérée inutile

<<<<<<< HEAD
  Tile & tileUp;
  Tile & tileDown;
  Tile & tileLeft;
  Tile & tileRight;
=======
  Tile* _tileUp;
  Tile* _tileDown;
  Tile* _tileLeft;
  Tile* _tileRight;
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc
  


public:

  enum Side
    {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };

  // Pour le constructeur, 
  //permet d'ajouter des options pour la création.
  /* Avéré inutile car matrice créée avec des Tile() car
     Les seules infos disponibles sont le nb de lignes et col au début. */
  /*
  enum Option
    {
      WITH_PLAYER,
      WITH_TARGET,
      WITH_BOX,
      EMPTY
    };
  */
  Tile();
  
  void setEmpty(bool b = true);
  bool isEmpty();

  void setBorder(bool b = true);
  bool isBorder();

  void setTarget(bool b = true);
<<<<<<< HEAD
  bool isTarget();
=======
  bool hasTarget();
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc

  void setPlayer(bool b = true);
  bool hasPlayer();

  void setBox(bool b = true);
  bool hasBox();

  void setReachable();
  void setUnreachable();
  bool isReachable();
  bool isReachableFrom(Tile::Side side);
 
<<<<<<< HEAD
  void setTileUp(const Tile & t=NULL);
  Tile & tileUp();

  void setTileDown(const Tile & t=NULL);
  Tile & tileDown();
  
  void setTileLeft(const Tile & t=NULL);
  Tile & tileLeft();

  void setTileRight(const Tile & t=NULL);
  Tile & tileRight();

}
=======
  void setTileUp(Tile & t);
  Tile & tileUp();

  void setTileDown(Tile & t);
  Tile & tileDown();
  
  void setTileLeft(Tile & t);
  Tile & tileLeft();

  void setTileRight(Tile & t);
  Tile & tileRight();

};
>>>>>>> 9767a7e0abc27fc7f17420089747ce6d0f5276cc


#endif
