#include <iostream>
#include <fstream>
#include "exceptionsMy.h"
#include <string>

using namespace std;

const auto LOG2N = 1/log(2);

// logfile variables
int number_insrtuction = 1;
bool is_trace = false;
ofstream tr_out;


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
int not_a(int);
int get_dig(char);
char get_chr(int);
const int dA = 'Z' - 'A' + 1;
unsigned int matrix[dA];


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
					if (is_trace)
						tr_out << number_insrtuction++ << ')' << buf << '\n';
					parser(buf);
					buf = "";
				}
		}
	}
	catch (MyException exc) {
		if (is_trace)
			tr_out << '\n' << exc.what() << endl;
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
		ans *= base;
		int der = get_dig(bchr);
		if (der >= base or der < 0)
			throw MyException("ERROR: incorrect base");
		ans += der;
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
	if (ans == "")
		ans += '0';
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
	return not_a(a) | b;
}

int reimplication(int a, int b)
{
	return implication(b, a);
}

int xnor(int a, int b)
{
	return (not_a(a) & not_a(b)) | (a & b);
}

int xor2(int a, int b)
{
	return a ^ b;
}

int koimplication(int a, int b)
{
	return not_a(implication(a, b));
}

int sheffer(int a, int b)
{
	return not_a(a) | not_a(b);
}

int pirs(int a, int b)
{
	return not_a(diz(a, b));
}

int not_a(int i)
{
	int p = (1 << (1 + (int)(log(i) * LOG2N))) - 1; // make binnary num: 111111...
	return (p ^ i);
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
			base = base * 10 + buf[i] - '0';
		else
			throw MyException("BAD INPUT EQUATION ERROR");
		i++;
	} while (i < ln - 1);
	if (buf[i] != ')')
		throw MyException("BAD INPUT EQUATION ERROR");

	if (base > 36 or base < 2)
		throw MyException("ERROR: incorrect base");

	char buf_per[64];
	printf("input %c: ", per);
	cin >> buf_per;
	matrix[per - 'A'] = gorner(base, buf_per);
	if (is_trace)
		tr_out << "input variable " << per << " - " << matrix[per - 'A'] << endl;
	return;
}

void write_pern(string buf)
{
	int ln = buf.length();
	if (ln < 5)
		throw MyException("BAD OUTPUT EQUATION ERROR");
	char per;
	if (buf[0] == '(' && isalpha(buf[1]) && buf[2] == ',')
		per = buf[1];
	else
		throw MyException("BAD OUTPUT EQUATION ERROR");

	int i = 3;
	int base = 0;
	do {
		if (isdigit(buf[i]))
			base = base * 10 + buf[i] - '0';
		else
			throw MyException("BAD OUTPUT EQUATION ERROR");
		i++;
	} while (i < ln - 1);
	if (buf[i] != ')')
		throw MyException("BAD OUTPUT EQUATION ERROR");

	if (base > 36 or base < 2)
		throw MyException("ERROR: incorrect base");

	cout << per << " - " << in_gorner(base, matrix[per - 'A']) << endl;
	if (is_trace)
		tr_out << "output variable " << per << " in base: " << base << endl;
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
	{
		matrix[ch - 'A'] = not_a(matrix[buf[1] - 'A']);
		if (is_trace)
			tr_out << "input variable " << buf[1] << ": " << matrix[buf[1] - 'A'] << " result: variable "\
			<< ch << ": " << matrix[ch - 'A'] << endl;
	}
	else
		throw MyException("UNNAR EQUATION ERROR");
}

void parser_bin(char ch, string buf)
{
	string op_vector[] = { "+", "&", "->", "<-", "~", "<>", "+>", "?", "!" };
	int (*func[])(int, int) = { con, diz, implication, reimplication, xnor, xor2, koimplication, sheffer, pirs };
	int op_cnt = 9;
	int ln = buf.length();
	if (ln > 4)
		throw MyException("BINNAR EQUATION ERROR");

	if (!(isalpha(buf[0]) and isalpha(buf[ln - 1])))
	{
		throw MyException("BINNAR EQUATION ERROR");
	}

	int a, b;
	a = matrix[buf[0] - 'A'];
	b = matrix[buf[ln - 1] - 'A'];

	for (int i = 0; i < op_cnt; i++)
	{
		if (buf.find(op_vector[i]) == 1 and op_vector[i].length() == ln - 2)
		{
			matrix[ch - 'A'] = func[i](a, b);
			if (is_trace)
				tr_out << "input variable " << buf[0] << ": " << a << ", " << buf[ln - 1] << ": " << b << " result: variable "\
				<< ch << ": " << matrix[ch - 'A'] << endl;
			return;
		}
	}

	throw MyException("BINNAR EQUATION ERROR");
}
