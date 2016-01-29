#include "Map.h" 
#include <stack>

int evaluate(string postfix);
int evaluate(string infix, const Map& values, string postfix, int& result){

    stack<char> postfixStack;
    stack<char> operatorStack;
    char current;
    if(!isValid(infix)) return 999999;
    for(int i = 0; i < infix.size(); i++){
        c = infix[i];
	cat = catChar(c); 
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

int isValid(string infix){
// Eliminate spaces
    for(int i = 0; i < infix.size(); i++){
        if(string[i] = " ") infix.erase(infix.begin()+i);
        if(cat(string[i]) == 5) return false;//TODO
	if(string[i] == "(") count_left++;
	if(string[i] == ")") count_right++;
    }

    if(count_left != count_right) return false; // Pair the parenthese;

    int prev = 0;
    for(int i = 0; i < infix.size(); prev = i, i++){
        if(isOperator(infix[prev] && isOperator(infix[i]))) return false;
        if(isOperand(infix[prev] && isOperand(infix[i]))) return false;
	if(infix[prev] = "(" && isOperator(infix[i])) return false;
    }
}
int precedence(const char c){
    if(c == "/" || c == "*") return 2;
    else if(c == "+" || c == "-") return 1;
    else return -1;
}
bool isOperand(char c){
    return ("a" <= c && c <= "z")? true:false;
}

bool isOperator(char c){
    return (c == "+" || c == "-" || c == "*" || c == "/")? true:false;
}

int catChar(const char c){

    if(c == " ") return 0;
    else if(isOperand(c)) return 1;
    else if(c == "(") return 2;
    else if(c == ")") return 3;
    else if(isOperator(c)) return 4;
    else
        return -1;
}
