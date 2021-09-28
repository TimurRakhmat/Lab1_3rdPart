#include <iostream>
#include <stdarg.h>

using namespace std;

int get_dig(char);
char get_chr(int);
void gorner_sum(int base, char* str, char** buf);
void calc(char**, int base, int count, ...);
void reverse(char* s);

int main()
{
    char* buf;
    calc(&buf, 16, 4, "1A", "1", "100000000000000000000000000000111", "1");
    reverse(buf);
    cout << buf << endl;
    free(buf);
}


void calc(char** bufptr, int base, int count, ...)
{
    char* buf = *bufptr;
    buf = (char*)calloc(BUFSIZ, sizeof(char));
    buf[0] = '0';
    char* current_dig;
    va_list argptr;
    va_start(argptr, count);
    for (; count; count--)
    {
        current_dig = va_arg(argptr, char*);
        gorner_sum(base, current_dig, &buf);
    }

    *bufptr = buf;
}


void reverse(char *s)
{
    int length = strlen(s);
    int c, i, j;

    for (i = 0, j = length - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


int get_dig(char bchr)
{
    return (int)(isdigit(bchr) ? bchr - '0' : toupper(bchr) - 'A' + 10);
}

char get_chr(int total)
{
    return (char)((total < 10) ? total + '0' : total + 'A' - 10);
}

void gorner_sum(int base, char* str, char **buf)
{
    int s1 = 0;
    int s2 = 0;
    bool ends2 = false;
    int rem = 0;
    int total = 0;
    int ln = strlen(str);

    for (int i = 0; i < ln ; i++)
    {
        char bchr = *(str + ln - 1 - i);
        char bchr2 = (ends2 ? '0': *(*buf + i));
        if (bchr2 == '\0') {
            ends2 = true;
            bchr2 = '0';
        }

        s1 = get_dig(bchr);
        s2 = get_dig(bchr2);
        total = s1 + s2 + rem;
        rem = total / base;
        total %= base;
        *(*buf + i) = get_chr(total);
    }

    if (ends2 and !rem)
    {
        *(*buf + ln) = '\0';
        return;
    }

    if (ends2 and rem)
    {
        *(*buf + ln) = get_chr(rem);
        *(*buf + ln + 1) = '\0';
        return;
    }

    while (*(*buf + ln))
    {
        rem += get_dig(*(*buf + ln));
        *(*buf + ln) = get_chr(rem % base);
        rem /= base;
        ln++;
    }

    if (rem)
        *(*buf + ln) = get_chr(rem);
    *(*buf + ln + 1) = '\0';

    return;
}