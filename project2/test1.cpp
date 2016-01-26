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
    Map m; 
    KeyType key;
    ValueType value;
    assert(m.size() == 0);  // test size()
    assert(m.empty()); // test empty()
    assert(!m.erase("Fred"));  // test erase()
    assert(!m.contains("Fred"));  // test contains()
    assert(!m.get(0, key, value)); // test get()
    assert(!m.get(key, value)); // test get()
    assert(m.insert("Fred", 222)); // test insert()

    // Normal Map Test
    m.get("Fred", value); // test get()
    assert(value== 222);  
    //assert(m.insertOrUpdate("Fred", 334));
    assert(m.contains("Fred")); // test contains()
    assert(m.update("Fred", 334)); // test update()
    m.get("Fred", value); // test get()
    assert(value== 334);
    assert(m.insertOrUpdate("Fred", 434.6)); // test insertOrUpdate()
    m.get("Fred", value);
    assert(value== 434.6);
    m.erase("Fred");  // test erase()
    assert(m.empty());

    // Swap;
    Map m1;
    m1.insert("Ethel", 456);
    m1.insert("Lucy", 789);
    m1.insert("Fred", 123);
    m.swap(m1);
    assert(m1.empty());
    assert(m.size() == 3);
    assert(m.contains("Ethel"));
    assert(m.contains("Lucy"));
    assert(m.contains("Fred"));
    m.swap(m1);

    // Combine
    Map m2;
    Map m3;
    assert(m2.empty());
    m2.insert("Lucy", 789);
    m2.insert("Ricky", 321);
    m3.insert("Wenliwen", -1111);
    std::cerr << m1.size() << " = m1.size()" << std::endl;
    assert(combine(m1, m2, m3)); // test return true 
    assert(!m3.contains("Wenliwen"));
    assert(m3.contains("Ricky"));
    assert(m3.contains("Ethel"));
    assert(m3.contains("Fred"));
    assert(m3.contains("Lucy"));
    assert(m3.size() == 4);

    Map m4;
    m2.update("Lucy", 9999);
    assert(!combine(m1, m2, m4)); // test return false
    assert(m4.size() == 3); // test false case for combine
    assert(!combine(m1, m2, m1));
    std::cerr << "********" << std::endl;
    m1.dump();
    assert(m1.size() == 3);



    //m1.dump();
    //std::cerr << "==================" << std::endl;
    //m2.dump();
    //std::cerr << "==================" << std::endl;
    //m.dump();
    //assert(m.size()==5);

    
    //Subtract
    Map m5;
    Map m6 = m4; // Ricky 321, Ethel 456, Fred 123
    std::cerr << "m6==============" << std::endl;
    m6.dump();
    m5.insert("Lucy", 789);
    m5.insert("Ricky", 321);
    m5.insert("Ethel", 456);
    Map m7;
    m7.insert("Pan", 873);
    subtract(m5, m6, m7); // m7: Pan 873, Lucy 789
    assert(m7.size() == 1);
    assert(!m7.contains("Pan"));
    assert(m7.contains("Lucy"));
    m7.dump();
    subtract(m5, m6, m5);
    assert(m5.size() == 1);
    assert(m5.contains("Lucy"));
    assert(!m5.contains("Ricky"));
    assert(!m5.contains("Ethel"));

    //Destructor
    for(int i = 0; i < 5; i++){
	Map m_temp;
	m_temp.insert("test", 0.1);
    }

    //Copy Constructor
    Map m_origin;
    m_origin.insert("origin0", 0);
    m_origin.insert("origin1", 1);
    m_origin.insert("origin2", 2);

    Map m_copy(m_origin);
    m_origin.erase("origin2");
    assert(m_copy.size() == 3);
    assert(m_copy.contains("origin0"));
    assert(m_copy.contains("origin1"));
    assert(m_copy.contains("origin2"));

    ValueType value_copy;
    m_copy.get("origin0", value_copy);
    assert(value_copy == 0);
    m_copy.get("origin1", value_copy);
    assert(value_copy == 1);
    m_copy.get("origin2", value_copy);
    assert(value_copy == 2);

    //Assign Operator
    Map m_assign = m_origin;
    m_origin.insert("origin2", 2);
    assert(m_assign.size() == 2);
    assert(m_assign.contains("origin0"));
    assert(m_assign.contains("origin1"));
    assert(!m_assign.contains("origin2"));

    ValueType value_assign;
    m_assign.get("origin0", value_assign);
    assert(value_assign == 0);
    m_assign.get("origin1", value_assign);
    assert(value_assign == 1);
    //m_assign.get("origin2", value_assign);
    //assert(value_assign == 2);
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

