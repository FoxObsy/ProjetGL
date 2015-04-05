#ifndef TILE_H
#define TILE_H

class Tile {

  bool _isEmpty;
  bool _isBorder;
  bool _hasTarget;
  bool _hasPlayer;
  bool _hasBox;
  bool _isReachable; // avérée inutile

  Tile* _tileUp;
  Tile* _tileDown;
  Tile* _tileLeft;
  Tile* _tileRight;
  


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
  bool hasTarget();

  void setPlayer(bool b = true);
  bool hasPlayer();

  void setBox(bool b = true);
  bool hasBox();

  void setReachable();
  void setUnreachable();
  bool isReachable();
  bool isReachableFrom(Tile::Side side);
 
  void setTileUp(Tile & t);
  Tile & tileUp();

  void setTileDown(Tile & t);
  Tile & tileDown();
  
  void setTileLeft(Tile & t);
  Tile & tileLeft();

  void setTileRight(Tile & t);
  Tile & tileRight();

};


#endif
