DIR := $(shell pwd)
CPP := g++

all: main
main: $(patsubst %.cpp,%.o,$(wildcard *.cpp)) 
	$(CPP) -o $@ $^
%.o:%.cpp
	$(CPP) -c -Wall -std=c++0x $< -o $@
