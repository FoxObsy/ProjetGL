
class Controls;


class Player {
  
private:
  int _x;
  int _y;
  Controls _controls;



public:

  // Constructeurs
  Player(int x=0, int y=0);

  // Getters / Setters
  int getX();
  int getY();
  void setX(int x);
  void setY(int y);


  // Méthodes de déplacement
  void up();
  void down();
  void left();
  void right();
  
