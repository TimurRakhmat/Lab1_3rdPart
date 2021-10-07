#include <iostream>
#include "../lab1_3rdPart_6step/exceptionsMy.h"
#include <fstream>
#include <vector>
#include <functional>
#include <string>
#include <map>


using namespace std;

class Instruct
{
public:
    static const int cnt_com = 10;
private:
    void pars_str(const string&);
    bool read_state(const string&, int);
    void print_rule(ostream& out);
    map <string, bool> is_set = {
        {"add", false},
        { "mult", false },
        { "sub", false },
        { "pow", false },
        { "div", false },
        { "rem", false },
        { "xor", false },
        { "input", false },
        { "output", false },
        { "=", false },
        { "order_ops", false },
        { "eq_left", false },
    };

public:
    map <string, string> rule = {   
        {"add", "add"},
        {"mult", "mult"},
        {"sub", "sub"},
        {"pow", "pow"},
        {"div", "div"}, 
        {"rem", "rem"}, 
        {"xor", "xor"},
        {"input", "input"}, 
        {"=", "="},
        {"output", "output"}
    };
    bool eq_left = true; // = pos
    bool op_left = true; // command pos
    bool bin_op_mid = false;
    string fname = "__last_instr.txt";
    string oname = "";
    Instruct(string fin);
    void init(string fin);
    Instruct();
    ~Instruct();
};

int add(int, int);
int mult(int, int);
int sub(int, int);
int pow(int, int);
int _div(int, int);
int rem(int, int);
int x_or(int, int);

int(*funcs[])(int, int) = { add, sub, pow, _div, rem, x_or, mult };

class InterpreterParser
{
public:
    InterpreterParser(const string& fname, Instruct &_inst);
private:
    vector<pair<string, int (*)(int, int)>> comms;
    void init_comms();
    map<string, int> vars;
    Instruct inst;
    void parse_line(const string& line);
    string parse_leq(const string& line); // variable behind =
    int parse_req(const string& line); // expression after =
    void parse_in_out(const string& line);
    int parse_in(const string& line);
    string parse_int(const string& line);
    void parse_out(const string& line);

    const vector<string> bin_comms = { "add", "sub", "pow", "div", "rem", "xor", "mult" };
    int (**func)(int, int) = funcs;
};

string strip(const string&);
int get_dig(char);
char get_chr(int);
int gorner(int, string);
string in_gorner(int, int);

int main(int argc, char** argv)
{
    try {

        if (argc < 2)
        {
            throw MyException("ERROR: file path not passed");
        }

        string fname = argv[1];
        string i_name = "";
        Instruct *_inst = nullptr;

        if (argc > 3)
        {
            char* trace = argv[2];
            if (!strcmp(trace, "/inst"))
            {
                if (argc > 3)
                {
                    i_name = argv[3];
                    _inst = new Instruct(i_name);
                    cout << "intstructions from " << fname << "were applied" << endl;
                }
            }
        }
        else
            {
                _inst = new Instruct();
                cout << "the default instructions were applied" << endl;
            }
        // command args
        
        InterpreterParser tip(fname, *_inst);
        
    }
    catch (MyException exc) {
        cout << '\n' << exc.what() << endl;
        exit(0);
    }
}

InterpreterParser::InterpreterParser(const string& fname, Instruct& _inst)
{
    inst = _inst;
    ifstream fin(fname);
    char b;
    int bracket_counter = 0;
    string buf = "";
    while (!fin.eof())
    {
        b = fin.get();

        if (b == '[')
        {
            bracket_counter++;
        }

        if (b == ']')
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
                if (isspace(b))
                    buf += ' ';
                else
                    buf += b;
            }
            else
            {
                parse_line(buf);
                buf = "";
            }
    }
}

void InterpreterParser::parse_line(const string& line) {
    string my_line = strip(line);
    int eq_pos = my_line.find(inst.rule["="]);
    int delta_eq = inst.rule["="].length();
    string lv = "";
    int rv = 0;
    if (eq_pos == -1)
        parse_out(my_line);
    else
    {
        if (inst.eq_left)
        {
            lv = parse_leq(strip(my_line.substr(0, eq_pos - 1)));
            if (my_line.find(inst.rule["input"]) != -1)
                cout << "enter " << lv << " : ";
            rv = parse_req(strip(my_line.substr(eq_pos + delta_eq)));
        }
        else
        {
            lv = parse_leq(strip(my_line.substr(eq_pos + delta_eq)));
            if (my_line.find(inst.rule["input"]) != -1)
                cout << "enter " << lv << " : ";
            rv = parse_req(strip(my_line.substr(0, eq_pos)));
        }

        vars[lv] = rv;
    }
}

