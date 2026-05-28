#include <iostream>

using namespace std;
void separateStrings(const char* inputString, const char* delimiter) {
    char currentToken[101] = { '\0' }; //
    int currentTokenIndex = 0;
    int delimiterIndex = 0;

    for (int i = 0; inputString[i] != '\0'; ++i) {  //마지막 공백을 만나기 전까지 검사할꺼임
        if (inputString[i] == delimiter[delimiterIndex]) {
            delimiterIndex++;
            if (delimiter[delimiterIndex] == '\0') {
                currentToken[currentTokenIndex] = '\0';
                cout << currentToken << endl;
                currentTokenIndex = 0;
                delimiterIndex = 0;
            }
        }
        else {
            if (delimiterIndex > 0) {
                for (int j = 0; j < delimiterIndex; ++j) {
                    currentToken[currentTokenIndex++] = delimiter[j];
                }
                delimiterIndex = 0;
            }
            currentToken[currentTokenIndex++] = inputString[i];
        }
    }

    currentToken[currentTokenIndex] = '\0';
    cout<< currentToken << endl;
}

int main() {
    char inputString[101];
    char delimiter[11];

    cout << "Enter the string : ";
    cin.getline(inputString, 101);

    cout << "Enter the delimiter : ";
    cin.getline(delimiter, 11);

    cout << "Separated tokens :" << endl;
    separateStrings(inputString, delimiter);
//return 0; 필요한가?
}
