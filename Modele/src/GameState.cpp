/**
 *  @title Boucle de jeu
 *  @author Romain Tourrel
 */
#include "../include/GameState.hpp"
using namespace std;

int GameState::event(int move){
  int sound = 0;
  if(move == 1){
    cout << "MOUVEMENT POSSIBLE ?? UP" <<endl;
    if(((matrix.getMatrix())[player.getX()+1][player.getY()]).isReachableFrom(Tile::Side::DOWN)){
      cout << "MOUVEMENT POSSIBLE : UP" <<endl;
      sound =1;
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
      cout << "ancien player x:" << player.getX() <<endl;
      cout << "ancien player y:" << player.getY() <<endl;
      player.up();
       cout << "nouveau player x:" << player.getX() <<endl;
      cout << "nouveau player y:" << player.getY() <<endl;
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
      player.incMoves();
      if(((matrix.getMatrix())[player.getX()][player.getY()]).hasBox()){
        cout << "CAISSE DETECTE" <<endl;
        sound=2;
  ((matrix.getMatrix())[player.getX()][player.getY()]).setBox(false);
  ((matrix.getMatrix())[player.getX()+1][player.getY()]).setBox(true);
  if(((matrix.getMatrix())[player.getX()+1][player.getY()]).hasTarget()){
    cout << "LIBERATION DE CIBLE" <<endl;
    nbr_target_free --;
  }
      }
    }
  }

 if(move == 2){
    cout << "MOUVEMENT POSSIBLE ?? DOWN" <<endl;
    if(((matrix.getMatrix())[player.getX()-1][player.getY()]).isReachableFrom(Tile::Side::UP)){
      cout << "MOUVEMENT POSSIBLE : DOWN" <<endl;
      sound =1;
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
      cout << "ancien player x:" << player.getX() <<endl;
      cout << "ancien player y:" << player.getY() <<endl;
      player.down();
       cout << "nouveau player x:" << player.getX() <<endl;
      cout << "nouveau player y:" << player.getY() <<endl;
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
      player.incMoves();
      if(((matrix.getMatrix())[player.getX()][player.getY()]).hasBox()){
        cout << "CAISSE DETECTE" <<endl;
        sound=2;
  ((matrix.getMatrix())[player.getX()][player.getY()]).setBox(false);
  ((matrix.getMatrix())[player.getX()-1][player.getY()]).setBox(true);
  if(((matrix.getMatrix())[player.getX()-1][player.getY()]).hasTarget()){
    cout << "LIBERATION DE CIBLE" <<endl;
    nbr_target_free --;
  }
      }

    }
  }
 if(move == 3){
  cout << "MOUVEMENT POSSIBLE ?? RIGHT" <<endl;
    if(((matrix.getMatrix())[player.getX()][player.getY()-1]).isReachableFrom(Tile::Side::LEFT)){
      cout << "MOUVEMENT POSSIBLE : RIGHT" <<endl;
      sound =1;
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
      cout << "ancien player x:" << player.getX() <<endl;
      cout << "ancien player y:" << player.getY() <<endl;
      player.right();
       cout << "nouveau player x:" << player.getX() <<endl;
      cout << "nouveau player y:" << player.getY() <<endl;
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
      player.incMoves();
      if(((matrix.getMatrix())[player.getX()][player.getY()]).hasBox()){
        cout << "CAISSE DETECTE" <<endl;
        sound=2;
  ((matrix.getMatrix())[player.getX()][player.getY()]).setBox(false);
  ((matrix.getMatrix())[player.getX()][player.getY()-1]).setBox(true);
  if(((matrix.getMatrix())[player.getX()][player.getY()-1]).hasTarget()){
    cout << "LIBERATION DE CIBLE" <<endl;
    nbr_target_free --;
  }
      }

    }
  }

 if(move == 4){
  cout << "MOUVEMENT POSSIBLE ?? LEFT" <<endl;
    if(((matrix.getMatrix())[player.getX()][player.getY()+1]).isReachableFrom(Tile::Side::RIGHT)){
      cout << "MOUVEMENT POSSIBLE" <<endl;
      sound =1;
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(false);
     cout << "ancien player x:" << player.getX() <<endl;
      cout << "ancien player y:" << player.getY() <<endl;
      player.left();
       cout << "nouveau player x:" << player.getX() <<endl;
      cout << "nouveau player y:" << player.getY() <<endl;
      ((matrix.getMatrix())[player.getX()][player.getY()]).setPlayer(true);
      player.incMoves();
      if(((matrix.getMatrix())[player.getX()][player.getY()]).hasBox()){
        cout << "CAISSE DETECTE" <<endl;
        sound=2;
  ((matrix.getMatrix())[player.getX()][player.getY()]).setBox(false);
  ((matrix.getMatrix())[player.getX()][player.getY()+1]).setBox(true);
  if(((matrix.getMatrix())[player.getX()][player.getY()+1]).hasTarget()){
    cout << "LIBERATION DE CIBLE" <<endl;
    nbr_target_free --;
  }
      }

    }
  }

  if (nbr_target_free == 0){
    end = true;
  }

  return sound;
}

bool GameState::getEnd(){
  return end;
}

Matrix GameState::getMatrix(){
  return matrix;
}

void GameState::initNbrTargetFree(){
  int nb;
  for(int i = 0; i<matrix.getRow();i++){
    for(int j = 0; j<matrix.getColumn();j++){
      if(matrix.getMatrix()[i][j].hasTarget() && !matrix.getMatrix()[i][j].hasBox()){
  nbr_target_free++;
      }
    }
  }
  cout << "COMPTE LE NB DE TARGET" <<endl;
}
// Constructeur
GameState::GameState(string file)
{
  matrix.setMap(file);
  int * positionPlayer = matrix.getPositionPlayer();
  player.setX(positionPlayer[0]);
  player.setY(positionPlayer[1]);
  nbr_target_free = 0;
  initNbrTargetFree();
  end = false;
  cout << "INIT MATRICE BIEN PASSE" <<endl;
}

