#include "Map.h"
#include <iostream> 

Map::Map():m_len(0){
    m_head = new Node();
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
    m_tail = m_head;
}

Map::~Map(){
    for(Node* curr = m_head->m_next; curr != m_head; curr = curr->m_next)
	erase(curr->m_pair.m_key);
    delete m_head;
}

Map::Map(const Map& other){
    m_len = 0;//TODO
    m_head = new Node();
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
    m_tail = m_head;
    KeyType key;
    ValueType value;
    for(int i = 0; i < other.m_len; i++){
	other.get(i, key, value);
	this->insert(key, value);
    }
}

Map& Map::operator=(const Map& rhs){//TODO: why Map&
    if(this != &rhs){
	Map temp(rhs);
	swap(temp);
    }
    return *this;
}

bool Map::empty() const{
    return m_head->m_next == m_head;
}

int Map::size() const{
    return m_len;
}

bool Map::insert(const KeyType& key, const ValueType& value){
    for(Node* curr = m_head->m_next; curr != m_head; curr = curr->m_next){
	if(curr->m_pair.m_key == key)
	    return false;
    }

    Node* node = new Node();
    node->m_prev = m_tail; // hook new's prev to old tail
    node->m_next = m_head; // hook new's next to m_head

    node->m_prev->m_next = node; // hook old tail's next to new tail
    node->m_next->m_prev = node;
    m_tail = node;

    node->m_pair.m_key = key; // insert the key
    node->m_pair.m_value = value; // insert the value

    m_len++;
    return true;

}

bool Map::update(const KeyType& key, const ValueType& value){
    for(Node* curr = m_head->m_next; curr != m_head; curr = curr->m_next){
        if(curr->m_pair.m_key == key){
            curr->m_pair.m_value = value;
	    return true;
	}
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    return update(key, value)? true:insert(key, value); 
}

bool Map::erase(const KeyType& key){
    for(Node* curr = m_head->m_next; curr != m_head; curr = curr->m_next){
        if(curr->m_pair.m_key == key){
	    curr->m_prev->m_next = curr->m_next;
	    curr->m_next->m_prev = curr->m_prev;

	    if(curr == m_tail)// Special case
                m_tail = curr->m_prev;
	    delete curr;
	    m_len--;
	    return true;
	}
    }
    return false;
}

bool Map::contains(const KeyType& key) const{
    for(Node* curr = m_head->m_next; curr != m_head; curr = curr->m_next){
	if(curr->m_pair.m_key == key) 
	    return true;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const{
    for(Node* curr = m_head->m_next; curr != m_head; curr = curr->m_next){
	if(curr->m_pair.m_key == key){
	    value = curr->m_pair.m_value;
	    return true;
	}
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const{
    if(i < 0 || i >= m_len)
	return false;

    Node* curr = m_head->m_next;
    for(int j = 0; j < i; j++){
	curr = curr->m_next;
    }
    key = curr->m_pair.m_key; 
    value = curr->m_pair.m_value; 
    return true;
}

void Map::swap(Map& other){
    // swap m_len
    int tmp_len = m_len;
    m_len = other.m_len;
    other.m_len = tmp_len;

    // swap m_head; 
    Node* tmp_head = m_head;
    m_head = other.m_head;
    other.m_head = tmp_head;

    // swap m_tail;
    Node* tmp_tail = m_tail;
    m_tail = other.m_tail;
    other.m_tail = tmp_tail;
}

void Map::dump(){
    Node* curr = m_head->m_next;
    for(int i = 0; i < size(); i++){
	std::cerr << curr->m_pair.m_key  << " " << curr->m_pair.m_value << std::endl;
	curr = curr->m_next;
    }
}

bool combine(const Map& m1, const Map& m2, Map& result){
    bool combine_flag = true;
    Map tmp_result = m1;
    
    std::cerr << tmp_result.size() << " debugging " << std::endl;
    for(int i = 0; i < m2.size(); i++){
	KeyType key;
	ValueType value_m2;
	m2.get(i, key, value_m2);
	if(m1.contains(key)){
	    ValueType value_m1;
	    m1.get(key, value_m1);
	    if(value_m1 == value_m2){
	        continue;	
	    }
	    else{
		tmp_result.erase(key);
		combine_flag = false;
	    }
	}
	else{
	    tmp_result.insert(key, value_m2);
	}
    }

    for(int i = 0; i < tmp_result.size() ; i++){
	KeyType key;
	ValueType value;
	tmp_result.get(i, key, value);
        result.insertOrUpdate(key, value);
    }

    return combine_flag;
}

void subtract(const Map& m1, const Map& m2, Map& result){
    for(int i = 0; i < m1.size(); i++){
	KeyType key_m1;
	ValueType value_m1;
        m1.get(i, key_m1, value_m1); 
        if(!m2.contains(key_m1))
	    result.insertOrUpdate(key_m1, value_m1);
    }
}
