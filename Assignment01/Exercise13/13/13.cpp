#include <iostream>

using namespace std;
                                         
int main() {
    char input[101];
    char map[101];
    //대문자는 소문자로,소문자는 대문자로
    cout << "Enter the string to convert.: ";
    cin.getline(input, 101);

    for (int i = 0; i < 101; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {   // 대문자일때 소문자로
            map[i] = input[i] + 32;
        }
        else if (input[i] >= 'a' && input[i] <= 'z') {//소문자일때 대문자로
            map[i] = input[i] - 32;
        }
        else {
            map[i] = input[i];
        }
    }

    for (int i = 0; i < 101; i++) {
        if (map[i] == NULL) break;
        cout << map[i];
    }



}