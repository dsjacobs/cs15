// compile: g++ -std=c++17 -Wall -Wextra -O0 -g scratch.cpp -o scratch
// run: : ./scratch


#include <iostream>
#include <cstring>
using namespace std;

char yonah[5] = {'y','o','n','a','h'};

// void countUpTo(int count) {
//     if (count < 0)
//             std::cout << "done" << std::endl;

//     return;

//     std::cout << "running next on: " << count - 1 << endl;
//     countUpTo(count - 1);
//     std::cout << count << std::endl;
//     }

bool isPalindrome(string s, int first, int last) {
    if (s[first] == s[last]) {isPalindrome(s,first+1, last-1);}
    else {return 0;}
    return 1;
}

int main(){
        countUpTo(10);

    // cout << "hello" << endl;
    // cout << yonah[3] << endl;
    // yonah[0] = 'j';
    // cout << yonah << endl;
    // char* yonahJ = new char[6];
    // cout << "moving " << *yonah << " to " << &yonahJ << endl;
    // for (int i=0; i<5; ++i) {
    //     yonahJ[i] = yonah[i];
    //     cout << "copied over letter: " << yonah[i] << endl;
    // }

    // char* myEmptyArray = new char[20];

    // cout << "new array: " << myEmptyArray << " at location " << &myEmptyArray << endl;




    return 0;

}