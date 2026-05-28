#include <iostream>

using namespace std;

//Node class 정의
template<typename T>
class Node {
public:
    T data;   //Node 의 data
    int depth;  //Node 의 깊이
    Node<T>* left;  //왼쪽 자식노드 포인터
    Node<T>* right;  //오른쪽 자식노드 포인터

    //생성자
    Node(T data, int depth) : data(data), depth(depth), left(nullptr), right(nullptr) {}
    ~Node() { //소멸자
        delete left;
        delete right;
    }
};

//BST class
template<typename T>
class BST {
private:
    Node<T>* m_root;
    int maxDepth;

public:
    BST() : m_root(nullptr), maxDepth(0) {}
    ~BST() {
        delete m_root;
    }

    //BST build 함수
    void build(T arr[], int start, int end) {
        if (start > end) return;  //기저조건
        int mid = (start + end) / 2;
        //int mid = start + (end - start) / 2;  //mid index

        insert(arr[mid], 0);   //mid를 insert
        build(arr, start, mid - 1);  //왼쪽 자식노드 재귀적으로
        build(arr, mid + 1, end);  //오른쪽 자식노드 재귀적으로
    }

    //Node 삽입 함수
    void insert(T n, int depth) {
        if (!m_root) {  //root node가 없으면 생성
            m_root = new Node<T>(n, 0);
            return;
        }

        Node<T>* parent = nullptr;
        Node<T>* node = m_root;
        int nextDepth = m_root->depth;

        //insert 할 위치 탐색
        while (node) {
            parent = node;

            nextDepth = parent->depth + 1;
            if (maxDepth < nextDepth) maxDepth = nextDepth; //maxDepth 재정의

            if (n < node->data) node = node->left;  //값이 더 작으면 왼쪽 자식노드로 삽입
            else node = node->right;  //값이 더 크면 오른쪽 자식 노드로 삽입
        }

        //찾은 자리에 newNode 삽입
        if (n < parent->data) parent->left = new Node<T>(n, nextDepth);
        else parent->right = new Node<T>(n, nextDepth);

        //cout << endl << endl;
    }

    //Tree 출력함수
    void printTree() {
        printRec(m_root, 0);
    }

    //재귀적으로 출력
    void printRec(Node<T>* node, int currentDepth) {
        if (node == nullptr) {
            if (currentDepth <= maxDepth) cout << "  " << endl;
            return;
        }

        //오른쪽 자식 노드 부터 재귀적으로 출력, (안으로 들어가서)
        printRec(node->right, currentDepth + 1);

        //현재 node 출력
        for (int i = 0; i < node->depth * 5; i++) cout << " ";
        cout << node->data << endl;

        //이번엔 왼쪽 자식노드를 재귀적으로 호출 후 출력
        printRec(node->left, currentDepth + 1);
    }
};

int main() {
    int size;
    cout << "Enter the size of the input array: ";
    cin >> size;

    //유효하지 않은 배열 size 처리
    if (size <= 0) {
        cout << "Invalid array size.\n";
        return 1;
    }

    double* arr = new double[size];
    cout << "Enter " << size << " elements of the input array (sorted in ascending order):\n";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    BST<double> bst;
    bst.build(arr, 0, size - 1);
    bst.printTree();

    // 배열 메모리 해제
    delete[] arr;

    return 0;
}