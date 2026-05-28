#include <iostream>

using namespace std;

class Student {
private:
    char* name;
    char* studentID;
    double assignmentScore;
    double examScore;
    double attendance;
    double finalScore;

public:

    Student() { examScore = 5.5; }
    Student(char* name, char* id, double aScore, double eScore, double att) {}
    ~Student() {}
    bool isNameCorrect(char* name) {}
    void changeScores(double aScore, double eScore, double att) {}
    void print() {
        cout << examScore;
    }
};


int main() {

    Student* val = new Student(); 
    val ->print();


    return 0;

}