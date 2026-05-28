#include <iostream>

using namespace std;

int main() {
    double input, celing, floor, round;//입력이 소숫점 3자리까지만 존재한다고 치자

    cout << "Enter the floating-point number: ";
    cin >> input;
    int flag = 1;  //음수 연산을 위한 플래그

    double k;  //나중에 값을 바꿀때 저장해 놓을 자리이다. (음수는 올림과 내림 반올림을 따라갈 때 반대로 해주면 되서)




    if (input < 0) {
        flag = -1;    //음수 연산을 절대값 씌워서 해주기 위한 플래그
    }
    
    int temp = ((int)(input*flag * 1000)) % 10;// 1000을 곱해서 정수바꿔서 나머지 연산 해주면 일의자리 즉 올림 내림 반올림을 고려해줘야하는 자릿수만 떨어짐

    
    celing = flag * (((flag * input * 1000) - temp) / 1000.0 + 0.01);
    floor = flag * (((flag * input * 1000) - temp) / 1000.0);//걍 내림


   

    if (temp >= 5) {
        round = celing;
    }
    else {
        round = floor;
    }

    // 음수를 -1을 곱해서 양수바꾸고 올림, 내림을 해보면 원래 양수일 때랑 반대가 된다.
    // 예를 들어 -2.545(소수점 둘째자리까지)이면 내림을 하면 -2.55이다. 반면 2.545를 올림하면 2.55가된다. 

    if (flag == -1)
    {
        k = celing;
        celing = floor;
        floor = k;

    }
    

    cout << "Celing " << celing << endl;
    cout << "Floor " << floor << endl;
    cout << "Rounding " << round << endl;
    return 0;
}