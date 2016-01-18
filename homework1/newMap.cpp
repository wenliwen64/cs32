#include "newMap.h"
#include <iostream>
#include <cstdlib>

Map::Map(const int n){//TODO
    if(n < 0){
	std::cout << "n < 0!" << std::endl; 
	exit(1);
    }
    else{
	m_len = 0;
	m_max = n;
	m_kv = new kv[n];
    }
}

Map::~Map(){
    delete [] m_kv;
}

Map::Map(const Map& other):m_len(other.m_len), m_max(other.m_max){
     this->m_kv = new kv[other.m_max];
     for(int i = 0; i < other.m_len; i++){
	 this->m_kv[i].key = other.m_kv[i].key;
	 this->m_kv[i].value = other.m_kv[i].value;
     }
}

Map& Map::operator=(const Map& rhs){
    if (this != &rhs)
    {
	Map temp(rhs);
	swap(temp);
    }
    return *this;
}

bool Map::empty() const{
    if(m_len == 0)
        return true;
    else
        return false;
}

bool Map::insert(const KeyType& key, const ValueType& value){
    if(m_len == m_max)
        return false;
    else{
	for(int i = 0; i < m_len; i++){
	    if(key == m_kv[i].key)
	        return false;
	} 
	m_kv[m_len].key = key;
        m_kv[m_len].value = value;
	m_len++;
	return true;
    }
}

bool Map::update(const KeyType& key, const ValueType& value){
    for(int i = 0; i < m_len; i++){
        if(key == m_kv[i].key){
	    m_kv[i].value = value;
	    return true;
	}
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value){
    for(int i = 0; i < m_len; i++){
        if(key == m_kv[i].key){
	    m_kv[i].value = value;   
	    return true;
	}
    }

    if(m_len == m_max)
        return false;
    else{
	m_kv[m_len].key = key;
        m_kv[m_len].value = value;
	m_len++;
	return true;
    } 
}

bool Map::erase(const KeyType& key){
    for(int i = 0; i < m_len; i++){
        if(key == m_kv[i].key){
	    for(int j = i; j < m_len-1; j++){
	        m_kv[j].key = m_kv[j+1].key;
	        m_kv[j].value = m_kv[j+1].value;
	    }
	    return true;
	}
    } 
    return false;
}

bool Map::contains(const KeyType& key) const{
    for(int i = 0; i < m_len; i++){
        if(key == m_kv[i].key)
	    return true;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const{
    for(int i = 0; i < m_len; i++){
        if(key == m_kv[i].key){
	    value = m_kv[i].value;
	    return true;
	}
    }     
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const{
    if(0 <= i && i <= size()){
	key = m_kv[i].key;
	value = m_kv[i].value;
	return true;
    }
    else
        return false;
}

void Map::swap(Map& other){
    int tmp_max = other.m_max;
    other.m_max = this->m_max;
    this->m_max = tmp_max;

    int tmp = other.m_len;
    other.m_len = this->m_len;
    this->m_len = tmp;

    kv* tmp_kv = other.m_kv;
    other.m_kv = this->m_kv;
    this->m_kv = tmp_kv;
    /*
    for(int i = 0; i < DEFAULT_MAX_ITEMS; i++){
        KeyType tmp_key = other.m_kv[i].key;
	other.m_kv[i].key = this->m_kv[i].key;
	this->m_kv[i].key = tmp_key;

        ValueType tmp_value = other.m_kv[i].value;
	other.m_kv[i].value = this->m_kv[i].value;
	this->m_kv[i].value = tmp_value;
    }
    */
}

void Map::dump() const{
    for(int i = 0; i < m_len; i++){
	std::cerr << m_kv[i].key << " " << m_kv[i].value << std::endl;
    }
}
