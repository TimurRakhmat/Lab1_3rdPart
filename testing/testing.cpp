// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

char get_chr(int total)
{
    return (char)((total < 10) ? total + '0' : total + 'A' - 10);
}

string in_gorner(int base, int num)
{
    string ans = "";
    while (num) {
        ans = get_chr(num % base) + ans;
        num /= base;
    }
    if (ans == "")
        ans += '0';
    return ans;
}

 
int main()
{
    int a = 6;
    unsigned int b = 8;
    int p;

    for (int i = 0; i < 50; i++) {
        int g = (1 + (int)(log(i) / log(2)));
        p = (1 << g) - 1;
        cout << in_gorner(2, i) << " - "  << in_gorner(2, (p ^ i)) << " - " << g << endl;
    }
    return 0;
}