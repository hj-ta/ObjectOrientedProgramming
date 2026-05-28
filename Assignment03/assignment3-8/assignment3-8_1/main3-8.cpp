#include <iostream>
#include <string>

using namespace std;


//template 타입의 Node class 정의
template <typename T>
class Node {
private:
	Node<T>* m_Next;  // next Node를 가리키는 포인터
	T m_Data;  // Node 의 data

public:
	Node();  // 기본 생성자
	Node(T data) : m_Data(data), m_Next(nullptr) {}

	//data 반환
	T getData() const {
		return m_Data;
	}

	//next Node 반환
	Node<T>* getNext() const {
		return m_Next;
	}

	//nextNode 설정
	void setNext(Node<T>* nextNode) {
		m_Next = nextNode;
	}

	~Node() {}// 기본 소멸자
};

//template 타입의 Queue class 정의
template <typename T>
class Queue {
private:
	Node<T>* m_Front;  //Queue의 맨 앞 node
	Node<T>* m_Back;  //Queue의 맨 뒤 node

public:
	//생성자
	Queue() : m_Front(nullptr), m_Back(nullptr) {}  // 명시적 생성자

	//소멸자
	~Queue() {
		while (!isEmpty()) {
			dequeue();
		}
	}

	//데이터를 queue에 넣기
	void enqueue(T data) {
		Node<T>* node = new Node<T>(data);
		//큐가 비어있으면 new Node 가 front 이자 back node
		if (isEmpty()) {
			m_Front = m_Back = node;
		}
		//queue 가 비어있지 않은 경우
		else {
			m_Back->setNext(node); //back node 의 next로 설정해줌
			m_Back = node; //마지막 노드 선언
		}
	}

	//queue에서 data를 제거 (후 반환해 주는 함수)
	T dequeue() {
		//queue 가 비었으면 underflow 오류메세지 출력
		if (isEmpty()) {
			cout << "Queue Underflow";
			return T();  //T 타입 객체 반환(기본 생성된)
		}
		Node<T>* temp = m_Front;  //temp 생성 후 front 가리킴
		T data = temp->getData();  // 제거할 노드의 데이터 저장
		m_Front = temp->getNext();  // 제거를 위해 두 번째 노드를 첫 번째로 설정

		//Queue 가 비었다면 back 도 null로 초기화
		if (m_Front == nullptr) {
			m_Back = nullptr;
		}
		delete temp; // temp 노드 메모리 해제
		return data;  //데이터 반환_ dequeue
	}


	//Queue가 비었는지 확인 해 주는 함수
	bool isEmpty() {
		return m_Front == nullptr;
	}

	// Queue 의 front 반환 함수 (맨 앞)
	T front() {
		if (isEmpty()) {
			cout << "Queue Underflow";
			return T();
		}
		return m_Front->getData();
	}

	//print 함수
	void print() {
		Node<T>* current = m_Front;
		cout << "Queue: ";
		//모든 노드 돌면서 값 출력
		while (current) {
			cout << current->getData();  //현재 노드 데이터 출력
			if (current->getNext()) {
				cout << " -> ";
			}
			current = current->getNext();  //다음 노드로 이동
		}
		cout << endl;
	}
};

int main() {
	Queue<int> q;

	string command;
	int num;

	while (true) {
		cin >> command;
		if (command == "enqueue") {
			cin >> num;
			q.enqueue(num);
			//doubleQueue.enqueue(num);
		}
		else if (command == "dequeue") {
			//cin >> num;
			q.dequeue();
			//cout << q.dequeue() << endl;
		}
		else if (command == "front") {
			cout << q.front() << endl;
			//cout<<doubleQueue.front()<<endl;
		}
		else if (command == "print") {
			q.print();
			//doubleQueue.print();
		}
		else if (command == "exit") {
			break;
		}
		else {
			cout << "Invalid command" << endl;
		}
	}
	return 0;
}