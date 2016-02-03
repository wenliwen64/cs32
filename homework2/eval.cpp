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

    vector<char> pad_string;
    pad_string.push_back(' ');
    for(string::iterator it = tmp_infix.begin(); it != tmp_infix.end(); it++){
        if(catChar(*it) == 4){ // operator
	    pad_string.push_back(' ');
	    pad_string.push_back(*it);
	    pad_string.push_back(' ');
	}
	else if(*it == '('){ // open parenthese
	    pad_string.push_back(*it);
	    pad_string.push_back(' ');
	}
	else if(*it == ')'){ // close parenthese
	    pad_string.push_back(' ');
	    pad_string.push_back(*it);
	}
	else if(*it == ' ')
	    continue;
	else{ // operand
	    pad_string.push_back(*it);
	}
    }
    pad_string.push_back(' ');

    string final_string;
    for(vector<char>::iterator it = pad_string.begin(); it != pad_string.end(); it++){
         final_string += *it;
    }

    //cerr << final_string << endl;;
         
    tmp_infix = final_string;
    //cerr << "tmp_infix = " << tmp_infix << endl;
    string::iterator prev = tmp_infix.begin();
    int count_open = 0;
    int count_close = 0;
    for(string::iterator it = tmp_infix.begin() + 1; it != tmp_infix.end(); prev = it, it++){
        if(*prev == ' ' && *it == ' ') return false; // Slick!
	if(*prev != ' ' && *it != ' ') return false; // Beautiful!
	if(*it == '(') count_open++;
	if(*it == ')') count_close++;
    }

    if(count_open != count_close) return false;

    return true;
}

int compute(int op1, int op2, char oper, int& result){
    switch(oper){
        case '+':
	    result = op1 + op2;
	    //cerr << op1 << " + " << op2 << " = " << result << endl;
	    break;
	case '-':
	    result = op1 - op2;
	    //cerr << op1 << " - " << op2 << " = " << result << endl;
	    break;
	case '*':
	    result = op1 * op2;
	    //cerr << op1 << " * " << op2 << " = " << result << endl;
	    break;
	case '/':
	    if(op2 == 0)
		return -1;
	    else{
		result = op1 / op2;
		//cerr << op1 << " / " << op2 << " = " << result << endl;
		break;
	    }
	default:
	    break;
    }
    return 0;
}

int eval_postfix(const string& postfix, int& result, const Map& m){
    stack<int> operandStack;
    for(string::const_iterator it = postfix.begin(); it != postfix.end(); it++){
        if(isOperand(*it)){
            int v;
	    m.get(*it, v);
	    operandStack.push(v);
	}
	else{// binary operator
	    int operand2 = operandStack.top();
	    //cerr << operand2 << " = operaend2 " << endl;
	    operandStack.pop();
	    int operand1 = operandStack.top();
	    //cerr << operand1 << " = operaend1 " << endl;
	    operandStack.pop();
	    int tmp_re;
	    if(compute(operand1, operand2, *it, tmp_re) != 0)
		return 3;
	    else
		operandStack.push(tmp_re);
	}
	//cerr << operandStack.top() << endl;
    }
    result = operandStack.top();
    //cerr << result << endl;
    return 0;
}

int evaluate(string infix, const Map& m, string& postfix, int& result){

    stack<int> postfixStack;
    stack<char> operatorStack;
    postfix = "";
    if(!isValid(infix)) return 1;
    

    for(int i = 0; i != infix.size(); i++){
        char c = infix[i];
	int cat = catChar(c); 
	if(cat == 0) continue; // discard spaces
	switch(cat){
	    case 1: // operand without unknown keys
	        postfixStack.push(c);
		//cerr << "stack " << c << endl;
		postfix += c;
		//cerr << postfix << " postfix" << endl;
		break;
	    case 2:
	        operatorStack.push(c);
		break;
	    case 3:
	        while(operatorStack.top() != '('){
		    postfixStack.push(operatorStack.top());
		    postfix += operatorStack.top();
		    //cerr << postfix << " postfix" << endl;
		    operatorStack.pop();
		}
		operatorStack.pop();
		break;
	    case 4:
	        while(!operatorStack.empty() && operatorStack.top() != '(' && precedence(c) <= precedence(operatorStack.top())){
		    postfixStack.push(operatorStack.top());
		    postfix  += operatorStack.top();
		    //cerr << postfix << " postfix" << endl;
                    operatorStack.pop();
		}
		operatorStack.push(c);
		break;
	    default:
	        break;
	}
    }

    while(!operatorStack.empty()){
        postfixStack.push(operatorStack.top());
        postfix += operatorStack.top();
	//cerr << postfix << " postfix" << endl;
	operatorStack.pop();
    }

    for(string::iterator it = infix.begin(); it != infix.end(); it++){
	if(isOperand(*it))
	    if(!m.contains(*it)){
		//cerr << "get out" << endl;
		return 2;
	    }
    }

    return eval_postfix(postfix, result, m);
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
    assert(isValid("a(a+b)/t") == false); 
    assert(isValid("aa") == false); 
    assert(isValid("(c+a)a") == false); 
    assert(isValid("a+ e") == true); 

    //cerr << "Passed all tests" << endl;
}

void test_eval_postfix(){
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
	m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    //assert(eval_postfix("yoau-*+", answer, m) == 0 && answer == -1);
    answer = 999;
    assert(eval_postfix("ae+", answer, m) == 0 && answer == -6);

}

int test_main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
	m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
	    pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate(")a(", m, pf, answer) == 1 && answer == 999);
    assert(evaluate(")(", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("(a- e)i", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("(a- e)(i)", m, pf, answer) == 1 && answer == 999);
    // unary operators not allowed;
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
	    pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
	    pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
	    pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
	    pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
	    pf == "a"  &&  answer == 3);
    cerr << "Passed all tests" << endl;
    return 0;
}


int main(){
    test_eval_postfix();
    test_isValid();
    test_main();
}
