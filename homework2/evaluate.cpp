#include "Map.h" 
#include <stack>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

int precedence(const char c){
    if(c == '/' || c == '*') return 2;
    else if(c == '+' || c == '-') return 1;
    else return -1;
}
bool isOperand(char c){
    return ('a' <= c && c <= 'z')? true:false;
}

bool isOperator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/')? true:false;
}

int catChar(const char c){

    if(c == ' ') return 0;
    else if(isOperand(c)) return 1;
    else if(c == '(') return 2;
    else if(c == ')') return 3;
    else if(isOperator(c)) return 4;
    else
        return -1;
}

bool isValid(const string& infix){
// Eliminate spaces
    string tmp_infix = infix;
    //tmp_infix = " " + tmp_infix + " ";
    for(string::iterator it = tmp_infix.begin(); it != tmp_infix.end(); it++){
        if(catChar(*it) == -1) return false;//TODO
    }
    cout << "-======" << tmp_infix << endl;

    stack<char> pad_string;
    pad_string.push(' ');
    for(string::iterator it = tmp_infix.begin(); it != tmp_infix.end(); it++){
        if(catChar(*it) == 4){
	    pad_string.push(' ');
	    pad_string.push(*it);
	    pad_string.push(' ');
	}
	else if(*it == '('){
	    pad_string.push(*it);
	    pad_string.push(' ');
	}
	else if(*it == ')'){
	    pad_string.push(' ');
	    pad_string.push(*it);
	}
	else if(*it == ' ')
	    it++;
	else
	    pad_string.push(*it);
    }
    pad_string.push(' ');

    string final_string;
    while(!pad_string.empty()){
        final_string += pad_string.top();
	pad_string.pop();
    }

    reverse(final_string.begin(), final_string.end());
    cout << final_string << endl;;
         
    tmp_infix = final_string;
	 /*
    tmp_infix = " " + tmp_infix + " ";
    cout << "happy" << endl;
    cout << tmp_infix << endl;
    for(string::iterator it = tmp_infix.begin(); it != tmp_infix.end(); it++){
        if(catChar(*it) == 4){  
	    cout << catChar(*it) << endl;
	    tmp_infix.insert(it, ' ');
	    tmp_infix.insert(it + 2, ' ');
	    it += 2;
	}
	else if(*it == '('){
	    tmp_infix.insert(it + 1, ' ');
	    it++;
	}
	else if(*it == ')'){
	    tmp_infix.insert(it, ' ');
	    it++;
	}
	
    }
    */

    cout << "tmp_infix = " << tmp_infix << endl;
    string::iterator prev = tmp_infix.begin();
    int count_open = 0;
    int count_close = 0;
    for(string::iterator it = tmp_infix.begin() + 1; it != tmp_infix.end(); prev = it, it++){
        if(*prev == ' ' && *it == ' ') return false;
	if(*it == '(') count_open++;
	if(*it == ')') count_close++;
    }

    if(count_open != count_close) return false;

    return true;
/*
    for(int)
    if(count_left != count_right) return false; // Pair the parenthese;

    int prev = 0;
    int count_left = 0;
    int count_right = 0;
    for(int i = 0; i < infix.size(); prev = i, i++){
        if(string[i] == "(") count_left++;
        if(string[i] == ")") count_right++;
	if(count_left < count_right) return false;

        if(isOperator(infix[prev] && isOperator(infix[i]))) return false;
        if(isOperand(infix[prev] && isOperand(infix[i]))) return false;
	if(infix[prev] == "(" && isOperator(infix[i])) return false;
	if(infix[i] == ")" && isOperator(infix[prev])) return false;
	if(infix[prev] == ")" && isOperand(infix[i]) return false;
	if(isOperand(infix[i]) && infix[i] == "(") return false;
	if(i == infix.size()-1 && isOperator(infix[i])) return false;
    }
    if(count_left != count_right) return false;
 */
}

/*
int evaluate(string infix, const Map& values, string postfix, int& result){

    stack<char> postfixStack;
    stack<char> operatorStack;
    char current;
    if(!isValid(infix)) return 999999;
    for(int i = 0; i < infix.size(); i++){
        char c = infix[i];
	int cat = catChar(c); 
	if(cat == 0) continue;
	switch(cat){
	    case 1:
	        postfixStack.push(c);
		break;
	    case 2:
	        operatorStack.push(c);
		break;
	    case 3:
	        while(operatorStack.top() != "("){
		    postfixStack.push(operatorStack.top());
		    operatorStack.pop();
		}
		operatorStack.pop();
		break;
	    case 4:
	        while(!operatorStack.emtpy() && operatorStack.top() != "(" && precedence(c) <= precedence(operatorStack.top())){
		    postfixStack.push(operatorStack.top());
                    operatorStack.pop();
		}
		operatorStack.push(c);
		break;
	    default:
	        break;
	}
    }
    while(!operatorStack.empty())
        postfixStack.push(operatorStack.top());
	operatorStack.pop();

    return postfix;
}
*/
void test_isValid(){
    assert(isValid("+") == false); 
    assert(isValid("+a") == false); 
    assert(isValid("") == false); 
    assert(isValid("(") == false); 
    assert(isValid(")") == false); 
    assert(isValid("()") == false); 
    assert(isValid("(a+b)#") == false); 
    assert(isValid("(a+b)/t") == true); 

    cout << "Passed all tests" << endl;
}


