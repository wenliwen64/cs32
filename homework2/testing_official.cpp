// tester.cpp
// To test HW 1 Problem 5, uncomment the following line:
// #define TESTNEW

#ifdef TESTNEW
#include "newMap.h"
#else
#include "Map.h"
#endif

#include &lt;iostream>
#include &lt;cstdlib>
#include &lt;cassert>
#include &lt;type_traits>

using namespace std;

bool get2type(bool (Map::*)(const KeyType&amp;, ValueType&amp;) const) { return true; }
bool get2type(bool (Map::*)(const KeyType&amp;, ValueType&amp;)) { return false; }
bool get2type(...) { return false; }
bool get3type(bool (Map::*)(int, KeyType&amp;, ValueType&amp;) const) { return true; }
bool get3type(bool (Map::*)(int, KeyType&amp;, ValueType&amp;)) { return false; }
bool get3type(...) { return false; }

static KeyType DUMMY = "junk";
static KeyType DEFAULT = "";
static KeyType ARRAY[6] = {
	"able", "baker", "charlie", "delta", "echo", "foxtrot"
};

static ValueType DUMMYV = 123;
static ValueType DEFAULTV = 0;
static ValueType ARRAYV[6] = { 10, 20, 30, 40, 50, 60 };

bool isPermutation(KeyType a[], const KeyType b[], int n)
{
	for (int k = 0; k &lt; n; k++)
	{
		int j;
		for (j = k; j &lt; n; j++)
		{
			if (b[k] == a[j])
			{
				KeyType t = a[k];
				a[k] = a[j];
				a[j] = t;
				break;
			}
		}
		if (j == n)
			return false;
	}
	return true;
}

bool has(const Map&amp; m, const KeyType&amp; k, const ValueType&amp; v)
{
	ValueType v2 = DEFAULTV;
	m.get(k, v2);
	ValueType v3 = DUMMYV;
	m.get(k, v3);
	return v2 == v  &amp;&amp;  v3 == v;
}

const int SPEC_MAX = 200;

