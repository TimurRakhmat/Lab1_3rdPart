#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <map>
#include <string>

using namespace std;

int find_sub(string, char*);
bool find_sub_sub(string substr, string buf);
map<string, bool> findtr(int (*find_sub)(string, char*), string substr, int fcount, ...);
void print_map(map<string, bool>);

int main()
{
    string substr = "aus\nasu";
    if (substr == "")
        cout << "empty string" << endl;
    else
    {
        cout << "substr: " << substr << " was founded in that files: " << endl;
        print_map(findtr(find_sub, substr, 3, "book.txt", "map.txt", "table.txt"));
    }
}


void read_n(string& buf, int n, ifstream& fin)
{
    for (int i = 0; i < n; i++)
    {
        if (!fin.eof())
            buf += fin.get();
    }
}


int find_sub(string substr, char* fname)
{
    ifstream fin(fname);
    char p1 = '\0';
    char p2 = '\0';
    int sublen = substr.length();
    string buf;
    

    for (int i = 0; i < sublen; i++)
    {
        buf += ' ';
    }

    read_n(buf, sublen, fin);
    bool is_find = false;
    do
    {
        is_find = find_sub_sub(substr, buf);
        if (!is_find)
        {
            buf = buf.substr(sublen, sublen);
            read_n(buf, sublen, fin);
        }
        else
            return true;
    } while (!fin.eof());

    return is_find;
}


map<string, bool> findtr(int (*find_sub)(string, char*), string substr, int fcount, ...)
{
    map<string, bool> dict;
    char* f_name;

    va_list argptr;
    va_start(argptr, fcount);
    bool cnt = false;
    for (; fcount; fcount--)
    {
        f_name = va_arg(argptr, char*);
        cnt = find_sub(substr, f_name);
        if (cnt)
            dict[f_name] = cnt;
    }
    va_end(argptr);
    return dict;
}

bool find_sub_sub(string substr, string buf)
{
    int sublen = substr.length();
    int i = 0, j = 0;
    while (buf[i] != substr[0] and i < sublen)
    {
        i++;
    }
    if (i >= sublen)
        return false;

    for (int ii = i; j < sublen && ii < sublen*2; ii++, j++)
    {
        if (buf[ii] != substr[j])
            return false;
    }
    if (j == sublen)
        return true;

    return false;
}

void print_map(map<string, bool> dict)
{
    map <string, bool> ::iterator it = dict.begin();
    for (int i = 0; it != dict.end(); it++, i++) {
        cout << i + 1 << ") file " << it->first << endl;
    }
}