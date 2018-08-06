#! /bin/bash

echo \#ifdef __CINT__
echo \#pragma link off all globals\;
echo \#pragma link off all classes\;
echo \#pragma link off all functions\;
echo 
for i in $@;
do 
    echo \#pragma link C++ class $i\;
done
echo
echo \#endif