void testone(int n)
{
	Map m;
	switch (n)
	{
				 default: {
	    cout &lt;&lt; "Bad argument" &lt;&lt; endl;
			} break; case  1: {
	    assert((is_same&lt;decltype(&amp;Map::empty), bool (Map::*)() const>::value));
			} break; case  2: {
	    assert((is_same&lt;decltype(&amp;Map::size), int (Map::*)() const>::value));
			} break; case  3: {
	    assert((is_same&lt;decltype(&amp;Map::contains), bool (Map::*)(const KeyType&amp;) const>::value));
			} break; case  4: {
	    assert(get2type(&amp;Map::get));
			} break; case  5: {
	    assert(get3type(&amp;Map::get));
			} break; case  6: {
	    assert(m.empty());
			} break; case  7: {
	    assert(m.size() == 0);
			} break; case  8: {
	    assert(!m.update(DEFAULT, DUMMYV)  &amp;&amp;  m.size() == 0);
			} break; case  9: {
	    assert(!m.erase(DEFAULT)  &amp;&amp;  m.size() == 0);
			} break; case 10: {
	    assert(!m.contains(DEFAULT));
	  		} break; case 11: {
	    ValueType v = DUMMYV;
	    assert(!m.get(DEFAULT, v)  &amp;&amp;  v == DUMMYV);
	  		} break; case 12: {
	    ValueType v = DUMMYV;
	    assert(!m.get(0, DEFAULT, v)  &amp;&amp;  v == DUMMYV);
	  		} break; case 13: {
	    assert(m.insert(DUMMY, DUMMYV));
	  		} break; case 14: {
	    m.insert(DUMMY, DUMMYV);
	    assert(!m.empty());
	  		} break; case 15: {
	    m.insert(DUMMY, DUMMYV);
	    assert(m.size() == 1);
	  		} break; case 16: {
	    m.insert(DUMMY, DUMMYV);
	    assert(m.contains(DUMMY));
	  		} break; case 17: {
	    m.insert(DUMMY, DUMMYV);
	    ValueType v = DEFAULTV;
	    assert(m.get(DUMMY, v));
	  		} break; case 18: {
	    m.insert(DUMMY, DUMMYV);
	    ValueType v = DEFAULTV;
	    m.get(DUMMY, v);
	    assert(v == DUMMYV);
	  		} break; case 19: {
	    m.insert(ARRAY[0], DUMMYV);
	    ValueType v = DEFAULTV;
	    assert(!m.get(ARRAY[1], v));
	  		} break; case 20: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    ValueType v = DUMMYV;
	    m.get(ARRAY[1], v);
	    assert(v == DUMMYV);
	  		} break; case 21: {
	    m.insert(DUMMY, DUMMYV);
	    KeyType k = DEFAULT;
	    ValueType v = DEFAULTV;
	    assert(m.get(0, k, v));
	  		} break; case 22: {
	    m.insert(DUMMY, DUMMYV);
	    KeyType k = DEFAULT;
	    ValueType v = DEFAULTV;
	    m.get(0, k, v);
	    assert(k == DUMMY  &amp;&amp;  v == DUMMYV);
	  		} break; case 23: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(!m.empty()   &amp;&amp;  m.size() == 2);
	  		} break; case 24: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(m.contains(ARRAY[0])  &amp;&amp;  m.contains(ARRAY[1]));
	  		} break; case 25: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(has(m, ARRAY[0], ARRAYV[0])  &amp;&amp;  has(m, ARRAY[1], ARRAYV[1]));
	  		} break; case 26: {
	    m.insert(ARRAY[0], DUMMYV);
	    m.insert(ARRAY[1], DUMMYV);
	    assert(has(m, ARRAY[0], DUMMYV)  &amp;&amp;  has(m, ARRAY[1], DUMMYV));
	  		} break; case 27: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insert(ARRAY[1], ARRAYV[1]));
	  		} break; case 28: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[0], ARRAYV[2]);
	    assert(m.size() == 2);
	  		} break; case 29: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[0], ARRAYV[2]);
	    assert(has(m, ARRAY[0], ARRAYV[0])  &amp;&amp;  has(m, ARRAY[1], ARRAYV[1]));
	  		} break; case 30: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insert(ARRAY[1], ARRAYV[1]));
	    assert(!m.insert(ARRAY[0], ARRAYV[2]));
	  		} break; case 31: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insert(ARRAY[1], ARRAYV[1]));
	    assert(!m.insert(ARRAY[0], ARRAYV[0]));
	  		} break; case 32: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    m.update(ARRAY[1], DUMMYV);
	    assert(m.size() == 3  &amp;&amp;  m.contains(ARRAY[0])  &amp;&amp;
			m.contains(ARRAY[1])  &amp;&amp;  m.contains(ARRAY[2]));
			} break; case 33: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    m.update(ARRAY[1], DUMMYV);
	    assert(has(m, ARRAY[0], ARRAYV[0])  &amp;&amp;  has(m, ARRAY[1], DUMMYV)  &amp;&amp;
						has(m, ARRAY[2], ARRAYV[2]));
	    		} break; case 34: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    assert(m.update(ARRAY[1], DUMMYV));
	    		} break; case 35: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.update(ARRAY[2], ARRAYV[0]);
	    assert(m.size() == 2  &amp;&amp;  has(m, ARRAY[0], ARRAYV[0])  &amp;&amp;
			has(m, ARRAY[1], ARRAYV[1])  &amp;&amp;  !m.contains(ARRAY[2]));
	    		} break; case 36: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(!m.update(ARRAY[2], ARRAYV[2])  &amp;&amp;  !m.update(ARRAY[3], ARRAYV[0]));
	  		} break; case 37: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
	    assert(!m.empty()   &amp;&amp;  m.size() == 2);
	  		} break; case 38: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
	    assert(has(m, ARRAY[0], ARRAYV[0])  &amp;&amp;  has(m, ARRAY[1], ARRAYV[1]));
	  		} break; case 39: {
	    m.insert(ARRAY[0], DUMMYV);
	    m.insertOrUpdate(ARRAY[1], DUMMYV);
	    assert(has(m, ARRAY[0], DUMMYV)  &amp;&amp;  has(m, ARRAY[1], DUMMYV));
	  		} break; case 40: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insertOrUpdate(ARRAY[1], ARRAYV[1]));
	  		} break; case 41: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insertOrUpdate(ARRAY[0], ARRAYV[2]);
	    assert(m.size() == 2  &amp;&amp;  has(m, ARRAY[0], ARRAYV[2])  &amp;&amp;
						has(m, ARRAY[1], ARRAYV[1]));
	  		} break; case 42: {
	    assert(m.insert(ARRAY[0], ARRAYV[0]));
	    assert(m.insert(ARRAY[1], ARRAYV[1]));
	    assert(m.insertOrUpdate(ARRAY[0], ARRAYV[2]));
			} break; case 43: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    m.insertOrUpdate(ARRAY[1], DUMMYV);
	    assert(m.size() == 3  &amp;&amp;  has(m, ARRAY[0], ARRAYV[0])  &amp;&amp;
			has(m, ARRAY[1], DUMMYV)  &amp;&amp;  has(m, ARRAY[2], ARRAYV[2]));
	    		} break; case 44: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    assert(m.insertOrUpdate(ARRAY[1], DUMMYV));
	    		} break; case 45: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insertOrUpdate(ARRAY[2], ARRAYV[0]);
	    assert(m.size() == 3  &amp;&amp;  has(m, ARRAY[0], ARRAYV[0])  &amp;&amp;
			has(m, ARRAY[1], ARRAYV[1])  &amp;&amp;  has(m, ARRAY[2], ARRAYV[0]));
	    		} break; case 46: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(m.insertOrUpdate(ARRAY[2], ARRAYV[2]));
	    		} break; case 47: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(m.erase(ARRAY[1]));
	    		} break; case 48: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.erase(ARRAY[1]);
	    assert(!m.empty()  &amp;&amp;  m.size() == 1  &amp;&amp;  has(m, ARRAY[0], ARRAYV[0])  &amp;&amp;
							!m.contains(ARRAY[1]));
	    		} break; case 49: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.erase(ARRAY[0]);
	    assert(!m.empty()  &amp;&amp;  m.size() == 1  &amp;&amp;  has(m, ARRAY[1], ARRAYV[1])  &amp;&amp;
							!m.contains(ARRAY[0]));
	    		} break; case 50: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.erase(ARRAY[0]);
	    m.erase(ARRAY[1]);
	    assert(m.size() == 0);
	    		} break; case 51: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    m.erase(ARRAY[1]);
	    m.erase(ARRAY[2]);
	    m.insert(ARRAY[3], ARRAYV[3]);
	    assert(m.size() == 2  &amp;&amp;  has(m, ARRAY[0], ARRAYV[0])  &amp;&amp;
			has(m, ARRAY[3], ARRAYV[3])  &amp;&amp;  !m.contains(ARRAY[1])  &amp;&amp;
							!m.contains(ARRAY[2]));
	    		} break; case 52: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    assert(!m.erase(ARRAY[2])  &amp;&amp;  m.size() == 2);
	    		} break; case 53: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    KeyType k;
	    ValueType v;
	    assert(!m.get(-1, k, v));
	    		} break; case 54: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    KeyType k = DUMMY;
	    ValueType v = DUMMYV;
	    m.get(-1, k, v);
	    assert(k == DUMMY  &amp;&amp;  v == DUMMYV);
	    		} break; case 55: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    KeyType k;
	    ValueType v;
	    assert(!m.get(2, k, v));
	    		} break; case 56: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    KeyType k = DUMMY;
	    ValueType v = DUMMYV;
	    m.get(2, k, v);
	    assert(k == DUMMY  &amp;&amp;  v == DUMMYV);
	    		} break; case 57: {
	    m.insert(DEFAULT, DUMMYV);
	    assert(m.size() == 1  &amp;&amp;  has(m, DEFAULT, DUMMYV));
	    		} break; case 58: {
	    m.update(DEFAULT, DUMMYV);
	    assert(m.size() == 0  &amp;&amp;  !m.contains(DEFAULT));
	    		} break; case 59: {
	    m.insertOrUpdate(DEFAULT, DUMMYV);
	    assert(m.size() == 1  &amp;&amp;  has(m, DEFAULT, DUMMYV));
	    		} break; case 60: {
	    m.insert(DEFAULT, DUMMYV);
	    m.erase(DEFAULT);
	    assert(m.size() == 0  &amp;&amp;  !m.contains(DEFAULT));
	    		} break; case 61: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
	    	m2.insert(ARRAY[2], ARRAYV[2]);
	    	m2.insert(ARRAY[3], ARRAYV[3]);
	    	m2.insert(ARRAY[1], ARRAYV[1]);
		m.swap(m2);
		assert(m.size() == 3);
	    }
	    		} break; case 62: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
	    	m2.insert(ARRAY[2], ARRAYV[2]);
	    	m2.insert(ARRAY[3], ARRAYV[3]);
	    	m2.insert(ARRAY[1], ARRAYV[1]);
		m.swap(m2);
		assert(has(m, ARRAY[1], ARRAYV[1])  &amp;&amp;  has(m, ARRAY[2], ARRAYV[2])  &amp;&amp;
			has(m, ARRAY[3], ARRAYV[3])  &amp;&amp;  !m.contains(ARRAY[0]));
	    }
	    		} break; case 63: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
	    	m2.insert(ARRAY[2], ARRAYV[2]);
	    	m2.insert(ARRAY[3], ARRAYV[3]);
	    	m2.insert(ARRAY[1], ARRAYV[1]);
		m.swap(m2);
		assert(m2.size() == 2);
	    }
	    		} break; case 64: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
	    	m2.insert(ARRAY[2], ARRAYV[2]);
	    	m2.insert(ARRAY[3], ARRAYV[3]);
	    	m2.insert(ARRAY[1], ARRAYV[1]);
		m.swap(m2);
		assert(has(m2, ARRAY[0], ARRAYV[0])  &amp;&amp;  has(m2, ARRAY[1], ARRAYV[1])  &amp;&amp;
			!m2.contains(ARRAY[2])  &amp;&amp;  !m2.contains(ARRAY[3]));
	    }
	    		} break; case 65: {
	    KeyType k;
	    for (int n = 0; n &lt; SPEC_MAX; n++)
	    {
		assert(m.insert(k, DUMMYV));
		k += 'x';
	    }
	    assert(m.size() == SPEC_MAX);
			} break; case 66: {
	    KeyType k;
	    for (int n = 0; n &lt; SPEC_MAX; n++)
	    {
		assert(m.insert(k, DUMMYV));
		k += 'x';
	    }
	    assert(!m.insert(k, DUMMYV)  &amp;&amp;  m.size() == SPEC_MAX  &amp;&amp;  !m.contains(k));
	    		} break; case 67: {
	    assert(m.insert(DUMMY, DUMMYV));
	    for (int n = 0; n &lt; 10*SPEC_MAX; n++)
		assert(m.insertOrUpdate(DUMMY, DUMMYV));
	    assert(m.size() == 1);
	    		} break; case 68: {
	    KeyType k;
	    KeyType kfirst;
	    for (int n = 0; n &lt; SPEC_MAX; n++)
	    {
		if (n == 0)
		{
			kfirst = k;
			assert(m.insert(kfirst, DUMMYV));
		}
		else
			assert(m.insert(k, DUMMYV));
		k += 'x';
	    }
	    assert(!m.insert(k, DUMMYV));
	    m.erase(kfirst);
	    assert(m.insert(k, DUMMYV));
	    k += 'x';
	    assert(!m.insert(k, DUMMYV));
#ifdef TESTNEW
	    		} break; case 69: {
	      // This test checked that swap takes the same amount of time
	      // no matter how many items are in the Maps.
	    		} break; case 70: {
	    const int CAPACITY = 2;
	    Map m2(CAPACITY);
	    KeyType k;
	    for (int n = 0; n &lt; CAPACITY; n++)
	    {
		assert(m2.insert(k, DUMMYV));
		k += 'x';
	    }
	    assert(!m2.insert(k, DUMMYV));
			} break; case 71: {
	    const int CAPACITY = SPEC_MAX*2;
	    Map m2(CAPACITY);
	    KeyType k;
	    for (int n = 0; n &lt; CAPACITY; n++)
	    {
		assert(m2.insert(k, DUMMYV));
		k += 'x';
	    }
	    assert(!m2.insert(k, DUMMYV));
	    		} break; case 72: {
	      // This test checked that the destructor deletes the dynamic array.
	    		} break; case 73: {
	      // This test checked that empty Maps can be copied and properly
	      // destroyed.
	    		} break; case 74: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    {
		Map m2(m);
	    	m2.insert(ARRAY[3], ARRAYV[3]);
		assert(m2.size() == m.size()+1);
	    }
	    		} break; case 75: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    {
		Map m2(m);
	    	m2.insert(ARRAY[3], ARRAYV[3]);
		KeyType a[4] = { DUMMY, DUMMY, DUMMY, DUMMY };
		for (int n = 0; n &lt; m2.size(); n++)
		{
		    ValueType v;
		    m2.get(n, a[n], v);
		}
		assert(m2.size() == 4  &amp;&amp;  isPermutation(a, ARRAY, 4));
	    }
	    		} break; case 76: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    m.insert(ARRAY[2], ARRAYV[2]);
	    {
		Map m2(m);
	    	m2.insert(ARRAY[3], ARRAYV[3]);
		KeyType a[3] = { DUMMY, DUMMY, DUMMY };
		for (int n = 0; n &lt; m.size(); n++)
		{
		    ValueType v;
		    m.get(n, a[n], v);
		}
		assert(m.size() == 3  &amp;&amp;  isPermutation(a, ARRAY, 3));
	    }
	    		} break; case 77: {
	    {
		Map m2(2);
	    	m2.insert(ARRAY[0], ARRAYV[0]);
	    	m2.insert(ARRAY[1], ARRAYV[1]);
		Map m3(m2);
		assert(!m3.insert(ARRAY[2], ARRAYV[2]));
	    }
	    		} break; case 78: {
	      // This test checked that the assignment operator doesn't just
	      // copy a pointer.
	    		} break; case 79: {
	      // This test checked that empty Maps can be assigned and properly
	      // destroyed.
	    		} break; case 80: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
	    	m2.insert(ARRAY[2], ARRAYV[2]);
	    	m2.insert(ARRAY[3], ARRAYV[3]);
	    	m2.insert(ARRAY[4], ARRAYV[4]);
		m2 = m;
	    	m2.insert(ARRAY[5], ARRAYV[5]);
		assert(m2.size() == m.size()+1);
	    }
	    		} break; case 81: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
	    	m2.insert(ARRAY[3], ARRAYV[3]);
	    	m2.insert(ARRAY[4], ARRAYV[4]);
	    	m2.insert(ARRAY[5], ARRAYV[5]);
		m2 = m;
	    	m2.insert(ARRAY[2], ARRAYV[2]);
		KeyType a[3] = { DUMMY, DUMMY, DUMMY };
		for (int n = 0; n &lt; m2.size(); n++)
		{
		    ValueType v;
		    m2.get(n, a[n], v);
		}
		assert(m2.size() == 3  &amp;&amp;  isPermutation(a, ARRAY, 3));
	    }
	    		} break; case 82: {
	    m.insert(ARRAY[0], ARRAYV[0]);
	    m.insert(ARRAY[1], ARRAYV[1]);
	    {
		Map m2;
	    	m2.insert(ARRAY[3], ARRAYV[3]);
	    	m2.insert(ARRAY[4], ARRAYV[4]);
	    	m2.insert(ARRAY[5], ARRAYV[5]);
		m2 = m;
	    	m2.insert(ARRAY[2], ARRAYV[2]);
		KeyType a[2] = { DUMMY, DUMMY };
		for (int n = 0; n &lt; m.size(); n++)
		{
		    ValueType v;
		    m.get(n, a[n], v);
		}
		assert(m.size() == 2  &amp;&amp;  isPermutation(a, ARRAY, 2));
	    }
#endif
			}
	}
}

int main()
{
	cout &lt;&lt; "Enter test number: ";
	int n;
	cin >> n;
	testone(n);
	cout &lt;&lt; "Passed" &lt;&lt; endl;
}
