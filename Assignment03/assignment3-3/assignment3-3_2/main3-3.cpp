#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>  // For strlen, strcmp, strcpy

using namespace std;

//Member 구조체
struct Member {
    char id[20];
    char password[20];
};

//member 관리 class
class MemberManagement {
private:
    Member* members;
    int size;  //member 수
    int capacity;  //용량
    const string fileName = "members.dat";
    char loggedInUser[20];  //로그인 한 아이디 표시하기위함

public:
    //생성자
    MemberManagement() : size(0), capacity(10) {
        members = new Member[capacity];
        loggedInUser[0] = '\0'; // 초기엔 로그인한 사람 x
        loadMembers();
    }

    //소멸자
    ~MemberManagement() {
        saveMembers();
        delete[] members;
    }

    //member 정보를 file에서 불러오는 함수
    void loadMembers() {
        ifstream file(fileName, ios::binary);  //binary 로 저장
        if (file.is_open()) {
            Member temp;
            while (file.read((char*)&temp, sizeof(Member))) {
                addMember(temp.id, temp.password, false, false); // 비밀번호 재암호화 방지
            }
            file.close();
        }
    }

    //member 정보 저장 함수
    void saveMembers() {//binar로 저장, trunc 로 덮어쓰기
        ofstream file(fileName, ios::binary | ios::trunc);
        if (file.is_open()) {
            for (int i = 0; i < size; i++) {
                file.write((char*)&members[i], sizeof(Member));
            }
            file.close();
        }
    }

    //add memeber vaild 검사 함수
    bool addMember(const char* id, const char* password, bool validate = true, bool encrypt = true) {
        if (findMember(id)) {// member 이미 존재하는지 검사
            cout << "ID already exists.";
            return false;
        }
        //password 유효성 검사
        if (validate && !validatePassword(password)) {
            cout << "Invalid password format.";
            return false;
        }
        //용량이 찼으면 그때마다 확장
        if (size == capacity) {
            expand();
        }
        //new member struct 생성
        Member newMember;
        strcpy(newMember.id, id);
        if (encrypt) {
            encryptPassword(newMember.password, password, newMember.id);
        }
        else {
            strcpy(newMember.password, password);
        }
        members[size++] = newMember;
        return true;
    }

    //findamember 함수, 이미 있는 id 인지 확인
    bool findMember(const char* id) {
        for (int i = 0; i < size; i++) {
            if (strcmp(members[i].id, id) == 0) {
                return true;
            }
        }
        return false;
    }

    //login 함수
    void login(const char* id, const char* password) { //입력받을 id, password
        for (int i = 0; i < size; i++) { //id 탐색
            if (strcmp(members[i].id, id) == 0) { //일치하는 id 를 찾으면
                char encryptedPassword[20];
                encryptPassword(encryptedPassword, password, id); //비밀번호 암호화, 암호화해야 비교가능
                if (strcmp(members[i].password, encryptedPassword) == 0) { //비밀번호도 일치하면
                    strcpy(loggedInUser, id);  //로그인한 id에 현재 id 저장
                    cout << "Login successful." << endl;
                    return;
                }
                break;
            }
        }
        cout << "Login failed. Invalid User id or password\n";
    }

    //logout 함수
    void logout() {
        loggedInUser[0] = '\0';
    }

    //회원탈퇴 함수
    void withdraw() {
        if (loggedInUser[0] == '\0') { //로그인한 상태인지 확인
            cout << "Invalid." << endl;
            return;
        }
        for (int i = 0; i < size; i++) { //로그인한 id와 일치하는 id 찾기
            if (strcmp(members[i].id, loggedInUser) == 0) {
                for (int j = i; j < size - 1; j++) {// 하나씩 땡겨서 저장하기
                    members[j] = members[j + 1];
                }
                size--; // 하나를 지웠으니 size--
                cout << "Successful withdraw.\n";
                logout();
                return;
            }
        }
    }

    //expand 함수
    void expand() {
        capacity *= 2;  //용량 x 2
        Member* newMembers = new Member[capacity];
        for (int i = 0; i < size; i++) {
            newMembers[i] = members[i];
        }
        delete[] members;
        members = newMembers;
    }

    //password 유효성 검사 함수
    bool validatePassword(const char* password) {
        bool hasAlpha = false, hasNum = false, hasSpecial = false; //알파벳, 숫자, 기호 여부 검사할것임
        int length = strlen(password); //password 길이 검사,strlen 사용
        if (length < 10 || length > 20) return false;  //길이 만족

        for (int i = 0; i < length; i++) {
            if (isalpha(password[i])) hasAlpha = true;  //알파벳 만족
            else if (isdigit(password[i])) hasNum = true; //숫자 만족
            else if (strchr("!@#$%^&*()", password[i])) hasSpecial = true; //특수기호 만족
        }
        //모두 만족할때만 ture를 return
        return hasAlpha && hasNum && hasSpecial;
    }

    //비밀번호 암호화 함수
    void encryptPassword(char* encrypted, const char* password, const char* id) {
        int key = strlen(id);  //id 길이가 비밀번호를 이동시킬 거리임
        for (int i = 0; password[i] != '\0'; i++) { //주어진 password 를 한글자씩
            if (isalpha(password[i])) {
                encrypted[i] = (password[i] + key) % 128;
            }//키 길이만큼 이동시키고 아스키코드의 끝인 127을 넘을 경우를 고려해 128 로나누어줌
            //if (encrypted[i] < 0) encrypted[i] += 128; 
            else {
                encrypted[i] == password[i];
            }
        }
        encrypted[strlen(password)] = '\0'; //마지막에 널문자
    }

    //menu 출력함수, main에서 하는게 아니라 함수로 만들어 빼줌
    void showMenu() {
        cout << "\n=====================" << endl;
        if (loggedInUser[0] != '\0') {  //
            cout << "Logged in user: " << loggedInUser << endl;
        }
        cout << "Menu." << endl;
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Withdraw\n";
        cout << "4. Exit\n";
        cout << " : ";
    }
};

//main  함수
int main() {
    MemberManagement system; // class 선언
    char id[20], password[20];
    int choice;  //메뉴 선택 번호

    do { //do while 을 쓴 이유는 처음엔 choice 를 입력받지 않고 한번 실행해야하기 때문
        system.showMenu();
        cin >> choice;

        switch (choice) {
            //login
        case 1:
            cout << "---------------------" << endl;
            cout << "User id: ";
            cin >> id;
            cout << "password: ";
            cin >> password;
            cout << "---------------------" << endl;
            system.login(id, password);
            cout << "---------------------" << endl;
            break;
            //register
        case 2:
            cout << "---------------------" << endl;
            cout << "User id: ";
            cin >> id;
            cout << "password: ";
            cin >> password;
            cout << "---------------------" << endl;
            cout << (system.addMember(id, password) ? "Registration successful." : "") << endl;
            cout << "---------------------" << endl;  //
            break;
            //withdraw
        case 3:
            cout << "---------------------" << endl;
            system.withdraw();
            cout << "---------------------" << endl;
            break;
            //exit
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid.\n";
        }

    } while (choice != 4);

    return 0;
}