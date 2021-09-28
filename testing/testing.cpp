// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

 
int main()
{
    fstream fin("input.txt");
    while (!fin.eof())
    {
        string buf;
        getline(fin, buf);
        cout << buf << endl;
    }
}