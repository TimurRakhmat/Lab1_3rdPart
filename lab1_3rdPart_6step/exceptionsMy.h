#pragma once
#include <iostream>
#include <string>
#include <exception>

using namespace std;

class MyException : public exception
{
private:
    string error_text;

public:
    MyException(const string& _error_text) {
        error_text = _error_text;
    }
    const char* what() const noexcept {
        return error_text.c_str();
    }
};
