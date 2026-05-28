/*#include<iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_BUFFER = 1024;
const int MAX_LINES = 100;

char* lines[MAX_LINES]; //메모장의 각줄의 첫 주소를 저장하는 일차원배열
int line_count = 0;

bool openFile(const char* filePath) {
	ifstream file(filePath);
	if (!file.is_open()) {
		cout << "Error opening file: " << filePath << endl;
		return false;
	}

	char buffer[MAX_BUFFER];
	while (file.getline(buffer, sizeof(buffer)) && line_count < MAX_LINES) { //
		lines[line_count] = new char[strlen(buffer) + 1];
		strcpy(lines[line_count], buffer);
		//int strcpy(const char* st1, const char* st2)
		line_count++;
	}
	file.close();
	for (int i = 0; i < line_count; i++) {
		cout << lines[line_count] << endl;
	}
	return true;

}

int myStrcmp(const char* str1, const char* str2) {
	int i;
	for (i = 0; str1[i] != '\0'; i++) {
		
		if (str1[i] != str2[i]) {
			
			return 1;
	
		}
	}
	if (str2[i] == '\0') {
		return 0;
	}
	else {
		return 1;
	}
}


int main() {

	char command[100];
	char val1[100];

	//strcmp(command, open) == 0
	while (1) {
		cin >> command;
		
		if (myStrcmp(command, "open") == 0) {
			cin >> val1;
			openFile(val1);
		}
		else if (strcmp(command, "search") == 0) {
			cout << "search";
		}
		else if (strcmp(command, "change") == 0) {
			cout << "change";
		}
		else if (strcmp(command, "exit") == 0) {
			break;
		} 
	}
	return 0;
}*/

#include <iostream>
#include <fstream>
#include <ctime>



using namespace std;

const int MAX_BUFFER = 1024;
const int MAX_LINES = 100; //

char* lines[MAX_LINES];
int line_count = 0;

// 직접 구현한 문자열 길이 계산 함수
int myStrlen(const char* str) {
    int length = 0;
    while (*str++) length++;
    return length;
}

// 직접 구현한 문자열 복사 함수
void myStrcpy(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

// 직접 구현한 문자열 탐색 함수
char* myStrstr(const char* haystack, const char* needle) {
    if (!*needle) return (char*)haystack;
    for (; *haystack; ++haystack) {
        if (*haystack == *needle) {
            const char* h = haystack, * n = needle;
            for (; *n && *h == *n; ++h, ++n); //
            if (!*n) return (char*)haystack;
        }
    }
    return nullptr;
}

// 직접 구현한 문자열 비교 함수
int myStrcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

void myStrncpy(char* dest, const char* src, int n) {
    while (n > 0 && *src) {
        *dest++ = *src++;
        n--;
    }
    while (n > 0) {
        *dest++ = '\0';
        n--;
    }
}

// 파일 열기 및 로드
bool openFile(const char*filePath) {  //참조연산자 &로 바꿔서 해보기
    ifstream file(filePath);
    if (!file.is_open()) {
        cout << "Error opening file: " << filePath << endl;
        return false;
    }

    char buffer[MAX_BUFFER];
    while (file.getline(buffer, sizeof(buffer)) && line_count < MAX_LINES) {
        lines[line_count] = new char[myStrlen(buffer) + 1];
        myStrcpy(lines[line_count], buffer);
        line_count++;
    }
    file.close();
    return true;
}

// 단어 검색
void searchWord(const char* word) {
    typedef struct result {
        int row, col;
    }RESULT;

    RESULT result[1024];
    int resultN = 0;

    for (int i = 0; i < line_count; i++) {
        char* line = lines[i];
        char* pos = myStrstr(line, word);
        while (line != '\0') {
            int col = pos - line;

            result[resultN].col = col;
            result[resultN].row = i;
            resultN++;

            pos = myStrstr(pos + 1, word);
        }
    }
    cout << "==='" << word << "' search(" << resultN << ")===" << endl;
    for (int i = 0; i < resultN; i++) {
        if (i) cout << ", ";
        cout << "(" << result[i].row << ", " << result[i].col << ")";
    }
    cout << endl << endl;
}

// 단어 변경
void changeWord(const char* word1, const char* word2) {
    for (int i = 0; i < line_count; i++) {
        char* line = lines[i];
        int len = myStrlen(line);
        char* newLine = new char[len * 2]; // 충분한 공간 확보
        char* temp = newLine;
        char* pos;

        while ((pos = strstr(line, word1)) != nullptr) {
            int charsBefore = pos - line;
            myStrncpy(temp, line, charsBefore);
            myStrcpy(temp + charsBefore, word2);
            temp += charsBefore + myStrlen(word2);
            line = pos + myStrlen(word1);                        //남은 문장을 다시 line 으로 정의하고 다시 검사
        }
        myStrcpy(temp, line);
        delete[] lines[i];
        lines[i] = newLine;
    }
}


// 단어 삽입
void insertWord(int row, int col, const char* word) {
    if (row - 1 >= line_count) return;
    char* line = lines[row - 1];
    int lineLen = myStrlen(line);
    char* newLine = new char[lineLen + myStrlen(word) + 1];

    myStrncpy(newLine, line, col - 1);
    myStrcpy(newLine + col - 1, word);
    myStrcpy(newLine + col - 1 + myStrlen(word), line + col - 1);

    delete[] lines[row - 1];
    lines[row - 1] = newLine;
}

// 단어 삭제
void deleteWord(const char* word) {
    for (int i = 0; i < line_count; i++) {
        char* line = lines[i];
        char* result = new char[myStrlen(line) + 1];
        char* pos;

        while ((pos = myStrstr(line, word)) != nullptr) {
            int n = pos - line;  // 
            myStrncpy(result, line, n); 
            result += n;
            line = pos + myStrlen(word);
        }
        myStrcpy(result, line);
        delete[] lines[i];
        lines[i] = result;
    }
}

// 파일 저장
void saveFile(const char* filePath) {
    ofstream file(filePath); 
    if (!file.is_open()) {
        cout << "Error opening file to save: " << filePath << endl; //cout?cerr?
        return;
    }

    for (int i = 0; i < line_count; i++) {
        file << lines[i] << endl;
    }
    file.close();
}

// 메인 함수
int main() {
    char commandLine[MAX_BUFFER];
    char command[10], param1[MAX_BUFFER], param2[MAX_BUFFER];
    int row, col;

    while (true) {
        cout << "Enter command: ";
        cin >> command;
        if (myStrcmp(command, "exit") == 0) {
            cout << "Exit the progrwam" << endl;
            break;
        }
        if (myStrcmp(command, "open") == 0) {
           // cout << "lhe\n";
            cin >> param1;
            if (!openFile(param1)) {
                cout << "Failed to open file." << endl;
            }
        }
        if (myStrcmp(command, "search") == 0) {
            cin >> param1;
            searchWord(param1);
        }
        else if (myStrcmp(command, "change") == 0) {
            cin >> param1 >> param2;
            changeWord(param1, param2);
        }
        else if (myStrcmp(command, "insert") == 0) {
            cin >> row >> col >> param1;
            insertWord(row, col, param1);
        }
        else if (myStrcmp(command, "delete") == 0) {
            cin >> param1;
            deleteWord(param1);
        }
        else if (myStrcmp(command, "save") == 0) {
            cin >> param1;
            saveFile(param1);
        }
    }

    for (int i = 0; i < line_count; i++) {
        delete[] lines[i];
    }

    return 0;
}
