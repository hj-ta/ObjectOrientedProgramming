#include <iostream>
#include <time.h>

using namespace std;
int main() {
    srand(time(NULL));//난수 생성을 위한 rand 메서드 사용 전 선언, 시스템 시간으로 난수 seed 를 만듬
    int i, j;
    int avg = 0;
    int data[5][10];
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            data[i][j] = rand() % 99+1; //1~99까지의 난수 생성해서 저장해두기
            //cout<<data[i][j]<<" ";//확인용
        }
        // cout<<endl;
    }


    for (i = 0; i < 5; i++) {
        avg = 0;
        for (j = 0; j < 10; j++) {
            avg += data[i][j];
            if (j == 0) {//맨 처음에만 검사, 10미만이면 공백을하나 추가해서 출력
                if (data[i][j] < 10) {
                    cout << " ";
                }
                cout << data[i][j];
            }
            //////////////////////////////
            else {
                if (data[i][j] < 10) {//현재 수가 10 미만이면 공백 하나 추가
                    cout << " ";
                   /*
                    if (data[i][j - 1] < 10) {//이전에 출력됬던 수 역시 10자리 미만이면 공백 하나 추가
                        cout << " "; */
                    

                }
                cout << " " << data[i][j];
            }



        }
        //한 행의 출력이 끝남
        cout << " |";
        if (avg < 1000) {//행 총합이 1천 미만이면 공백 추가
            cout << " ";
        }
        cout << avg << " |";

        if (avg / 10 < 100) {//행 평균이 100 미만이면 공백 추가
            cout << " ";
        }
        if (avg / 10 < 10) {//행 평균이 10 미만이면 공백 추가
            cout << " ";
        }
        //반올림
        if (avg % 10 == 0) {//딱 나누어져 떨어지면
            cout << avg / 10 << endl;
        }
        else {//아니면
            if ((avg % 10) / 10.0 > 0.5) {
                cout << avg / 10 + 1 << endl;
            }
            else {
                cout << avg / 10 << endl;
            }
        }
    } 
 return 0;
}