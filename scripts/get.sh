#!/bin/bash
# to get the code from simonl (can be replaced by any student login)
# ./get.sh simonl
name=$1
mkdir $name
cd $name
wget http://www.ecole.ensicaen.fr/~$name/SI3ALabs.tar.gz
tar xf SI3ALabs.tar.gz
result=`git tag|grep postexam`
if [[ -z $result ]]
then
  echo !!!!!!!!!!!!!!!!FAILURE!!!!!!!!!!!!!
else
  echo ok
fi

# cros duche broussard jbrolland virgili jlevillain jean amauduit ullmo
# nferrand gerfault pascal tran nassala lebagousse
