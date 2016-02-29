bool isQueue(const vector<int>& seq1, const vector<int>&^ seq2){
    for(vector<int>::iterator it1 = seq1.begin(); it1 != seq1.end(); it1++){
	for(vector<int>::iterator it2 = seq2.begin(); it2 != seq1.end(); it2++){`
	    if((*it1) = (*it2))
		break;
	    else
		return false;
	}
    }
         return true;
}

bool isStack(const vector<int>& seq1, const vector<int>&^ seq2){
    
    for(vector<int>::iterator it1 = seq1.begin(); it1 != seq1.end(); it1++){
	for(vector<int>::iterator it2 = seq2.end(); it2 != seq1.begin(); it2++){`
	    if((*it1) = (*it2))
		break;
	    else
		return false;
	}
    }
         return true;
}

2.1

head
p == nullptr;
p->next
p->num

2.2

current == nullptr
current
last_node
current->next
