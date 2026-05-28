#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class TaggerState {
public:
    virtual void toward() = 0;
};

class Back : public TaggerState {
public:
    void toward() override {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 1,3 });
        cout << "Forward.";
    }
};

class Front : public TaggerState {
public:
    void toward() override {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 1,3 });
        cout << "Tagger found out";

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 1,10 });
        cout << "Lose.." << "\n";

        _getch();
        exit(0);
    }
};

class Player {
private:
    TaggerState* state;
    int progress;

public:
    Player() : state(nullptr), progress(0) {}
    ~Player() {
        delete state;
    }

    void SetState(TaggerState* state) {
        delete this->state;
        this->state = state;
    }
    void toward() {
        state->toward();
        progress++;
    }

    int GetProgress() {
        return progress;
    }
};

void showIntro() {
    cout << "=========================" << endl;
    cout << " Red Light! Green Light! " << endl;
    cout << endl;
    cout << "     (Press any key)     " << endl;
    cout << "=========================" << endl;
    _getch();   //입력받아도 아무것도 안보이게 되는 함수
    system("cls");
}

int main() {
    showIntro();

    int phrase_cursor = 0;
    int temp = -1;
    int randNum;
    short cursor = 0;
    char input = '\0';
    int red_or_green = -1; // 1=red, -1=green
    int red_time = 2;

    Player* player = new Player();

    string phrase = "Green Light!";

    while (true) {

        time_t now = time(0); // To change the input of a rand function over time, you can use the 
        srand(now);

        // Measure the current time 
        char* dt = ctime(&now);
        string timeStr(dt);
        string sec = timeStr.substr(17, 2);

        // Perform  in 1-second increments

        if (temp != stoi(sec)) {
            temp = stoi(sec);

            // print 5 characters in 1 second 
            randNum = 2 + rand() % 5;


            // Prints a string to the console at a specified location 그린라이트 출력
            if (red_or_green == -1) {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(phrase_cursor + 1),0 });
                for (int i = phrase_cursor; i < phrase_cursor + randNum; i++) {
                    cout << phrase[i];
                    if (i >= phrase.size()) {
                        break;
                    }
                }
            }

            red_time--;

            //앞으로 가기
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,3 });
            cout << "\033[2K";

            if (input) {
                player->toward();
                input = '\0';
            }

            //상태바 출력
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,5 });
            cout << " start | ";
            for (int i = 0; i < player->GetProgress(); i++)
                cout << "@@";
            for (int i = 0; i < 20 - player->GetProgress(); i++)
                cout << "--";
            cout << " | end ";
            cout << " ( " << player->GetProgress() << "/20 )\n";

            phrase_cursor += randNum;


            //state 변경해야하는지 확인
            if (phrase_cursor > phrase.size() || red_time == 0) {  //turn 이 바뀌어야 할때
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
                cout << "\033[2K";
                if (red_or_green == 1) { // red light 상태라면
                    player->SetState(new Back());
                    red_time = -1;
                }
                else { //turn 이 green 에서 red 로 바뀔 때
                    player->SetState(new Front());
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 1,0 });
                    cout << "Red Light!";
                    red_time = 2 + rand() % 9;

                }
                phrase_cursor = 0;
                red_or_green *= -1;
            }

            //게임 끝났는지 확인
            if (player->GetProgress() == 20) {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 1,10 });
                cout << "Win!!" << "\n";
                _getch();
                exit(0);
            }
        }

        // Accept keyboard input 
        if (_kbhit()) input = _getch();
    }

    return 0;
}