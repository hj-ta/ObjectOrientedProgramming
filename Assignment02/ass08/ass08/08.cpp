#include <iostream>

const int MAX_COMMAND_LENGTH = 100;
const int MAX_TOKENS = 6;
char command[MAX_COMMAND_LENGTH];
char* tokens[MAX_TOKENS];
int numTokens;

using namespace std;

int customStrlen(const char* str) {
    int length = 0;
    while (*str != '\0') {
        ++length;
        ++str;
    }
    return length;
}

char* customStrcpy(char* dest, const char* src) {
    char* originalDest = dest;
    while (*src != '\0') {
        *dest = *src;
        ++dest;
        ++src;
    }
    *dest = '\0';
    return originalDest;
}

double stringToDouble(const char* str) {
    double result = 0.0;
    bool isNegative = false;     // 음수 Flag
    bool isDecimal = false;      // 정수부 Flag
    double decimalMultiplier = 0.1;

    if (*str == '-') {
        isNegative = true;
        ++str;
    }

    while (*str != '\0') {
        if (*str == '.') {
            isDecimal = true;
            ++str;
            continue;
        }

        int digit = *str - '0';

        if (isDecimal) {     // 정수부 처리
            result += digit * decimalMultiplier;
            decimalMultiplier *= 0.1;
        }
        else {            //실수부 처리
            result = result * 10 + digit;
        }

        ++str;
    }

    if (isNegative) {
        result = -result;
    }

    return result;
}

class Student {
private:
    char* name = 0;
    char* studentID;  //cin.getline(
    double assignmentScore;
    double examScore;
    double attendance;
    double finalScore;

public:
    Student() {} //기본생성자

    Student(char* name, char* id, double aScore, double eScore, double att) {
        this->name = new char[customStrlen(name) + 1];
        customStrcpy(this->name, name);

        this->studentID = new char[customStrlen(id) + 1];
        customStrcpy(this->studentID, id);

        assignmentScore = aScore;
        examScore = eScore;
        attendance = att;
        calculateFinalScore();
    }

    ~Student() {
        delete[] name;
        delete[] studentID;
    }

    bool compareStrings(const char* str1, const char* str2) {
        while (*str1 && *str2) {
            if (*str1 != *str2)
                return false;
            str1++;
            str2++;
        }

        if (*str1 != *str2)
            return false;
        return true;
    }

    bool isNameCorrect(char* name) {
        cout << "isNameCorrect " << this->name << " " << name << endl;
        return compareStrings(this->name, name);
    }

    void changeScores(double aScore, double eScore, double att) {
        assignmentScore = aScore;
        examScore = eScore;
        attendance = att;
        calculateFinalScore();
    }

    void print() {
        cout << "Name : " << name << endl;
        cout << "Student ID : " << studentID << endl;
        cout << "Final Score : " << finalScore << endl;
        cout << "---------------" << endl;
    }

private:
    void calculateFinalScore() {
        finalScore = 0.1 * attendance + 0.4 * assignmentScore + 0.5 * examScore;
    }
};




bool compareStrings(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2)
            return false;
        str1++;
        str2++;
    }

    if (*str1 != *str2)
        return false;
    return true;
}

void splitString(const char* str, char delimiter, char* tokens[], int& numTokens) {
    numTokens = 0;
    const char* startToken = nullptr;
    const char* endToken = nullptr;

    while (*str == delimiter)
        ++str;

    startToken = str;

    while (*str != '\0') {
        if (*str == delimiter) {
            endToken = str;
            int tokenLength = endToken - startToken;
            tokens[numTokens] = new char[tokenLength + 1];

            for (int i = 0; i < tokenLength; ++i)
                tokens[numTokens][i] = startToken[i];
            tokens[numTokens][tokenLength] = '\0';
            ++numTokens;

            while (*(str + 1) == delimiter)
                ++str;

            startToken = str + 1;
        }
        ++str;
    }

    if (startToken != str) {
        int tokenLength = str - startToken;
        tokens[numTokens] = new char[tokenLength + 1];

        for (int i = 0; i < tokenLength; ++i)
            tokens[numTokens][i] = startToken[i];
        tokens[numTokens][tokenLength] = '\0';
        ++numTokens;
    }
}

int main() {
    const int MAX_STUDENTS = 10;
    int student_idx = 0;
    Student* students[MAX_STUDENTS];

    while (true)
    {
        cin.getline(command, MAX_COMMAND_LENGTH);
        splitString(command, ' ', tokens, numTokens);

        if (compareStrings(tokens[0], "insert")) {
            if (student_idx < MAX_STUDENTS)
            {
                students[student_idx] = new Student(tokens[1], tokens[2], stringToDouble(tokens[3]), stringToDouble(tokens[4]), stringToDouble(tokens[5]));
                student_idx++; 
            }
        }
        else if (compareStrings(tokens[0], "find")) {
            cout << "=====find=====" << endl;
        }
        else if (compareStrings(tokens[0], "change")) {
            for (int i = 0; i < student_idx; i++)
            {
                students[i]->isNameCorrect(tokens[1]);
                /*cout << "change " << students[i]->isNameCorrect(tokens[1]) << endl;
                if (students[i]->isNameCorrect(tokens[1])) {
                    students[i]->changeScores(stringToDouble(tokens[3]), stringToDouble(tokens[4]), stringToDouble(tokens[5]));
                    break;
                }*/
            }
        }
        else if (compareStrings(tokens[0], "print")) {
            cout << "=====print=====" << endl;
            for (int i = 0; i < student_idx; i++)
            {
                students[i]->print();
            }
        }
        else if (compareStrings(tokens[0], "exit")) {
            cout << "Exit the program" << endl;
            break;
        }
    }



    return 0;
}