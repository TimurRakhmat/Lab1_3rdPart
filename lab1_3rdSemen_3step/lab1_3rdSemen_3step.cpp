#include <iostream>
#include <stdarg.h>

using namespace std;

double polynomial(double, int cnt, ...);

int main()
{
    cout << polynomial(3.0, 2, 1.0, 5.0, 1.0);
}

double polynomial(double x, int cnt, ...)
{
    va_list argptr;
    va_start(argptr, cnt);
    double ans = 0;
    for (; cnt + 1; cnt--)
    {
        ans = ans * x + va_arg(argptr, double);
    }
    return ans;
}
