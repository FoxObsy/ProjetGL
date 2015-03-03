#!/bin/bash
# To compile and run the code in simonl you should use: 
#  ./test.sh simonl c
# To run and view the code:
#  ./test.sh simon v
# If you don't wand to compile:
#  ./test.sh simonl
name=$1
actions=$2
cd $name
if [[ "$actions" == *c* ]]
then
  mkdir build
  cd build
  rm -rf *
  cmake ..
  make binocular
  cd ..
fi
cd build
./Binocular/binocular

cd ..

if [[ "$actions" == *v* ]]
then
  vimdiff ./Binocular/binocular.cpp ../simonl/Binocular/binocular.cpp
fi
