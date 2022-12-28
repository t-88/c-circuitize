#/!bin/bash

filename='main'

clear
echo "----------------------- compiling ------------------------------"
gcc  -Iincludes/ -Iincludes/ui -o main *.c  `sdl2-config --cflags --libs`  
if  (($? != 0)); then
    echo "---------------- error compiling ----------------------------"
else 
    echo "--------------------done compiling ------------------------------"
    echo "----------------------- running ----------------------------------"
    ./$filename
    rm main
    echo
    echo "---------------------- done running ------------------------------"
fi 
