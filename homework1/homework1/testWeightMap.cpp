#include "WeightMap.h"
#include <iostream> 
#include <cassert>

int main(){
    WeightMap m;  // maps strings to doubles
    m.enroll("Jay", 98.5);
    assert(m.size() == 1);
    m.enroll("Jay", 34.5);
    assert(m.size() == 1);

    m.enroll("Pan", 45.6);
    assert(m.weight("Pan") == 45.6 && m.weight("Jay") == 98.5);

    m.enroll("Liwen", 109.4);
    m.adjustWeight("Liwen", -110.9);
    m.adjustWeight("Jason", -4.0);
    assert(m.weight("Liwen") == 109.4 && m.size() == 3);
    m.print();

    m.adjustWeight("Liwen", -12.0);
    assert(m.weight("Liwen") == 97.4);
    m.print();

    std::cout << "Passed all tests" << std::endl;
}
