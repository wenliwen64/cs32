DIR := $(shell pwd)
CPP := g++

all: testMap 
testMap:Map.o testMap.o
	$(CPP) $^ -o $@
Map.o: Map.h Map.cpp
	$(CPP) -c Map.cpp -o Map.o 
testMap.o: testMap.cpp Map.h
	$(CPP) -c testMap.cpp -o testMap.o 
