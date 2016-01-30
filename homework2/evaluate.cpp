#include "Map.h" 
#include <stack>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
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

    vector<char> pad_string;
    pad_string.push_back(' ');
    for(string::iterator it = tmp_infix.begin(); it != tmp_infix.end(); it++){
        if(catChar(*it) == 4){
	    pad_string.push_back(' ');
	    pad_string.push_back(*it);
	    pad_string.push_back(' ');
	}
	else if(*it == '('){
	    pad_string.push_back(*it);
	    pad_string.push_back(' ');
	}
	else if(*it == ')'){
	    pad_string.push_back(' ');
	    pad_string.push_back(*it);
	}
	else if(*it == ' ')
	    it++;
	else
	    pad_string.push_back(*it);
    }
    pad_string.push_back(' ');

    string final_string;
    for(vector<char>::iterator it = pad_string.begin(); it != pad_string.end(); it++){
         final_string += *it;
    }

    cout << final_string << endl;;
         
    tmp_infix = final_string;
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
}

int compute(char operand1, char operand2, char oper){
    switch(oper){
        case '+':
	    return operand1 + operand2;
	case '-':
	    return operand1 - operand2;
	case '*':
	    return operand1 * operand2;
	case '/':
	    if(operand2 == 0)
	    return operand1 / operand2;

	default:
    }
}

int eval_postfix(const string& postfix, int& result){
    stack<char> operandStack;
    for(string::iterator it = postfix.begin(); it != postfix.end(); it++){
        if(isOperand(*it))
	    operandStack.push(*it);
	else{// binary operator
	    char operand2 = operandStack.top();
	    operandStack.pop();
	    char operand1 = operandStack.top();
	    operandStack.pop();
	    compute(operand1, operand2, *it, result);
	}
    }
}

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
	        while(operatorStack.top() != '('){
		    postfixStack.push(operatorStack.top());
		    operatorStack.pop();
		}
		operatorStack.pop();
		break;
	    case 4:
	        while(!operatorStack.empty() && operatorStack.top() != '(' && precedence(c) <= precedence(operatorStack.top())){
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

    return eval_postfix(postfix, result);
}

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


