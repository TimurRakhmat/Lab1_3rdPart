#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <map>

using namespace std;

int find_sub(char*, char*);
map<char*, int> findtr(int (*)(char*, char*), char*, int, ...);
void print_map(map<char*, int>);

int main() 
{
    char substr[] = "";
    print_map(findtr(find_sub, substr, 3, "book.txt", "map.txt", "table.txt"));
}

int find_sub(char* substr, char* fname)
{
    ifstream fin(fname);
    char* p1 = substr;
    char* p2;
    char* buf1;
    char lChar;
    int count = 0;

    while (!fin.eof())
    {
        p2 = substr;
        while (*p2)
        {
            lChar = fin.get();
            if (*p2 != lChar)
                break;
            p2++;
        }
        if (!(*p2))
            count++;
    }
    return count;
}

map<char*, int> findtr(int (*find_sub)(char*, char*), char* substr, int fcount, ...)
{
    map<char*, int> dict;
    char* f_name;

    va_list argptr;
    va_start(argptr, fcount);
    int cnt = 0;
    for (; fcount; fcount--)
    {
        f_name = va_arg(argptr, char*);
        cnt = find_sub(substr, f_name);
        if (cnt)
            dict[f_name] =  cnt;
    }
    va_end(argptr);
	return dict;
}

void print_map(map<char*, int> dict)
{
    map <char*, int> ::iterator it = dict.begin();
    for (int i = 0; it != dict.end(); it++, i++) {
        cout << i + 1 << ") file " << it->first << " count: " << it->second << endl;
    }
}