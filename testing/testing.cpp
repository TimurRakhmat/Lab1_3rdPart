// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

void last() // ���������� �������� three()
{
    std::cout << "Start last\n";
    std::cout << "last throwing int exception\n";
    throw -1;
    std::cout << "End last\n";
 
}
 
void three() // ���������� �������� two()
{
    std::cout << "Start three\n";
    last();
    std::cout << "End three\n";
}
 
void two() // ���������� �������� one()
{
    std::cout << "Start two\n";
    three();
    std::cout << "End two\n";
}
 
void one() // ���������� �������� main()
{
    std::cout << "Start one\n";
    two();
    std::cout << "End one\n";
}
 
int main()
{
    std::cout << "Start main\n";
    try
    {
        one();
    }
    catch (int)
    {
         std::cerr << "main caught int exception\n";
    }
    std::cout << "End main\n";
 
    return 0;
}