#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;
bool combine(const Map& m1, const Map& m2, Map& result); //TODO:
void subtract(const Map& m1, const Map& m2, Map& result); //TODO:

void test()
{
    // Empty Map Test
    Map m; // Empty m;
    KeyType key;
    ValueType value;
    assert(m.size() == 0);
    assert(m.empty());
    assert(!m.erase("Fred"));
    assert(!m.contains("Fred"));
    assert(!m.get(0, key, value));
    assert(!m.get(key, value));
    assert(m.insert("Fred", 222));
    m.get("Fred", value);
    assert(value== 222);
    //assert(m.insertOrUpdate("Fred", 334));
    assert(m.update("Fred", 334));
    assert(m.contains("Fred"));
    m.get("Fred", value);
    assert(value== 334);
    m.erase("Fred");
    assert(m.empty());

    //
    Map m1;
    m1.insert("Ethel", 456);
    m1.insert("Lucy", 789);
    m1.insert("Fred", 123);
    m.swap(m1);
    assert(m1.empty());
    assert(m.size() == 3);
    m.swap(m1);

    //combine
    Map m2=m;
    assert(m2.empty());
    m2.insert("Lucy", 789);
    m2.insert("Ricky", 321);

    m.insert("Wenliwen", -1111);
    std::cerr << m1.size() << " = m1.size()" << std::endl;
    assert(combine(m1, m2, m));
    m1.dump();
    std::cerr << "==================" << std::endl;
    m2.dump();
    std::cerr << "==================" << std::endl;
    m.dump();
    assert(m.size()==5);

    
    //Subtract
    //m.erase("Lucy");
    m.erase("Ricky");
    Map m4;
    Map m10;
    m4 = m;
    std::cerr << "m4==============" << std::endl;
    m4.dump();
    Map m5;
    m5.insert("Lucy", 789);
    m5.insert("Ricky", 321);
    m5.insert("Ethel", 654);
    std::cerr << "m5==============" << std::endl;
    m5.dump();
    m.insert("Pan", 98);
    subtract(m4, m5, m4);
    std::cerr << "===============" << std::endl;
    m4.dump();
    //assert();
    /*
    Map m;
    assert(m.insert("Fred", 123));
    //cerr << "happy" << endl;
    assert(m.insert("Ethel", 456));
    assert(m.size() == 2);
    double d = 42;
    assert(m.get("Fred", d)  &&  d == 123);
    d = 42;
    string s1;
    assert(m.get(0, s1, d)  &&
	    ((s1 == "Fred"  &&  d == 123)  ||  (s1 == "Ethel"  &&  d == 456)));
    string s2;
    assert(m.get(1, s2, d)  &&  s1 != s2  &&
	    ((s2 == "Fred"  &&  d == 123)  ||  (s2 == "Ethel"  &&  d == 456)));
	    */
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}

