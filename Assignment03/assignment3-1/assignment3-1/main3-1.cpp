#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//Node class 설정
class Node {
public:
	Node* next;
	int value;
	Node(int val): value(val),next(nullptr){} //초기화, 대괄호 안에 있어도 되지만,이게더 빠르게 연산, 보기에도 간결
};


//원형 리스트 class
class CircularLinkedList {
private:
	Node* head;
	int size;//노드개수
public:
	CircularLinkedList():head(nullptr),size(0){}//생성자

	~CircularLinkedList() { //소멸자,노드 소멸하는방법
		Node* current = head;
		if (current) {
			Node* next = nullptr;
			do { //head 부터 지우는식임
				next = current->next;
				delete current;
				current = next;
			} while (current != head);
		}
	}

	void initialize() {
		size = 10;
		Node* last = nullptr;
		int input_value;
		for (int i = 0; i < size; i++) {
			cin >> input_value;  //cin으로 값을 받을꺼임
			Node* newNode = new Node(input_value); //Node 생성자보면 input_value=val인거 알수있음
			if (!head) { //아무것도 없으면 newNode 가 head이자 last
				head = newNode;
				last = newNode;
			}
			else {
				last->next = newNode;
				last = newNode; //초기화 연산자, newNode가 가리키는 애가 last 가 됨, 반대는 x
			}
		}
		if (last) {
			last->next = head;
		}
	}

	void print() {
		if (!head) return;
		Node* current = head;
		do {
			cout << current->value << " ";
			current = current->next;
		} while (current != head); //하나 뛰어넘고 온거라 조건 무조건 충족
		cout << endl;
	}

	void transfer(int from, int to) {

		//from,to 가 잘못 입력된 경우
		if (from >= size || to >= size || from < 0 || to < 0) {
			cout << "Invaild" << endl;
			return; //함수 종료후, 값 반환
		}
		//from 노드 설정코드
		Node* fromNode = head;
		for (int i = 0; i < from; i++) {
			fromNode = fromNode->next;
		}
		//to 노드 설정코드
		Node* toNode = head;
		for (int i = 0; i < to; i++) {
			toNode = toNode->next;
		}
		//from, to 가 같은경우
		if (from == to) {
			cout << "Source and destination are the same. " << endl;
			return;
		}
		//transfer 메인로직
		Node* current = fromNode;
		int currentIndex = from;
		//current와 currentindex 설정

		while(true) {
			Node* nextNode = current->next; //current를 from에 두고 한칸씩 옆으로 옮김
			currentIndex = (currentIndex + 1) % size; //index 도 한칸씩 옮길건데 원형리스트 특성상 last 를 넘어갈 경우를 고려

			//연결 끊김 시뮬레이션
			if (rand() % 10 == 0) {
				int prevIndex = (currentIndex == 0) ? size - 1 : currentIndex - 1;
				//이건 9번과 0번사이에 끊어졌을 때를 고려해서 넣어준것
				//
				cout << "Detected a disconnection between" << prevIndex << " and " << currentIndex << endl;
				exit(1);
				//return;
			}
			current = nextNode;  //한칸 옮겨짐

			//from 이랑 to랑 같아졌는지 확인
			if (current == toNode) { //둘다 주소값을 담는 놈이라 == 써도됨,클래스 끼리x
				break;
			}
		}
		toNode->value = fromNode->value; //최종 목적지에 값 전달
	}
};


int main() {
	srand(time(nullptr));
	CircularLinkedList list;
	string command;
	int from, to;
	string temp;

	while (true) {
		cout << "Command : ";
		cin >> command;

		if (command == "initialize") {
			list.initialize(); //list.initialize; 이렇게 하면 그냥 함수의 주소값을 가리키는 포인터가 되더라
		}
		else if (command == "print") {
			list.print();
		}
		else if (command == "transfer") {
			cin >> from >> temp >> to;

			//cin>>from
			//cin>>ignore(4) 이렇게 해도 됨

			list.transfer(from, to);
		}
		else if (command == "exit") {
			break;
		}
		else {
			cout << "Invalid Command" << endl;
		}
	}

	return 0;
}