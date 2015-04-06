#include "../include/Matrix.hpp"

/*Matrix Matrix::setMap(String chMatrix){
  _pathFile = chMatrix;
  ifstream fileMatrix(chMatrix, ios::binary); 
  String line;
  int i = 0;
  bool emptyLine;
  if(fileMatrix){
    while(!fileMatrix.eof() && !emptyLine){
      getline(fileMatrix, line);
      i++;
      if(line == ""){
	emptyLine = true;
      }
      for(int j = 0; j<line.length();j++){
	switch(ligne[j]){
	case 'b' :
	  _matrix[i][j]->setBox(true);
	case 'p' :
	  _matrix[i][j]->setPlayer(true);
	case 'c' :
	  _matrix[i][j]->setTarget(true);
	case '-' :
	  _matrix[i][j]->setEmpty(true);
	case 'x' :
	  _matrix[i][j]->setBorder(true);
	}
	_column = j;
      }	
    }
    _row = i;
  }
  }*/

Tile **Matrix::getMatrix(){
  return _matrix;
}

int Matrix::getRow() const{
  return _row;
}

int Matrix::getColumn() const{
  return _column;
}

int* Matrix::getPositionPlayer(){
  int pos[2];
  for(int i =0; i < _row; i++){
    for(int j = 0; j < _column; j++){
      if(_matrix[i][j].hasPlayer()){
        pos[0] = i;
	pos[1] = j;
	return pos;
      }
    }
  }
}
