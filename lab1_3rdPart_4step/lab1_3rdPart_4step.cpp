#include <iostream>
#include <fstream>

using namespace std;

int gorner(int base, char* str);


int main(int argc, char** argv)
{
    char buf[BUFSIZ];
    char* fname = argv[1];
    ifstream fin(fname);
    ofstream fon("answer.txt");
    while (!fin.eof())
    {
        fin >> buf;
        int max_base = 0;
        char* p = buf;
        while(*p)
        {
            char bchr = *p;
            int current_base = (isdigit(bchr) ? bchr - '0' : toupper(bchr) - 'A' + 10);
            if (max_base < current_base) max_base = current_base;
            ++p;
        }
        max_base++;
        fon << buf << " - CC" << max_base << "; 10base- " << gorner(max_base, buf) << endl;
    }
}

int gorner(int base, char* str)
{
    int ans = 0;
    while (*str)
    {
        char bchr = *str;
        ans = ans * base + (int)(isdigit(bchr) ? bchr - '0' : toupper(bchr) - 'A' + 10);
        str++;
    }
    return ans;
}
