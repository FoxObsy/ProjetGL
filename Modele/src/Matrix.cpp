#include "../include/Matrix.hpp"
#include "../include/Tile.hpp"

Tile **Matrix::getMatrix(){
  return _matrix;
}

unsigned int Matrix::getRow(){
  return _row;
}

unsigned int Matrix::getColunm(){
  return _column;
}
