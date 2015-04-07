#include "../include/Matrix.hpp"

Matrix Matrix::setMap(string chMatrix){ 
  _pathFile = chMatrix;
  ifstream fileMatrix(_pathFile.c_str(), ios::in); 
  string line;
  int i = 0;
  bool emptyLine;
  if(fileMatrix){
    fileMatrix >> _column >> _row;
    while(!fileMatrix.eof() && !emptyLine){
      getline(fileMatrix, line);
      if(line == ""){
	emptyLine = true;
      }else{
	if(i == 0){
	  _matrix = new Tile* [_row];
	  for(int j = 0; j < _row; j++){
	    _matrix[j] = new Tile[_column];
	  }
	}else{
	  for(int j = 0; j<_column;j++){
	    switch(line[j]){
	    case 'b' :
	      _matrix[i-1][j].setBox(true);
	      break;
	    case 'p' :
	      _matrix[i-1][j].setPlayer(true);
	      break;
	    case 't' :
	      _matrix[i-1][j].setTarget(true);
	      break;
	    case '-' :
	      _matrix[i-1][j].setEmpty(true);
	      break;
	    case 'x' :
	      _matrix[i-1][j].setBorder(true);
	      break;
	    }
	  }
	}
      }
      i++;
    }
    fileMatrix.close();
    attribSideTiles();
  }else{ 
    cout << "Impossible d'obtenir le fichier";
  }
}

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
  int *pos = new int[2];
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

void Matrix::AffMatrix(){
  for(int i = 0; i<_row; i++){
    for(int j = 0; j < _column; j++){
      if(_matrix[i][j].hasBox() && !_matrix[i][j].hasTarget()){
	cout << 'b';
      }else if(_matrix[i][j].hasBox() && _matrix[i][j].hasTarget()){
	cout << 'B';
      }
      else if(_matrix[i][j].hasTarget() && _matrix[i][j].isEmpty()){
	cout << 't';
      
      }else if(_matrix[i][j].hasTarget() && _matrix[i][j].hasPlayer()){
	cout << 'P';
      }else if(_matrix[i][j].isBorder()){
	cout << 'x';
      }
      else if(_matrix[i][j].hasPlayer()){
	cout << 'p';
      }else{
	cout << '-';
      }
    }
    cout << endl;
  }
}

void Matrix::attribSideTiles() {
  for (int i = 1; i<_row-1; i++){
    for(int j = 1; j < _column-1; j++){
      getMatrix()[i][j].setTileUp(&getMatrix()[i+1][j]);
      getMatrix()[i][j].setTileDown(&getMatrix()[i-1][j]);
      getMatrix()[i][j].setTileLeft(&getMatrix()[i][j+1]);
      getMatrix()[i][j].setTileRight(&getMatrix()[i][j-1]);
    }
  }
}