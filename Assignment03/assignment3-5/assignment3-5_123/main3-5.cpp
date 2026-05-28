#include <iostream>
using namespace std;

// Term class (각 항을 구성)
class Term {
public:
    int coeff;   // 계수
    int exp;     // 차수
    Term* next;  // next 포인터(다음항 연결)

    //생성자(계수와 차수를 초기화, 다음항을 연결하는 포인터는 null로 초기화)
    Term(int c = 0, int e = 0, Term* n = nullptr) : coeff(c), exp(e), next(n) {}
};

// Polynomial class 
class Polynomial {
private:
    Term* head;  // 다항식의 첫 항

public:
    Polynomial() : head(nullptr) {}  //생성자

    ~Polynomial() {  //소멸자
        Term* current = head;
        while (current != nullptr) {
            Term* nextTerm = current->next;
            delete current;
            current = nextTerm;
        }
    }

    //addTerm 함수 ( 다항식에 새로운 항 추가 )
    void addTerm(int coeff, int exp) {
        Term* newTerm = new Term(coeff, exp); //동적할당으로 새로운 항 생성,
        //다항식이 비어있거나, 새로운 항의 차수가 기존의 최고차항보다 클 때
        if (head == nullptr || head->exp < exp) {
            //새로운 항을 head로 설정
            newTerm->next = head;
            head = newTerm;
        }
        else {
            Term* current = head;
            Term* prev = nullptr;
            //새로운 항의 자리를 찾기위한 탐색 로직
            while (current != nullptr && current->exp > exp) {
                prev = current;
                current = current->next;
            }
            //자리를 찾았는데 같은 차수의 항이 있는 경우
            if (current != nullptr && current->exp == exp) {
                current->coeff += coeff; //계수끼리 더해준다.
                //연산을 해 만약 계수가 0이 되면 list에서 항을 삭제
                if (current->coeff == 0) {
                    if (prev) prev->next = current->next;
                    else head = current->next;
                    delete current;
                }
                delete newTerm;
                //기존의 다항식의 항에 계수를 더해줬으니 newTerm 은 삭제
            }
            //자리를 찾았는데 같은 차수의 항이 없는 경우에 새로운 항을 삽입
            else {
                newTerm->next = current;
                if (prev) prev->next = newTerm;
                else head = newTerm;
            }
        }
    }

    void printPolynomial() const {
        //다항식이 비어있는 경우, 0인 경우
        if (head == nullptr) {
            cout << "0" << endl;
            return;
        }

        Term* current = head;

        while (current != nullptr) {//current 로 다항식을 순회
            //이거 양수 음수 출력양식 확인 ㄱ && current->coeff >0
            if (current != head) cout << " + ";

            if (current->coeff == 1 && current->exp == 0) {
                cout << "1";
            }

            if (current->coeff != 1 && current->coeff !=-1) {
                if (current->coeff < 0) cout  << current->coeff ;
                else cout << current->coeff;
            }
            //
            else if (current->coeff == -1 && current->exp != 0) {
                cout << "-";
            }

            if (current->exp != 0) {
                cout << "x^" << current->exp << " ";
            }
            current = current->next;
        }
        cout << endl;
    }

    // + 연산자 오버로드 함수 (두 다항식의 덧셈)
    Polynomial operator+(const Polynomial& rhs) const {
        Polynomial result;
        Term* term1 = this->head;
        Term* term2 = rhs.head;

        //result에 먼저 다항식1의 모든 항을 저장
        while (term1 != nullptr) {
            result.addTerm(term1->coeff, term1->exp);
            term1 = term1->next;
        }

        //result에 다항식2의 모든 항을 저장
        while (term2 != nullptr) {
            result.addTerm(term2->coeff, term2->exp);
            term2 = term2->next;
        }
        //resuit 반환
        return result;
    }

    // - 연산자 오버로드 함수 (두 다항식의 뺄셈)
    Polynomial operator-(const Polynomial& rhs) const {
        Polynomial result;
        Term* term1 = this->head;
        Term* term2 = rhs.head;

        //result에 먼저 다항식1의 모든 항을 저장
        while (term1 != nullptr) {
            result.addTerm(term1->coeff, term1->exp);
            term1 = term1->next;
        }

        //다항식 2는 계수에 모두 - 를 붙여서 저장
        while (term2 != nullptr) {
            result.addTerm(-term2->coeff, term2->exp);
            term2 = term2->next;
        }

        return result;
    }

    // 다항식의 미분값을 구하는 함수
    Polynomial derivative() const {
        Polynomial result;
        Term* current = head;

        //모든 항을 순회하며 연산
        while (current != nullptr) {
            // 항이 상수가 아닌 경우
            if (current->exp != 0) {
                // 미분 연산을 수행하고 결과를 result 에 저장
                result.addTerm(current->coeff * current->exp, current->exp - 1);
            }
            current = current->next; //다음항으로 이동
        }
        return result;
    }
};

