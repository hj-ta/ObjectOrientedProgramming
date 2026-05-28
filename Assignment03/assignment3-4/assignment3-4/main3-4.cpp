#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

//Time class
class Time {
protected:
    int hour;
    int minute;
    int second;

public:
    Time(int hour = 0, int min = 0, int sec = 0) : hour(hour), minute(min), second(sec) {}
    ~Time() {} //소멸자

    //setTime 함수
    void setTime(int hour, int min, int sec) {
        this->hour = hour;
        this->minute = min;
        this->second = sec;
    }

    //addTome 함수
    void addTime(int sec) {
        this->second += sec;
        this->minute += second / 60;
        this->second %= 60;
        this->hour += minute / 60;
        this->minute %= 60;
        this->hour %= 24;
    }

    //pritnTime 함수
    void printTime() {
        printf("%02d:%02d:%02d\n", hour, minute, second);
    }
};

//Korea class
class Korea : public Time { //Time class 를 public 을 상속받아서 사용
public:
    Korea(int hour, int min, int sec) : Time(hour, min, sec) {}
    ~Korea() {}
};

class WashingtonDC : public Time {
public:
    WashingtonDC(int hour, int min, int sec) : Time(hour, min, sec) {}
    ~WashingtonDC() {}
};

class Paris : public Time {
public:
    Paris(int hour, int min, int sec) : Time(hour, min, sec) {}
    ~Paris() {}
};

class GreenwichObservatory : public Time {
public:
    GreenwichObservatory(int hour, int min, int sec) : Time(hour, min, sec) {}
    ~GreenwichObservatory() {}
};

void calculateTimes(Korea& kor, WashingtonDC& dc, Paris& paris, GreenwichObservatory& greenwich) {
    time_t now = time(0);
    tm* local = localtime(&now);  // 시스템의 로컬 시간
    tm* gmt = gmtime(&now);  // Utc 시간

    // UTC 시간 기준으로 한국 시간 설정 (UTC+9)
    kor.setTime((gmt->tm_hour + 9) % 24, gmt->tm_min, gmt->tm_sec);

    // UTC 시간 설정 (UTC+0)
    greenwich.setTime(gmt->tm_hour, gmt->tm_min, gmt->tm_sec);

    // UTC 시간 기준으로 워싱턴 DC 시간 설정 (UTC-4)
    dc.setTime((gmt->tm_hour - 4 + 24) % 24, gmt->tm_min, gmt->tm_sec);

    // UTC 시간 기준으로 파리 시간 설정 (UTC+2)
    paris.setTime((gmt->tm_hour + 2) % 24, gmt->tm_min, gmt->tm_sec);
}

int main() {
    //객체 선언(0으로 초기화, 안하면 이때 setting 이 고정되어버림)
    Korea korea(0, 0, 0);
    WashingtonDC dc(0, 0, 0);
    Paris paris(0, 0, 0);
    GreenwichObservatory greenwich(0, 0, 0);

    string command;
    int seconds;

    while (true) {
        cout << "Command: ";
        cin >> command;

        if (command == "setting") {
            calculateTimes(korea, dc, paris, greenwich);
        }
        else if (command == "add") {
            cin >> seconds;
            korea.addTime(seconds);
            dc.addTime(seconds);
            paris.addTime(seconds);
            greenwich.addTime(seconds);
        }
        else if (command == "print") {
            cout << "Output                " << endl;
            cout << "Korea                = "; korea.printTime();
            cout << "WashingtonDC         = "; dc.printTime();
            cout << "Paris                = "; paris.printTime();
            cout << "GreenwichObservatory = "; greenwich.printTime();
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