string InterpreterParser::parse_leq(const string& line) { //y
    if (!line.empty() and line.find(' ') == -1 and !isdigit(line[0]))
    {
        int ln = line.length();
        for (int i = 0; i < ln; i++)
        {
            char c = line[i];
            if (!isalpha(c) and !isdigit(c) and (c != '_'))
            {
                string ex = "ERROR: " + line + "- bad variable name";
                throw MyException(ex);
            }
        }
        return line;
    }
    string ex = "ERROR: " + line + "- bad variable name";
    throw MyException(ex);
}

string InterpreterParser::parse_int(const string& line) { //y
    if (!line.empty() and line.find(' ') == -1)
    {
        int ln = line.length();
        int i = 0;
        if (line[0] == '-')
            i++;
        for (; i < ln; i++)
            if (!isdigit(line[i]))
            {
                string ex = "ERROR: " + line + " - incorect num";
                throw MyException(ex);
            }
        return line;
    }
    string ex = "ERROR: " + line + "- bad variable name";
    throw MyException(ex);
}

int InterpreterParser::parse_req(const string& line) { //x
    if (line.find(inst.rule["input"]) != -1)
        return parse_in(line);

    int ln = line.length();
    int pos = -1;
    int num = -1;
    string com = "";
    for (int i = 0; i < Instruct::cnt_com - 3; i++)
    {
        pos = line.find(inst.rule[bin_comms[i]]);
        if (pos != -1)
        {
            num = i;
            com = bin_comms[i];
            break;
        }
    }
    if (pos == -1)
    {
        string ex = "ERROR: " + line + " - unknown command";
        throw MyException(ex);
    }
    if (inst.bin_op_mid)
    {
        if (pos > 0 and (pos + inst.rule[com].length() < ln - 1))
        {
            string lv1 = parse_leq(strip(line.substr(0, pos - 1)));
            string lv2 = parse_leq(strip(line.substr(pos + inst.rule[com].length() + 1)));
            return func[num](vars[lv1], vars[lv2]);
        }
        string ex = "ERROR: " + line + " - unknown command";
        throw MyException(ex);
    }

    int pos_rb = line.rfind(')');
    int pos_lb = line.find('(');

    if (inst.op_left) {
        if (pos != 0 or pos_rb != ln)
        {
            string ex = "ERROR: " + line + " - bad operation position";
            throw MyException(ex);
        }
    }
    else
        if (pos + inst.rule[com].length() != ln or pos_lb != 0)
        {
            string ex = "ERROR: " + line + " - bad operation position";
            throw MyException(ex);
        }

    if (pos_lb != line.rfind('(') or line.find(')') != pos_rb)
    {
        string ex = "ERROR: " + line + " - bad operation position";
        throw MyException(ex);
    }
    string eq = strip(line.substr(pos_lb + 1, pos_rb - pos_lb - 1));
    string lv1 = "";
    string lv2 = "";
    int pos_ap = eq.find(',');
    if (pos_ap == -1)
    {
        string ex = "ERROR: " + line + " - unknown command";
        throw MyException(ex);
    }
    else
    {
        lv1 = parse_leq(strip(eq.substr(0, pos_ap)));
        lv2 = parse_leq(strip(eq.substr(pos_ap + 1)));
        return func[num](vars[lv1], vars[lv2]);
    }
}

