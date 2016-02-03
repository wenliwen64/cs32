GCC := g++

all: test_mazestack test_mazequeue test_evaluate
test_mazestack: test_mazestack.cpp mazestack.cpp
	$(GCC) -o test_mazestack test_mazestack.cpp mazestack.cpp
test_mazequeue: test_mazequeue.cpp mazequeue.cpp
	$(GCC) -o test_mazequeue test_mazequeue.cpp mazequeue.cpp
test_evaluate: eval.cpp Map.cpp Map.h
	$(GCC) -o test_evaluate eval.cpp Map.cpp