int main() {

    /////////
    cout << "Test case 1 : 기본적인 다양식 연산" << endl;
    Polynomial poly1, poly2;
    poly1.addTerm(3, 4);  //poly1에 3 x^4 항 입력
    poly1.addTerm(2, 2);  //poly1에 2 x^2 항 입력

    poly2.addTerm(5, 3);  //poly2에 5 x^3 항 입력
    poly2.addTerm(1, 2);  //poly2에 1 x^2 항 입력

    cout << "Polynomial 1: ";
    poly1.printPolynomial();  //poly1 출력
    cout << "Polynomial 2: ";
    poly2.printPolynomial();  //poly2 출력

    // 두 다항식의 합 
    Polynomial polySum = poly1 + poly2;
    cout << "Sum of Polynomials: ";
    polySum.printPolynomial();

    // 두 다항식의 뺄셈
    Polynomial polyMinus = poly1 - poly2;
    cout << "Minus of Polynomials: ";
    polyMinus.printPolynomial();

    //poly1의 미분
    Polynomial poly1Derivative = poly1.derivative();
    cout << "Derivative of Polynomial 1: ";
    poly1Derivative.printPolynomial();

    //poly2의 미분
    Polynomial poly2Derivative = poly2.derivative();
    cout << "Derivative of Polynomial 2: ";
    poly2Derivative.printPolynomial();

    //////////////////////////////////////////////

    //Testcase2 : 입력한 계수에 음수가 있을 때
    cout << "\nTest case 2: 계수가 음수인 항이 있을 때" << endl;
    Polynomial poly3, poly4;
    poly3.addTerm(-4, 5); // poly3에 -4x^5 항 입력
    poly3.addTerm(2, 3);  // poly3에 2x^3 항 입력
    poly3.addTerm(-3, 2); // poly3에 -3x^2 항 입력
    poly3.addTerm(1, 1);  // poly3에 1x^1 항 입력
    poly3.addTerm(2, 0);  // poly3에 2x^0 항 입력

    poly4.addTerm(-3, 3); // poly4에 -3x^3 항 입력
    poly4.addTerm(6, 1);  // poly4에 6x^1 항 입력
    poly4.addTerm(-2, 2); // poly4에 -2x^2 항 입력
    poly4.addTerm(4, 0);  // poly4에 4x^0 항 입력
    poly4.addTerm(1, 6);  // poly4에 1x^6 항 입력

    cout << "Polynomial 3: ";
    poly3.printPolynomial(); // poly3 출력
    cout << "Polynomial 4: ";
    poly4.printPolynomial(); // poly4 출력

    // 두 다항식의 합
    Polynomial polySum2 = poly3 + poly4;
    cout << "Sum of Polynomials: ";
    polySum2.printPolynomial();

    // 두 다항식의 차를 구함
    Polynomial polyMinus2 = poly3 - poly4;
    cout << "Minus of Polynomials: ";
    polyMinus2.printPolynomial();

    // poly3의 미분
    Polynomial poly3Derivative = poly3.derivative();
    cout << "Derivative of Polynomial 3: ";
    poly3Derivative.printPolynomial();

    // poly4의 미분
    Polynomial poly4Derivative = poly4.derivative();
    cout << "Derivative of Polynomial 4: ";
    poly4Derivative.printPolynomial();

    ///////////////////////////////////////////

    // Test case 3: 모든 항의 계수가 0이 되는 경우
    cout << "\nTest case 3: 모든 항의 계수가 0이 되는 경우" << endl;
    Polynomial poly5, poly6;
    poly5.addTerm(3, 2);
    poly5.addTerm(-3, 2);
    poly5.addTerm(4, 5);
    poly5.addTerm(-4, 5);
    poly5.addTerm(6, 3);
    poly5.addTerm(-6, 3);

    poly6.addTerm(0, 1);
    poly6.addTerm(2, 4);
    poly6.addTerm(-2, 4);

    cout << "Polynomial 5: ";
    poly5.printPolynomial(); // poly5 출력
    cout << "Polynomial 6: ";
    poly6.printPolynomial(); // poly6 출력

    // 두 다항식의 합
    Polynomial polySum3 = poly5 + poly6;
    cout << "Sum of Polynomials: ";
    polySum3.printPolynomial();

    // 두 다항식의 차
    Polynomial polyMinus3 = poly5 - poly6;
    cout << "Minus of Polynomials: ";
    polyMinus3.printPolynomial();

    // poly5의 미분
    Polynomial poly5Derivative = poly5.derivative();
    cout << "Derivative of Polynomial 5: ";
    poly5Derivative.printPolynomial();

    // poly6의 미분
    Polynomial poly6Derivative = poly6.derivative();
    cout << "Derivative of Polynomial 6: ";
    poly6Derivative.printPolynomial();

    ///////////////////////////////////////////////////////////////////////

    // Test case 4: 차수가 높은 항이 있을 때
    cout << "\nTest case 4: 높은 차수의 항 추가" << endl;
    Polynomial poly7, poly8;
    poly7.addTerm(1, 100);
    poly7.addTerm(-1, 99);
    poly7.addTerm(3, 50);
    poly7.addTerm(2, 25);
    poly7.addTerm(5, 0);

    poly8.addTerm(5, 100);
    poly8.addTerm(3, 98);
    poly8.addTerm(-2, 50);
    poly8.addTerm(4, 25);
    poly8.addTerm(1, 1);

    cout << "Polynomial 7: ";
    poly7.printPolynomial(); //poly7 출력
    cout << "Polynomial 8: ";
    poly8.printPolynomial(); //poly8 출력

    //두 다항식의 합
    Polynomial polySum4 = poly7 + poly8;
    cout << "Sum of Polynomials: ";
    polySum4.printPolynomial();

    //두 다항식의 차
    Polynomial polyMinus4 = poly7 - poly8;
    cout << "Minus of Polynomials: ";
    polyMinus4.printPolynomial();

    // poly7의 미분
    Polynomial poly7Derivative = poly7.derivative();
    cout << "Derivative of Polynomial 7: ";
    poly7Derivative.printPolynomial();

    // poly8의 미분
    Polynomial poly8Derivative = poly8.derivative();
    cout << "Derivative of Polynomial 8: ";
    poly8Derivative.printPolynomial();

    return 0;
}
