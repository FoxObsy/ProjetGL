

class Controles {

private:
  int _x;
  int _y;

public:

  // Constructeur
  Controles(int x=0, int y=0);

  int getX();
  int getY();
  void setX(int x);
  void setY(int y);

  void up();
  void down();
  void left();
  void right();
  





/* dans joueur :
methodes up() down() etc qui appellent controles.up() etc, et qui mettent à jour la pos du joueur à partir de la position modifiée dans controles.
*/



}