void InterpreterParser::parse_out(const string& line) {
    string _out = inst.rule["output"];
    int pos = line.find(_out);
    int ln = line.length();
    int pos_rb = line.rfind(')');
    int pos_lb = line.find('(');
    if (pos == -1)
    {
        string ex = "ERROR: " + line + " - unknowd command";
        throw MyException(ex);
    }

    if (inst.bin_op_mid and pos > 0 and (pos + _out.length() < ln - 1))
    {
        string lv = parse_leq(strip(line.substr(0, pos)));
        string base_str = strip(line.substr(pos + _out.length()));
        int base = 10;
        base = gorner(10, base_str);
        if (base < 2 or base > 36)
        {
            string ex = "ERROR: " + in_gorner(10, base) + "base out of range[2, 36]";
            throw MyException(ex);
        }
        cout << in_gorner(base, vars[lv]) << endl;
        return;
    }

    if (inst.op_left) {
        if (pos != 0 or pos_rb != ln - 1)
        {
            string ex = "ERROR: " + line + " - bad operation position";
            throw MyException(ex);
        }
    }
    else
        if (pos + _out.length() != ln or pos_lb != 0)
        {
            string ex = "ERROR: " + line + " - bad operation position";
            throw MyException(ex);
        }
    
    if (pos_lb != line.rfind('(') or line.find(')') != pos_rb)
    {
        string ex = "ERROR: " + line + " - bad operation position";
        throw MyException(ex);
    }
    string eq = strip(line.substr(pos_lb + 1, pos_rb - pos_lb - 1));
    string lv = "";
    int base = 10;
    int pos_ap = eq.find(',');
    if (pos_ap == -1)
        lv = parse_leq(eq);
    else
    {
        lv = parse_leq(strip(eq.substr(0, pos_ap)));
        base = gorner(10, parse_int(strip(eq.substr(pos_ap + 1))));
    }
    if (base < 2 or base > 36)
    {
        string ex = "ERROR: " + in_gorner(10, base) + "base out of range[2, 36]";
        throw MyException(ex);
    }
    cout << in_gorner(base, vars[lv]) << endl;
}

int InterpreterParser::parse_in(const string& line) {
    string _in = inst.rule["input"];
    int pos = line.find(_in);
    int ln = line.length();
    int pos_rb = line.rfind(')');
    int pos_lb = line.find('(');
    if (pos == -1)
    {
        string ex = "ERROR: " + line + " - unknowd command";
        throw MyException(ex);
    }
    if (_in == line)
    {
        string snum = "";
        cin >> snum;
        return gorner(10, snum);
    }
    if (inst.op_left) {
        if (pos != 0 or pos_rb != ln - 1)
        {
            string ex = "ERROR: " + line + " - bad operation position";
            throw MyException(ex);
        }
    }
    else
        if (pos + _in.length() != ln or pos_lb != 0)
        {
            string ex = "ERROR: " + line + " - bad operation position";
            throw MyException(ex);
        }

    if (pos_lb != line.rfind('(') or line.find(')') != pos_rb)
    {
        string ex = "ERROR: " + line + " - bad operation position";
        throw MyException(ex);
    }
    string eq = strip(line.substr(pos_lb + 1, pos_rb - pos_lb - 1));
    int base = 10;

    base = gorner(10, parse_int(eq));
    if (base < 2 or base > 36)
    {
        string ex = "ERROR: " + in_gorner(10, base) + "base out of range[2, 36]";
        throw MyException(ex);
    }
    string snum = "";
    cin >> snum;
    return gorner(base, snum);
}

Instruct::Instruct(string file)
{
    init(file);
}

void Instruct::init(string filename)
{
    char b;
    oname = filename;
    ifstream fin(filename);
    string buf = "";
    while (!fin.eof())
    {
        b = fin.get();
        if (b == '#')
        {
            while (b != '\n' and b != EOF)
                b = fin.get();
        }

        if (b != '\n')
        {
            if (!isspace(b))
                buf += b;
            else
                buf += ' ';
        }
        else
        {
            if (!buf.empty()) {
                pars_str(buf);
            }
            buf = "";
        }
    }
    fin.close();
}

Instruct::Instruct()
{
    init(fname);
}

Instruct::~Instruct()
{
    if (oname == fname)
        return;
    ofstream ofn(fname);
    print_rule(ofn);
    print_rule(cout);
    ofn.close();
}

