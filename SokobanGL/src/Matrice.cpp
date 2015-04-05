/**
 * @title Matrice.cpp
 * @brief Permet d'implémenter la matrice utile à la grille de jeu
 */

#include "../include/Matrice.hpp"
#include "../include/Case.hpp"


unsigned int Matrice::getLignes() const{
  return _lignes;
}

unsigned int Matrice::getColonnes() const{
  return _colonnes;
}

double *Matrice::getMat() {
  return _mat;
}

Matrice & Matrice::operator= (const Matrice & m){
  if(this != &m){
    _lignes = m._lignes;
    _colonnes = m._colonnes;
    _mat = new Case[_lignes*_colonnes];
    memcpy(_mat, m._mat, sizeof(Case)*_lignes*_colonnes);
  }
  return *this;
}

Matrice Matrice::operator= (Matrice && m){
  if(this != &m){
    _lignes = m._lignes;
    _colonnes = m._colonnes;
    _mat = m._mat;
  }

  m._lignes = 0;
  m._colonnes = 0;
  m._mat = nullptr;
	
  cout << "op=Matrice(" << _lignes << "," << _colonnes << ")=" << this << " 2e= " << &m << endl;
	
  return *this;
}





ostream & operator<< (ostream & out, Matrice & m){
  int i,j;
  for(i=0;i<(int)m.getLignes();i++){
    for(j=0;j<(int)m.getColonnes();j++){
      out << m.getMat()[i*m.getColonnes()+j] << "\t";
    }
    out << endl;
  }
  out << endl;
	
  return out;
}

istream & operator>> (istream & in, Matrice & m){
  unsigned int l,c;
  in >> l >> c;
  Matrice mtemp = Matrice(l,c);
	
  unsigned int i,j;
  for(i=0;i<l;i++){
    for(j=0;j<c;j++){
      in >> mtemp.getMat()[i*c+j];
    }
  }
  m = mtemp;
	
  return in;
}

Matrice Matrice::extractMat(unsigned int lig, unsigned int col){
  Matrice extm = Matrice();
  unsigned int i,j,k=0,l=0;
	
  if( lig < this->getLignes() && col < this->getColonnes() ){
	
    extm = Matrice(this->getLignes() - 1,this->getColonnes() - 1);
		
    for(i=0;i<extm.getLignes();i++){
      if(k == lig)
	k++;
      for(j=0;j<extm.getColonnes();j++){
	if(l == col)
	  l++;
	extm._mat[i*extm.getColonnes()+j] = this->_mat[k*this->getColonnes()+l];
	l++;
      }
      k++;
      l = 0;
    }
  }
  return extm;
}
