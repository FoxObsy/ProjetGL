#ifndef MATRIX
#define MATRIX

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
    _matrix = new Tile[_row][_column];
  }

  unsigned int getRow() const;
  unsigned int getColumn() const;
  Tile **getMatrix();
  
  ~Matrix(){ }

};

#endif
