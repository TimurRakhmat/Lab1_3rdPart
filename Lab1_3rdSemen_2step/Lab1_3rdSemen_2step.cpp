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
    if (is_convex(5, point{ 2, 4 }, point{ -1, 8 }, point{ 0, 19 }, point{ 4, 14 }, point{ 3, 9 }))
        cout << "polygon is convex";
    else
        cout << "polygon is not convex";
}

bool is_convex(int count, ...)
{
    va_list argptr;
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

        if (neg && pos) return false; // произошел поворот в разные стороны
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

    va_end(argptr);
    return true;
}


int calc(point& a, point& b, point& c)
{
    return (b.x - a.x)* (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
}