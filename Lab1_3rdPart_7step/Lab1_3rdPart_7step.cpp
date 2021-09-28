#include <iostream>
#include <string>
#include <fstream>
#include "../lab1_3rdPart_6step/exceptionsMy.h"


using namespace std;

const int HASHSIZE = 128;
struct Node {
    string key="";
    string value="";
    Node* pnode = nullptr;
};


class HashTable
{
public:
	static const int HASHSIZE = 128;
	struct Node {
		string key = "";
		string value = "";
		Node* pnode = nullptr;
	};

	Node hashtable[HASHSIZE];
	void insert(const string, const string);
	string find(const string);
	int hash_func(const string, int);
	int get_dig(char bchr);
	int gorner(string, int, int);
	void deleteNodeList(int index);
	void delete_list();

	HashTable() {};
	~HashTable() {
		delete_list();
	}
};


int main(int argc, char** argv)
{
	//string gt[] = { "qeaE123", "qebE123", "qecE123","SDoisdf234", "24FN42ss", "39", "15" }; // (39 and 15) mod 128 == 67
	//string gt2[] = { "wqeaE123", "wqebE123", "wqecE123","wSDoisdf234", "w24FN42ss", "3339", "1115" };
	int ln_gt = 7;
	HashTable ht;
	/*
	for (int i = 0; i < ln_gt; i++)
	{
		ht.insert(gt[i], gt2[i]);
	}

	for (int i = 0; i < ln_gt; i++)
	{
		cout << ht.find(gt[i]) << endl;
	}*/

	if (argc != 2)
		throw MyException("ERROR missing input file");

	fstream fin(argv[1]);
	ofstream fout("__temp.txt");

	char b = '/0';
	bool end_ofdefine = false;
	string buf = "";
	string bufkey = "";
	string bufvalue = "";
	bool is_key = false;
	bool is_val = false;
	while (!fin.eof())
	{
		if (!end_ofdefine) {
			b = fin.get();
		}

		if (b != '#' and buf == "" and !end_ofdefine)
		{
			end_ofdefine = true;
			fin.seekg(-1, fin.cur);
			buf = "";
		}

		if (!end_ofdefine)
		{
			if (buf != "#define")
				buf += b;
			fout << b;

			if (b == '\n' or b == EOF)
			{
				if (bufkey == "" or bufvalue == "")
				{
					end_ofdefine = true;
					buf = "";
					continue;
				}
			}

			if (((string)"#define").find(buf) != 0)
			{
				end_ofdefine = true;
				continue;
			}

			if (!is_key and bufkey=="")
			{
				if (buf == "#define")
				{
					is_key = true;
				}
				continue;
			}

			if (isspace(b) and bufkey == "")
				continue;
			
			if (isspace(b))
				is_key = false;

			if (is_key)
			{
				bufkey += b;
				continue;
			}

			if (isspace(b) and bufvalue == "")
				continue;

			is_val = true;
			if (b == '\n' or b == EOF)
			{
				buf = "";
				ht.insert(bufkey, bufvalue);
				is_key = false;
				bufkey = "";
				bufvalue = "";
				continue;
			}

			bufvalue += b;
		}

		if (end_ofdefine)
		{
			b = fin.get();
			if (!isspace(b))
				buf += b;
			else
			{
				if (ht.find(buf) != "")
					fout << ht.find(buf);
				else
					fout << buf;
				buf = "";
			}

			if (isspace(b))
				fout << b;
		}
	}
}

void HashTable::insert(const string key, const string value)
{
	int index = hash_func(key, HASHSIZE);
	if (hashtable[index].key == "") {
		hashtable[index] = { key, value, nullptr };
		return;
	}

	Node* p = &hashtable[index];
	while (p->pnode != nullptr)
	{
		p = p->pnode;
	}
	p->pnode = new Node{ key, value, nullptr };
}

string HashTable::find(const string key)
{
	int index = hash_func(key, HASHSIZE);

	Node* p = &hashtable[index];
	while (p->key != key)
	{
		p = p->pnode;
		if (p == nullptr)
			return "";
	}

	return p->value;
}

int HashTable::hash_func(string buf, int siz)
{
    return gorner(buf, 62, siz);
}

int HashTable::get_dig(char bchr)
{
	if (isdigit(bchr))
		return bchr - '0';
	if (isalpha(bchr))
		if (bchr == toupper(bchr))
			return bchr - 'A' + 10;
		else
			return bchr - 'a' + 10 + 'Z' - 'A' + 1;
}

int HashTable::gorner(string str, int base, int siz)
{
	int ans = 0;
	int i = 0;
	int ln = str.length();
	while (i < ln)
	{
		char bchr = str[i];
		ans %= siz;
		ans *= base % siz;
		ans %= siz;
		int der = get_dig(bchr) % siz;
		ans += der;
		ans %= siz; // rules of mod sum and prod
		i++;
	}
	return ans;
}

void HashTable::deleteNodeList(int index)
{
	Node* p = hashtable[index].pnode;
	Node* pp = &hashtable[index];
	while (p->pnode != nullptr)
	{	
		pp = p;
		p = p->pnode;
	}
	pp->pnode = nullptr;
	delete p;
}

void HashTable::delete_list()
{
	for (int i = 0; i < HASHSIZE; i++) {
		while (hashtable[i].pnode != nullptr)
		{
			deleteNodeList(i);
		}
	}
}
