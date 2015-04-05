#ifndef TILE_H
#define TILE_H

class Tile {

  bool _isEmpty;
  bool _isBorder;
  bool _isTarget;
  bool _hasPlayer;
  bool _hasBox;
  bool _isReachable; // avérée inutile

  Tile & tileUp;
  Tile & tileDown;
  Tile & tileLeft;
  Tile & tileRight;
  


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
  bool isTarget();

  void setPlayer(bool b = true);
  bool hasPlayer();

  void setBox(bool b = true);
  bool hasBox();

  void setReachable();
  void setUnreachable();
  bool isReachable();
  bool isReachableFrom(Tile::Side side);
 
  void setTileUp(const Tile & t=NULL);
  Tile & tileUp();

  void setTileDown(const Tile & t=NULL);
  Tile & tileDown();
  
  void setTileLeft(const Tile & t=NULL);
  Tile & tileLeft();

  void setTileRight(const Tile & t=NULL);
  Tile & tileRight();

}


#endif
