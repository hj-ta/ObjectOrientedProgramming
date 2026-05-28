#include <iostream>

using namespace std;

int Perfect(int input) {
    int sum = 0;     //sum을 0으로 초기화

    if (input % 2 != 0)    
    {
        return -1;     //입력받은 수의 머듈러2 값이 0이 아닐경우 -1을주고 믿의 식이 실행되지 않도록 하는 역할을 한다.
    }
    else 
    {
        for (int i = 1; i < input; i++)  // 약수를 구하기위해 2로,3으로 ... 나누어 줄것임
        {
            if (input % i == 0) //나머지가 0이라면, 나누어 떨어진다면 약수니까 sum에 더해줌
            {
                sum += i;
            }
        }
        if (sum == input)
        {
            return input; // 나누며 약수를 구하는 연산을 끝까지 한거임
        }
        else 
        {
            return -1;
        }
    }

}


int main() {
    cout << "Perfect numbers between 1 and 1000: " << endl;

    for (int i = 1; i <= 1000; i++)    // 완전수가 맞는지 자기자신을 약수들의 합이 자기자신이 되는지 확인하는 식을 나열하여 써준다.
    {
        if (Perfect(i) != -1)
        {
            cout << i << " = ";

            for (int j = 1; j <= i / 2; j++) 
            {
                if (i % j == 0) 
                {
                    cout << j;

                    if (j == i / 2) 
                    {
                        ;
                    }
                    else 
                    {
                        cout << " + ";

                    }
                }

            }
            cout << endl;
        }



    }

}