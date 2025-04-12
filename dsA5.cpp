#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename T>
class Stack {
private:
    T* arr; // storage
    int capacity;
    int topIndex; // point to the top element

    // dynamically resize the capacity of stack
    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i <= topIndex; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

public:
    Stack(int size = 10) : capacity(size), topIndex(-1) {
        arr = new T[capacity];
    }
    ~Stack() { delete[] arr; }
    bool isEmpty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }

    // return top element
    T top() const {
        if (isEmpty()) { return T(); }
        return arr[topIndex];
    }

    // insert new element to the top
    void push(const T& value) {
		// check capacity first
        if (topIndex == capacity - 1) {
            resize();
        }
        arr[++topIndex] = value;
    }

    // pop out top element
    void pop() {
        if (isEmpty()) { return; }
        --topIndex;
    }
};

// variables[<varName>] = <value>
unordered_map<char, double> variables;

// decides precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Shunting Yard Algorithm：infix -> postfix
vector<string> shuntingYard(const string &expression) {
    Stack<char> operators;
    vector<string> output;
    istringstream tokens(expression);
    char ch;
    
    while (tokens >> ch) {
        if (isdigit(ch)) { // number
            string operand(1, ch);
            bool hasDecimalPoint = false;

            // parse whole number
            while (tokens.peek() != EOF && (isdigit(tokens.peek()) || tokens.peek() == '.')) {
                if (tokens.peek() == '.') {
                    if (hasDecimalPoint) break; // actually should not have decimal again
                    hasDecimalPoint = true;
                }
                operand += tokens.get();
            }
            output.push_back(operand);
        } else if (isalpha(ch)) { // variables
            output.push_back(string(1, ch));
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
			// pop operators to output when there's something inside "operators"
			// and until meet the other parenthese
            while (!operators.isEmpty() && operators.top() != '(') {
                output.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.pop(); // remove '('
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			// pop operators to output when there's something inside "operators"
			// and compare precedences of THIS operator and operators' top element
            while (!operators.isEmpty() && precedence(operators.top()) >= precedence(ch)) {
                output.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.push(ch);
        }
    }
    
    while (!operators.isEmpty()) {
        output.push_back(string(1, operators.top()));
        operators.pop();
    }
    return output;
}

// calculate final answer
double evaluatePostfix(const vector<string> &postfix) {
    Stack<double> operandStack;
    cout << "postfix: ";
    for (const auto &token : postfix) {
		cout << token << " ";
        if (isdigit(token[0])) {
			// throw number to operand stack
            operandStack.push(stod(token));
        } else if (isalpha(token[0])) {
			// check if existed in variable list
            if (variables.count(token[0])) {
                operandStack.push(variables[token[0]]);
            } else {
				operandStack.push(0); // should not happen
			}
        } else {
			// encounter operator
			// pop two top elements and do operation
			// after that, put the result back to operand stack
            double b = operandStack.top(); operandStack.pop();
            double a = operandStack.top(); operandStack.pop();
            if (token == "+") operandStack.push(a + b);
            else if (token == "-") operandStack.push(a - b);
            else if (token == "*") operandStack.push(a * b);
            else if (token == "/") operandStack.push(a / b);
        }
    }
    
    return operandStack.top();
}

void processInput(const string &line) {
    if (line.find('=') != string::npos) {
		// <var_name> = <value>
        char var = line[0];
        string expr = line.substr(2); // arithmetic
        vector<string> postfix = shuntingYard(expr);
        double value = evaluatePostfix(postfix);
        variables[var] = value;
        cout << "\n" << var << " = " << value << "\n";
    } else {
		// pure arithmetic
        vector<string> postfix = shuntingYard(line);
        double value = evaluatePostfix(postfix);
        cout << "\n" << value << "\n";
    }
}

int main() {
	cout << "start\n";
	
    processInput("a = 8 + 2 * 3");
    processInput("b = 18 + 2 * 3");
	processInput("c = b / (8 - 3) ");
	processInput("d = b / (8.8 - 3.3) ");
	processInput("e = 1 / (2 + (3 - (4 + (5 - 6))))");
	return 0;
}
