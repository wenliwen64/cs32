#include "Map.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Map m1;
	Map m2;
	Map m3;

//  test combination fucntion  case 0 : empty Map
    assert(combine(m1, m2, m3));
	assert(m3.size() == 0);

//  test insert function
    assert(m1.insert("Fred", 123));
    assert(m2.insert("Fred", 122));
    
	assert(m1.contains("Fred"));
	assert(m1.size() == 1);
    assert(m2.size() == 1);

//  test combination function  case 1 : 1 item, same key, different value
    assert(!combine(m1, m2, m3));
	assert(m3.size() == 0);

//  test combination function  case 1 : 1 item, same key, same value

    assert(m2.erase("Fred"));
    assert(m2.insert("Fred", 123));
    assert(combine(m1, m2, m3));
	assert(m3.size() == 1);

//  test combination function case 2: same key, differ value, return error
    assert(m1.insert("Ethel", 456));
	assert(m2.insert("Ethel", 454));
	assert(!combine(m1, m2, m3));
    assert(m3.size() == 1);
   
//  test  combination function case 3: multiple items
    assert(m1.insert("Zheng", 789));
	assert(m2.insert("Lucy", 789));
	assert(!combine(m1, m2, m3));
    assert(m3.size() == 3);
    

//  test swap


//  test subtract
    Map msub1;
	Map msub2;
	Map msub3;

    assert(msub1.insert("Fred", 123));
    assert(msub1.insert("Ethel", 456));
    assert(msub1.insert("Lucy", 789));

    assert(msub2.insert("Fred", 123));

	assert(msub1.size() == 3);

	subtract(msub1, msub2, msub3);


    assert(msub3.size() == 2);

    assert(msub2.erase("Fred"));
    assert(msub2.insert("Freds", 123));

	subtract(msub1, msub2, msub3);
	assert(msub3.size()==3);

	
    assert(msub2.insert("Ethel", 456));
    assert(msub2.insert("Lucy", 788));
	subtract(msub1, msub2, msub3);
	assert(msub3.size() == 1);





//	double d = 42;
//    assert(m.get("Fred", d)  &&  d == 123);
//    d = 42;
//    string s1;
//    assert(m.get(0, s1, d)  &&
//           ((s1 == "Fred"  &&  d == 123)  ||  (s1 == "Ethel"  &&  d == 456)));
//    string s2;
//    assert(m.get(1, s2, d)  &&  s1 != s2  &&
//           ((s2 == "Fred"  &&  d == 123)  ||  (s2 == "Ethel"  &&  d == 456)));
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
