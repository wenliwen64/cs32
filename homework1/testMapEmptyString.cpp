#include <iostream>
#include "Map.h"
#include <cassert>
int main(){
    Map gpas;
    gpas.insert("Fred", 2.956);
    assert(!gpas.contains(""));
    gpas.insert("Ethel", 3.538);
    gpas.insert("", 4.000);
    gpas.insert("Lucy", 2.956);
    assert(gpas.contains(""));
    gpas.dump();
    std::cout << "=============" << std::endl;
    gpas.erase("Fred");
    gpas.dump();
    assert(gpas.size() == 3  &&  gpas.contains("Lucy")  &&  gpas.contains("Ethel")  &&
	    gpas.contains(""));
}
