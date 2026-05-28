#include <iostream>

using namespace std;

class Stack {
private:
    int top;
    int* arr;
    int capacity;

public:
    Stack(int size) {
        capacity = size;
        arr = new int[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] arr;
    }

    void push(int value) {
        if (top == capacity - 1) {
            cout << "Stack Overflow" << endl;
            return;
        }
        arr[++top] = value;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        return arr[top--];
    }

    int peek() {
        if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        return arr[top];
    }

    bool isEmpty() {
        return top == -1;
    }
};

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int evaluateExpression(const char* expression) {
    Stack numbers(100);
    Stack operators(100);

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] == ' ')
            continue;

        if (expression[i] == '(') {
            operators.push(expression[i]);
        }
        else if (expression[i] >= '0' && expression[i] <= '9') {    // ??
            int num = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                num = num * 10 + (expression[i] - '0');    //4 9    4 * 10 + 9
                i++;
            }
            numbers.push(num);
            i--;
        }
        else if (expression[i] == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                int operand2 = numbers.pop();
                int operand1 = numbers.pop();
                char op = operators.pop();

                switch (op) {
                case '+':
                    numbers.push(operand1 + operand2);
                    break;
                case '-':
                    numbers.push(operand1 - operand2);
                    break;
                case '*':
                    numbers.push(operand1 * operand2);
                    break;
                case '/':
                    numbers.push(operand1 / operand2);
                    break;
                }
            }
            operators.pop();
        }
        else {
            while (!operators.isEmpty() && precedence(operators.peek()) >= precedence(expression[i])) {
                int operand2 = numbers.pop();
                int operand1 = numbers.pop();
                char op = operators.pop();

                switch (op) {
                case '+':
                    numbers.push(operand1 + operand2);
                    break;
                case '-':
                    numbers.push(operand1 - operand2);
                    break;
                case '*':
                    numbers.push(operand1 * operand2);
                    break;
                case '/':
                    numbers.push(operand1 / operand2);
                    break;
                }
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.isEmpty()) {
        int operand2 = numbers.pop();
        int operand1 = numbers.pop();
        char op = operators.pop();

        switch (op) {
        case '+':
            numbers.push(operand1 + operand2);
            break;
        case '-':
            numbers.push(operand1 - operand2);
            break;
        case '*':
            numbers.push(operand1 * operand2);
            break;
        case '/':
            numbers.push(operand1 / operand2);
            break;
        }
    }

    return numbers.pop();
}

int main() {
    char expression[100];

    cout << "Enter the formula: ";
    cin.getline(expression, 100);

    int result = evaluateExpression(expression);

    cout << "Result" << result << endl;
 //return 0; ÇÊ¿ä??
}

