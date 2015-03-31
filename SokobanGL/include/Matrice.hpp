/**
 * @title Matrice de caisses
 * @author Romain Tourrel
 */

#ifndef MATRICE
#define MATRICE

#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

class Matrice {
 private:

  unsigned int _lignes;
  unsigned int _colonnes;
  Case *_mat;
		
 public:

 Matrice(): _lignes(0), _colonnes(0), _mat(nullptr) {}

  Matrice(unsigned int lig,unsigned int col){
    _lignes = lig;
    _colonnes = col;
    _mat = new Case[_lignes*_colonnes];
  }
		
  // Constructeur par recopie
  Matrice(const Matrice & m){
    _lignes = m._lignes;
    _colonnes = m._colonnes;
    _mat = new double[_lignes*_colonnes];
    memcpy(_mat, m._mat, sizeof(double)*_lignes*_colonnes);
  }
		
  // Constructeur par deplacement
  Matrice(Matrice && m){
    _lignes = m._lignes;
    _colonnes = m._colonnes;
    _mat = m._mat;
			
    m._lignes = 0;
    m._colonnes = 0;
    m._mat = nullptr;
			
    cout << "+++Matrice(" << _lignes << "," << _colonnes << ")=" << this << " 2e= " << &m << endl;
  }
		
  unsigned int getLignes() const;
  unsigned int getColonnes() const;
  double *getMat();
		
  Matrice & operator=(const Matrice &);

  Matrice operator=(Matrice && m);
		
  ~Matrice(){}	
		
  friend ostream & operator<< (ostream & out, Matrice & m);
  friend istream & operator>> (istream & in, Matrice & m);


		
  Matrice extractMat(unsigned int i, unsigned int j);

};


#endif
