#include "../include/Matrix.hpp"

Matrix Matrix::setMap(string chMatrix){ 
  _pathFile = chMatrix;
  ifstream fileMatrix(_pathFile.c_str(), ios::in); 
  string line;
  int i = 0;
  bool emptyLine;
  if(fileMatrix){
    fileMatrix >> _column >> _row;
    cout << _row << endl;
    cout << _column << endl;
    while(!fileMatrix.eof() && !emptyLine){
      getline(fileMatrix, line);
      cout << line.length() - 1 << endl;
      if(line == ""){
	emptyLine = true;
      }else{
	if(i == 0){
	  _matrix = new Tile* [_row + 1];
	  for(int j = 0; j < _row + 1; j++){
	    _matrix[j] = new Tile[_column];
	  }
	  cout << "allocation matrice ok" << endl;
	}else{
	  for(int j = 0; j<(line.length() - 1);j++){
	    cout << "colonne nb :" << j << endl;
	    switch(line[j]){
	    case 'b' :
	      _matrix[i][j].setBox(true);
	      break;
	    case 'p' :
	      _matrix[i][j].setPlayer(true);
	      break;
	    case 't' :
	      _matrix[i][j].setTarget(true);
	      break;
	    case '-' :
	      _matrix[i][j].setEmpty(true);
	      break;
	    case 'x' :
	      _matrix[i][j].setBorder(true);
	      break;
	    }
	  }
	}
      }
      cout << "nb ligne :" << i << endl;
      i++;
    }
    fileMatrix.close();
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
