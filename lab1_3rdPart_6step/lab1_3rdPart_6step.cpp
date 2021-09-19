#include <iostream>
#include <fstream>
#include "exceptionsMy.h"
#include <string>

using namespace std;

bool parser(string);
void read_pern(string);
void parser_neg(char, string);
void parser_bin(char, string);
void write_pern(string);
int gorner(int, char*);
string in_gorner(int, int);
int con(int, int);
int diz(int, int);
int implication(int, int);
int reimplication(int, int);
int xnor(int, int);
int xor2(int, int);
int koimplication(int, int);
int sheffer(int, int);
int pirs(int, int);
int get_dig(char);
char get_chr(int);
const int dA = 'Z' - 'A' + 1;
int matrix[dA];


int main(int argc, char** argv) 
{
	if (argc < 2)
	{
		cout << "ERROR: you didn't write file name";
		return -1;
	}

	char* fname = argv[1];
	char* tr_name = nullptr;
	ifstream fin(fname);
	ofstream tr_out;

	bool is_trace = false;
	if (argc > 2)
	{
		char* trace = argv[2];
		if (!strcmp(trace, "/trace"))
		{
			if (argc > 3)
			{
				tr_name = argv[3];
				is_trace = true;
			}
		}
	}

	if (is_trace)
	{
		tr_out.open(tr_name, 'w');
	}


	for (int i = 0; i < dA; i++)
		matrix[i] = 0;


	try
	{
		char b;
		int bracket_counter = 0;
		string buf = "";
		while (!fin.eof())
		{
			b = fin.get();

			if (b == '{')
			{
				bracket_counter++;
			}

			if (b == '}')
			{
				if (bracket_counter < 0)
					throw MyException("ERROR:lost left comment bracket");
				bracket_counter--;
				if (!bracket_counter)
					b = fin.get();
			}

			if (b == '%' and bracket_counter == 0)
			{
				while (b != '\n' and b != EOF)
					b = fin.get();
			}
			if (!bracket_counter)
				if (b != ';')
				{
					if (!isspace(b))
						buf += toupper(b);
				}
				else
				{
					parser(buf);
					buf = "";
				}
		}
	}
	catch (MyException exc) {
		cout << '\n' << exc.what() << endl;
	}
	catch (...) {
		cout << "\n for anything" << endl;
	}

	return 0;
}


bool parser(string buf)
{
	if (buf.find("READ") == 0)
	{
		read_pern(buf.substr(4));
	}
	else if (buf.find("WRITE") == 0)
		write_pern(buf.substr(5));
	else if (buf.find(":=") == 1 and isalpha(buf[0]))
	{
		string right = buf.substr(3);
		if (right.length() < 2)
			throw MyException("BAD INSTRUCTION ERROR");
		if (right.length() == 2)
			parser_neg(buf[0], right);
		else
			parser_bin(buf[0], right);
	}
	else
		throw MyException("BAD INSTRUCTION ERROR");

	return true;
}

int gorner(int base, char* str)
{
	int ans = 0;
	while (*str)
	{
		char bchr = *str;
		ans = ans * base + get_dig(bchr);
		str++;
	}
	return ans;
}

string in_gorner(int base, int num)
{
	string ans = "";
	while (num) {
		ans = get_chr(num % base) + ans;
		num /= base;
	}
	return ans;
}

int con(int a, int b)
{
	return a & b;
}

int diz(int a, int b)
{
	return a | b;
}

int implication(int a, int b)
{
	return ~a | b;
}

int reimplication(int a, int b)
{
	return implication(b, a);
}

int xnor(int a, int b)
{
	return (~a & ~b) | (a & b);
}

int xor2(int a, int b)
{
	return a ^ b;
}

int koimplication(int a, int b)
{
	return ~implication(a, b);
}

int sheffer(int a, int b)
{
	return ~a | ~b;
}

int pirs(int a, int b)
{
	return ~a & ~b;
}

void read_pern(string buf)
{
	int ln = buf.length();
	if (ln < 5)
		throw MyException("BAD INPUT EQUATION ERROR");
	char per;
	if (buf[0] == '(' && isalpha(buf[1]) && buf[2] == ',')
		per = buf[1];
	else
		throw MyException("BAD INPUT EQUATION ERROR");

	int i = 3;
	int base = 0;
	do {
		if (isdigit(buf[i]))
			base += base * 10 + buf[i] - '0';
		else
			throw MyException("BAD INPUT EQUATION ERROR");
		i++;
	} while (i < ln - 1);
	if (buf[i] != ')')
		throw MyException("BAD INPUT EQUATION ERROR");

	char buf_per[64];
	printf("input %c: ", per);
	cin >> buf_per;
	matrix[per - 'A'] = gorner(base, buf_per);
	return;
}

void write_pern(string buf)
{
	int ln = buf.length();
	if (ln < 5)
		throw MyException("BAD INPUT EQUATION ERROR");
	char per;
	if (buf[0] == '(' && isalpha(buf[1]) && buf[2] == ',')
		per = buf[1];
	else
		throw MyException("BAD INPUT EQUATION ERROR");

	int i = 3;
	int base = 0;
	do {
		if (isdigit(buf[i]))
			base += base * 10 + buf[i] - '0';
		else
			throw MyException("BAD INPUT EQUATION ERROR");
		i++;
	} while (i < ln - 1);
	if (buf[i] != ')')
		throw MyException("BAD INPUT EQUATION ERROR");

	cout << per << " - " << in_gorner(base, matrix[per - 'A']) << endl;
}


int get_dig(char bchr)
{
	return (int)(isdigit(bchr) ? bchr - '0' : toupper(bchr) - 'A' + 10);
}

char get_chr(int total)
{
	return (char)((total < 10) ? total + '0' : total + 'A' - 10);
}

void parser_neg(char ch, string buf)
{
	if (isalpha(buf[1]) and buf[0] == '/')
		matrix[ch - 'A'] = ~matrix[ch - 'A'];
}

void parser_bin(char ch, string buf)
{
	//op_vector =
}