void Instruct::pars_str(const string &buf)
{
    int ln = buf.length();
    int i = 0;
    while (isspace(buf[i]) and i < ln)
        i++;
    string l_s = "";
    while (!isspace(buf[i]) and i < ln)
    {
        l_s += buf[i];
        i++;
    }
    if (l_s.empty())
    {
        throw MyException("empty instruction line");
    }

    while (isspace(buf[i]) and i < ln)
        i++;
    string r_s = "";
    while (!isspace(buf[i]) and i < ln)
    {
        r_s += buf[i];
        i++;
    }

    if (r_s.empty())
    {
        if (l_s == "right=") {
            if (is_set["eq_left"]) {
                throw MyException("ERROR repeat command: order of assignment");
            }
            eq_left = false;
            is_set["eq_left"] = true;
            return;
        }
        else if (l_s == "left=") {
            if (is_set["eq_left"]) {
                throw MyException("ERROR repeat command: order of assignment");
            }
            eq_left = true;
            is_set["eq_left"] = true;
            return;
        }
        if (read_state(buf, ln))
            return;
        string errorstr = buf + "\n Error in instruct";
        throw MyException(errorstr);
    }
    else {
        map <string, string> ::iterator it = rule.begin();
        for (; it != rule.end(); it++) {
            if (it->first == l_s){
                if (is_set[l_s]) {
                    string errorstr = "ERROR repeat command: redefinition " + buf;
                    throw MyException(errorstr);
                }
                rule[l_s] = r_s;
                is_set[l_s] = true;
                return;
            }
        }
        if (read_state(buf, ln))
            return;
        string errorstr = buf + "\n Error in instruct";
        throw MyException(errorstr);
    }
}

void Instruct::print_rule(ostream& out)
{
    map <string, string> ::iterator it = rule.begin();
    for (; it != rule.end(); it++) {  // выводим их
        out << it->first << " " << it->second << endl;
    }
    if (!eq_left)
        out << "right=" << endl;
    if (!op_left and bin_op_mid)
        out << "()(op)" << endl;
    if (op_left and bin_op_mid)
        out << "(op)()" << endl;
    if (op_left and !bin_op_mid)
        out << "op()" << endl;
}

bool Instruct::read_state(const string &buf, int ln)
{
    if (is_set["order_ops"]) {
        throw MyException("ERROR repeat command: order of operands and operations");
    }

    string buf_no_space = "";
    for (int i = 0; i < ln; i++) {
        if (isspace(buf[i]))
            continue;
        buf_no_space += buf[i];
    }

    if (buf_no_space == "()op") {
        op_left = false;
        bin_op_mid = false;
    }
    else if (buf_no_space == "op()") {
        op_left = true;
        bin_op_mid = false;
    }
    else if (buf_no_space == "(op)()") {
        op_left = true;
        bin_op_mid = true;
    }
    else if (buf_no_space == "()(op)") {
        op_left = false;
        bin_op_mid = true;
    }
    else {
        string errorstr = buf + "\n Error in instruct";
        throw MyException(errorstr);
    }

    is_set["order_ops"] = true;
    return true;
}

string strip(const string &line)
{
    int b = 0, end = 0;
    int ln = line.length();
    for (int i = 0; i < ln; i++)
        if (!isspace(line[i]))
        {
            b = i;
            break;
        }
    for (int i = ln - 1; i > 0; i--)
        if (!isspace(line[i]))
        {
            end = i;
            break;
        }
    return line.substr(b, end - b + 1);
}

string in_gorner(int base, int num)
{
    string ans = "";
    if (num < 0)
    {
        num *= -1;
        ans += '-';
    }

    while (num) {
        ans = get_chr(num % base) + ans;
        num /= base;
    }
    if (ans == "")
        ans += '0';
    return ans;
}

int gorner(int base, string str)
{
    bool sgn = 1;
    int ans = 0;
    int ln = str.length(), i = 0;
    if (str[0] == '-')
    {
        sgn = -1;
        i++;
    }
    while (i != ln)
    {
        char bchr = str[i];
        ans *= base;
        int der = get_dig(bchr);
        if (der >= base or der < 0)
            throw MyException("ERROR: incorrect base");
        ans += der;
        i++;
    }
    return sgn * ans;
}

int get_dig(char bchr)
{
    return (int)(isdigit(bchr) ? bchr - '0' : toupper(bchr) - 'A' + 10);
}

char get_chr(int total)
{
    return (char)((total < 10) ? total + '0' : total + 'A' - 10);
}

int add(int a, int b)
{
    return a + b;
}
int mult(int a, int b)
{
    return a * b;
}
int sub(int a, int b)
{
    return a - b;
}
int pow(int a, int b)
{
    if (b < 0)
        throw MyException("ERROR pow is less than zero");
    int ans = 1;
    for (int i = 0; i < b; i++)
    {
        ans *= a;
    }
    return ans;
}
int _div(int a, int b)
{
    if (b == 0)
        throw MyException("ZERO_DEVISION error");
    return a / b;
}
int rem(int a, int b)
{
    return a % b;
}
int x_or(int a, int b)
{
    return (a ^ b);
}