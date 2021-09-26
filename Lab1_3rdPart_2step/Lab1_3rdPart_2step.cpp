#include <iostream>
#include <stdarg.h>

using namespace std;
struct point {
    int x;
    int y;
};

bool is_convex(int, ...);
int calc(point&, point&, point&);

int main()
{
    if (is_convex(4, point{ 0, 2 }, point{ 0, -5 }, point{ -2, 2 }, point{ -1, -1 }))
        cout << "polygon is convex";
    else
        cout << "polygon is not convex";
}

bool is_convex(int count, ...)
{
    va_list argptr;
    __try
    {
        va_start(argptr, count);
        point first, second, last, prelast, p1, p2, p3;

        first = va_arg(argptr, point);
        second = va_arg(argptr, point);

        p1 = first;
        p2 = second;

        bool neg = false;
        bool pos = false;

        int crossProd = 0;

        for (; count - 2; count--)
        {
            p3 = va_arg(argptr, point);
            if (count - 2 == 2)
                prelast = p3;
            if (count - 2 == 1)
                last = p3;
            crossProd = calc(p1, p2, p3);
            if (crossProd < 0)
                neg = true;
            else if (crossProd > 0)
                pos = true;

            if (neg && pos) return false; // rotate in different corner
            p1 = p2;
            p2 = p3;
        }

        crossProd = calc(prelast, last, first);
        if (crossProd < 0)
            neg = true;
        else if (crossProd > 0)
            pos = true;

        if (neg && pos) return false;

        crossProd = calc(last, first, second);
        if (crossProd < 0)
            neg = true;
        else if (crossProd > 0)
            pos = true;

        if (neg && pos) return false;

        return true;
    }
    __finally
    {
        va_end(argptr);
    }
}


int calc(point& a, point& b, point& c)
{
    return (b.x - a.x)* (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
}