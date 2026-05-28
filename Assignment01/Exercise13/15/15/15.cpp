#include <iostream>
#include <time.h>

using namespace std;

int main() {
    srand(time(NULL));//난수 생성

    int secret[4];    // 맞춰야할 정답 난수로 발생
    int guess[4] = { 0, };
    int chance = 5;

    for (int i = 0; i < 4; i++)
    {
        secret[i] = rand() % 10; //0~9까지의 난수 생성해서 저장해두기


        for (int j = 0; j < i; j++) {
            if (secret[i] == secret[j])  // 안에 값이 같을때, 즉 overlapping 을 방지하기 위하여
            {
                i--;
            }

        }

        guess[i] = 0;
    }

    //cout << secret[0] << secret[1] << secret[2] << secret[3] << "\n";
    int input;
    for (int i = 0; i < 5; i++)
    {
        cout << "Guess: ";
        cin >> input;
        int  hit = 0;
        int blow = 0;

        guess[0] = input / 1000;             //0번지 자릿수 뜯어내기 위한연산
        guess[1] = (input % 1000) / 100;     //1번지 숫자 뜯기
        guess[2] = (input % 100) / 10;       //2번지 숫자 뜯기
        guess[3] = input % 10;               //3번지 숫자 뜯기
        //cout << guess[0] << guess[1] << guess[2] << guess[3] << "\n";

        for (int j = 0; j < 4; j++) {
            if (secret[j] == guess[j]) {//정확한 위치에 정확한 수가 있으면 hit
                hit++;
            }
            else {                 
                for (int h = 0; h < 4; h++)          //블로우를 검사할것
                {
                    if (secret[j] == guess[h] && j != h)  //블로우를 검사, 그런데 위에서 s2=g2 처럼 같아지는 경우를 빼기위한 조건
                    {
                        blow++;
                        break;
                    }
                }
            }
        }


        cout << "Hit: " << hit << " Blow: " << blow << endl;
        cout << "------------------" << endl;
        cout << endl;

        if (hit == 4) {        //맞췄을때
            cout << "Win" << endl;
            break;
        }
        else
            chance--;

        if(chance == 0){
            cout << "Lose" << endl << endl;
            cout << "the correct answer: " << secret[0] << secret[1] << secret[2] << secret[3] << endl;
            break;
        }
        
    }
}



