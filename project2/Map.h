#ifndef MAP_INCLUDED
#define MAP_INCLUDED
#include <string>
typedef std::string KeyType;
//typedef int KeyType;
typedef double ValueType;
//typedef std::string ValueType;

class Map{
    public:
	Map();
	~Map();
	Map(const Map& other);
	Map& operator=(const Map& rhs);
	bool empty() const;
	int size() const;
	bool insert(const KeyType& key, const ValueType& value);
	bool update(const KeyType& key, const ValueType& value);
	bool insertOrUpdate(const KeyType& key, const ValueType& value);
	bool erase(const KeyType& key);
	bool contains(const KeyType& key) const;
	bool get(const KeyType& key, ValueType& value) const;
	bool get(int i, KeyType& key, ValueType& value) const;
	void swap(Map& other);
	void dump() const;
    private:
	struct Pair{
	    KeyType m_key;
	    ValueType m_value;
	};
    private:
	struct Node{
	    Pair m_pair;
	    Node* m_prev;
	    Node* m_next;
	    Node():m_prev(nullptr), m_next(nullptr){
	    }
	};
    private:
	int m_len;
        Node* m_head;
	Node* m_tail;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);

#endif
