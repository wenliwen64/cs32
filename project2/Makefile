GCC := g++

all: test0 test1
int2string: testInt2String
test0: Map.cpp Map.h test0.cpp
	$(GCC) -o test0 Map.cpp test0.cpp 
test1: Map.cpp Map.h test1.cpp
	$(GCC) -o test1 Map.cpp test1.cpp 
testInt2String: Map.cpp Map.h testInt2String.cpp
	$(GCC) -o testInt2String Map.cpp testInt2String.cpp
