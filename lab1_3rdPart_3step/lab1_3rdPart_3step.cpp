#include <iostream>
#include <stdarg.h>

using namespace std;

double polynomial(double, int cnt, ...);

int main()
{
    cout << polynomial(3.0, 3, 0.0, 2.0, 6.0, 1.0);
}

double polynomial(double x, int cnt, ...)
{
    va_list argptr;
    va_start(argptr, cnt);
    double ans = 0;

    for (; cnt + 1; cnt--)
    {
        ans *= x;
        ans += va_arg(argptr, double);
    }

    va_end(argptr);

    return ans;
}
