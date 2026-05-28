#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

//linked list 의 Node class 
template<typename T>
class Node {
public:
	T data;  //노드의 data
	Node<T>* next;  //다음 노드를 가리킬 포인터

	//생성자 _ 노드 를 처음 생성할 때 데이터를 초기화 하고, next 포인터를 null로 초기화
	Node(T data) :data(data), next(nullptr) {}
	
	~Node(){}//소멸자
	
};


//Stack class 정의
template<typename T>
class Stack {
private:
	Node<T>* m_Top;  //스택의 최상위 노드를 가리킴

public:
	Stack() :m_Top(nullptr) {} //생성자

	~Stack() { //소멸자 _ 모든 노드를 순차적으로 제거
		while (!isEmpty()) {
			pop();
		}
	}

	//push 함수 _ stack에 새로운 인자를 삽입
	void push(T data) {
		Node<T>* node = new Node<T>(data);
		node->next = m_Top;
		m_Top = node;
	}

	//stack이 비었는지 확인해주는 bool 함수
	bool isEmpty() {
		return m_Top == nullptr;
	}

	//pop 함수 _ stack의 최상위 노드를 제거
	T pop() {
		if (isEmpty()) {
			//Stack이 비어있을 경우에 출력메세지
			cout << "Stack Underflow";
			return -1;
		}
		Node<T>* node = m_Top;
		T data = node->data;
		m_Top = m_Top->next; //맨위에 값 삭제
		delete node;
		return data;  //삭제한 노드의 data 를 return
	}
	T top() {
		if (isEmpty()) {
			cout << "Stack Underflow";
			return -1;
			//throw std:: out_of_range("Stack Underflow");
		}
		return m_Top->data;
	}
	//출력함수
	void print() {
		cout << "Stack : ";
		Node<T>* current = m_Top;
		while (current) {
			cout << current->data; //T data 라고 해야하나?
			if (current->next) {
				cout << " -> ";
			}
			current = current->next;
		}
		cout << endl;
	}
};

int main() {

	//////int, double, char 타입 중 해당하는 stack과 input 타입을 선택////////


	Stack<int> s1;
	//Stack<double> s2;
	//Stack<char> s3;

	string command;

	int input; 
	//double input;
	//char input;

	while (true) {
		cin >> command;
		if (command == "push") {
			cin >> input;
			s1.push(input);
		}
		else if (command == "pop") {
			cout << s1.pop();
		}
		else if (command == "top") {
			cout << s1.top();
		}
		else if (command == "print") {
			s1.print();
		}
		else if (command == "isEmpty") {
			if (s1.isEmpty()) {
				cout << "Stack is empty" << endl;
			}
			else {
				cout << "Stack is not empty" << endl;
			}
		}
		else if (command == "exit") {
			break;
		}
		else {
			cout << "Invaild command" << endl;
		}
	}
	return 0;
}