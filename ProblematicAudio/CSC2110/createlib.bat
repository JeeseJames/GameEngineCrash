@echo off
cls

g++ -c String.cpp
g++ -c FileIO.cpp
g++ -c Random.cpp
ar -r libcsc2110.a String.o FileIO.o Random.o
