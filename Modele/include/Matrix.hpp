#ifndef MATRIX
#define MATRIX


#include "Tile.hpp"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Matrix{
private:
  int _row;
  int _column;
  Tile **_matrix;
  string _pathFile;

public:
  Matrix():_row(0), _column(0), _matrix(0), _pathFile("") {}

  /*Matrix(string chMatrix){
    _pathFile = chMatrix;
    ifstream fileMatrix(_pathFile.c_str(), ios::in); 
    string line;
    int i = 0;
    bool emptyLine;
    if(fileMatrix){
      while(!fileMatrix.eof() && !emptyLine){
        getline(fileMatrix, line);
	if(line == ""){
	  emptyLine = true;
	}else{
	  if(i == 0){
	    fileMatrix >> _row >> _column;
	    _matrix = new Tile* [_row];
	    for(int j = 0; j < _row; j++){
	      _matrix[j] = new Tile[_column];
	    }  
	  }else{
	    for(int j = 0; j<line.length();j++){
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
	i++;
      }
      fileMatrix.close();
    }
    }*/

  /*Matrix(string pFileMatrix){
    _pathFile = pFileMatrix;
    ifstream fileMatrix(_pathFile.c_str(), ios::in);
    if(fileMatrix){
      fileMatrix >> _row >> _column;
      fileMatrix.close();
    }
    }*/

  //Matrix setMap(string chMatrix);
  int getRow() const;
  int getColumn() const;
  Tile **getMatrix();
  int* getPositionPlayer();
  
  ~Matrix(){ }

};

#endif
