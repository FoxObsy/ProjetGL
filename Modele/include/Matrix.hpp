#ifndef MATRIX
#define MATRIX

using namespace std;

class Matrix{
private:
  unsigned int _row;
  unsigned int _column;
  Tile **_matrix;
  String _pathFile;
  int _nbTagetFree;

public:
  Matrix():_row(0), _column(0), _matrix(nullptr), _pathFile(nullptr), _nbTargetFree(0) {}

  Matrix(unsigned int row, unsigned int column){
    _row = row;
    _column = column;
    _pathFile = "";
    _matrix = new Tile* [_row];
    for(int j = 0; j < _row; j++){
      _matrix[j] = new Tile[_column];
    }  
    _nbtargetFree = 0;
  }

  Matrix(String chMatrix){
    _pathFile(chMatrix);
    ifstream fileMatrix(chMatrix, ios::binary); 
    String line;
    int i = 0;
    bool emptyLine;
    if(fileMatrix){
      while(!fileMatrix.eof() && !emptyLine){
        getline(fileMatrix, line);
	if(line == ""){
	  emptyLine = true;
	}else{
	  if(i == 0){
	    for(int j = 0; j<line.length(); j++){
	      
	    }
	  }else{
	    for(int j = 0; j<line.length();j++){
	      switch(line[j]){
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
	    }
	  }
	}
	i++;
      }
    }
  }

  Matrix setMap(String chMatrix);
  unsigned int getRow() const;
  unsigned int getColumn() const;
  Tile **getMatrix();
  int[] getPositionPlayer();
  
  ~Matrix(){ }

};

#endif
