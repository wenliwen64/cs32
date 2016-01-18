#include "WeightMap.h"
#include <iostream> 

WeightMap::WeightMap(){
}

bool WeightMap::enroll(std::string name, double startWeight){
    if(startWeight >= 0)
	return m_map.insert(name, startWeight);
    else
	return false;
}

double WeightMap::weight(std::string name) const{
    double tmp_weight;
    if(m_map.get(name, tmp_weight))
	return tmp_weight; 
    else
	return -1;
}

bool WeightMap::adjustWeight(std::string name, double amt){
    if(m_map.contains(name)){
	if((weight(name) + amt) < 0)
	    return false;
	else
            return m_map.update(name, weight(name) + amt);
    }
    else
	return false;
}

int WeightMap::size() const{
    return m_map.size();
}

void WeightMap::print() const{
    std::string tmp_name;
    double tmp_weight;
    for(int i = 0; i < m_map.size(); i++){
	m_map.get(i, tmp_name, tmp_weight);
	std::cout << tmp_name << " " << tmp_weight << std::endl;
    }
}
