#ifndef MATRIX
#define MATRIX

#include "Tile.hpp"
using namespace std;

class Matrix{
private:
  unsigned int _row;
  unsigned int _column;
  Tile **_matrix;

public:
  Matrix():_row(0), _column(0), _matrix(nullptr) {}

  Matrix(unsigned int row, unsigned int column){
    _row = row;
    _column = column;
    _matrix = new Tile*[row];
    for(int j = 0; j < _row; j++){
      _matrix[j] = new Tile[_column];
    }  
  }

  Matrix(String chMatrix){
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
	  }
	}
      }
    }
  }

  unsigned int getRow() const;
  unsigned int getColumn() const;
  Tile **getMatrix();
  
  ~Matrix(){ }

};

#endif
