#include <iostream>
#include "../lab1_3rdPart_6step/exceptionsMy.h"
#include <fstream>
#include <vector>
#include <string>
#include <map>


using namespace std;

class Instruct
{
    static const int cnt_com = 10;
private:
    void pars_str(const string&);
    bool read_state(const string&, int);
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
        {"output", "output"},
        {"=", "="}
    };
    bool eq_left = true;
    bool op_left = true;
    bool bin_op_mid = false;
    string fname = "__last_instr.txt";
    string oname = "";
    Instruct(string fin);
    void init(string fin);
    Instruct();
    ~Instruct();
    void print_rule(ostream& out); // after debug, move to private?
};

class Tokenizer;

int main(int argc, char** argv)
{
    try {
        string fname = "";
        if (argc == 2)
        {
            fname = argv[1];
        }

        Instruct inst;
        if (!fname.empty())
            inst.init(fname);
        else
            inst.init(inst.fname);

        inst.print_rule(cout);
    }
    catch (MyException exc) {
        cout << '\n' << exc.what() << endl;
    }
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
    return;
}

Instruct::~Instruct()
{
    if (oname == fname)
        return;
    ofstream ofn(fname);
    print_rule(ofn);
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

/*
#include <iostream>
#include "../lab1_3rdPart_6step/exceptionsMy.h"
#include <fstream>
#include <vector>

using namespace std;

class Instruct
{
public:
    string ADD = "add";
    string MULT = "mult";
    string SUB = "sub";
    string POW = "pow";
    string DIV = "div";
    string REM = "rem";
    string XOR = "xor";
    string INPUT = "input";
    string OUTPUT = "output";
    string EQ = "=";
};

class Tokenizer
{
public:
    using DelimetersList = std::vector<std::string>;
    Tokenizer(const DelimetersList& delimiters)
        : m_delimiters(delimiters)
    {
    }
    void tokenize(const std::string& str)
    {
        m_tokens.clear();
        size_t start = 0;
        size_t end = 0;
        while (end != str.length())
        {
            auto delimiter = findDelimiter(str, start);
            end = delimiter.pos;
            m_tokens.push_back({ start, end - start });
            start = end + delimiter.length;
        }
    }
    struct Token
    {
        size_t begin;
        size_t length;
    };
    using TokensList = std::vector<Token>;
    const TokensList& getTokens() const
    {
        return m_tokens;
    }
private:
    struct Delimiter
    {
        size_t pos;
        size_t length;
    };
    Delimiter findDelimiter(const std::string& str, size_t start) const
    {
        size_t minPos = str.length();
        size_t length = 0;
        for (auto& delimiter : m_delimiters)
        {
            auto pos = str.find(delimiter, start);
            if (pos < minPos)
            {
                minPos = pos;
                length = delimiter.length();
            }
        }
        return { minPos, length };
    }
private:
    const DelimetersList m_delimiters;
private:
    TokensList m_tokens;
};
int main()
{
    std::string s = "お客#様のレビ#ュー\nはゲー\nム#の改善に役#立ちます！";
    std::cout << "string: \n" << s << "\n----\n" << std::endl;
    Tokenizer tokenizer({ " ", "\n", "\r", "#" });
    tokenizer.tokenize(s);
    for (auto& t : tokenizer.getTokens())
    {
        std::cout << s.substr(t.begin, t.length) << std::endl;
    }
    return 0;
}


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
                        buf += b;
                    else
                        buf += ' ';
                }
                else
                {
                    cout << buf << endl;
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


//Aviv Maman
#include <cctype>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

enum Token {
    literal, identifier, plus_symbol, minus_symbol, times_symbol, equals, lparen, rparen, error, eof, newline, terminal
};

struct Lexeme {
    Token token;
    string word;
};

Program:    Assignment*
Assignment: Identifier = Exp;

Exp: Term Exp' | Term
Exp': + Exp | - Exp

Term:   Fact Term'  | Fact
Term': * Term

Fact:   ( Exp ) | - Fact | + Fact | Literal | Identifier
Identifier:         Letter [Letter | Digit]*
Letter: a|...|z|A|...|Z|_
Literal:    0 | NonZeroDigit Digit*
NonZeroDigit:   1|...|9
Digit:  0|1|...|9

//method to output enum members neatly
string translate(Token t) {
    switch (t) {
    case literal: return "literal token"; break;
    case identifier: return "identifier token"; break;
    case plus_symbol: return "+ token"; break;
    case minus_symbol: return "- token"; break;
    case times_symbol: return "* token"; break;
    case lparen: return "( token"; break;
    case rparen: return ") token"; break;
    case equals: return "= token"; break;
    case error: return "error token\n"; break;
    case eof: return "eof token"; break;
    case newline: return "\n"; break;
    case terminal: return "terminal token"; break;
    }
    return "bad token";
}

class Lexer {
private:
    ifstream inFile;
    pair<Token, string> curr_token;
    pair<Token, string> get_token() {
        char c;
        string word, line;
        while (inFile.get(c)) {
            if (isdigit(c)) {
                if (c == '0') {
                    char next = inFile.peek();
                    if (isdigit(next)) { //001 is not valid
                        getline(inFile, line);
                        return make_pair(error, "error"); //Literal:  0 | NonZeroDigit Digit*
                    }
                    else return make_pair(literal, "0");
                }
                else if (c >= '1' && c <= '9') { //Literal:	0 | NonZeroDigit Digit*
                    while (isdigit(c)) {
                        word += c;
                        inFile.get(c);
                    }
                    inFile.putback(c);
                    return make_pair(literal, word);
                }
            }
            else if (isalpha(c) || c == '_') { //Identifier:         Letter [Letter | Digit]*
                while (isalnum(c) || c == '_') {
                    word += c;
                    inFile.get(c);
                }
                inFile.putback(c);
                return make_pair(identifier, word);
            }
            else if (c == '+') return make_pair(plus_symbol, "+");
            else if (c == '-') return make_pair(minus_symbol, "-");
            else if (c == '*') return make_pair(times_symbol, "*");
            else if (c == '=') return make_pair(equals, "=");
            else if (c == '(') return make_pair(lparen, "(");
            else if (c == ')') return make_pair(rparen, ")");
            else if (c == ';') return make_pair(terminal, ";");
        }
        return make_pair(eof, "End of file");
    }
public:
    Lexer() = delete;
    Lexer(string filename) {
        inFile.open(filename);
    }
    ~Lexer() {
        inFile.close();
    }
    deque<pair<Token, string>> tokenizer() {
        deque<pair<Token, string>> t;
        curr_token = get_token();
        while (curr_token.first != eof) {
            t.push_back(curr_token);
            curr_token = get_token();
        }
        t.push_back(make_pair(eof, "End of file"));
        return t;
    }
};

class Parser {
private:
    deque<pair<Token, string>> tokens;
    pair<Token, string> curr_token;
    std::map<std::string, int> state;

public:
    Parser(deque<pair<Token, string>> tokens) {
        this->tokens = tokens;
    }
    void get_token() {
        curr_token = tokens.front();
        tokens.pop_front();
    }
    //pattern matching method. if encounters a match, we proceed to pop the next token off the queue and store it in curr_token
    void match(Token t) {
        if (curr_token.first == t) {
            get_token();
        }
        else {
            cout << "Error: Expected token: " << translate(t) << ". Given token: " << translate(curr_token.first) << "\n";
            exit(-1);
        }
    }
    //method to print out all Token/Word pairs
    void printSymbolTable() {
        for (pair<Token, string> r : tokens) {
            cout << r.second << "\t" << setw(20) << translate(r.first) << endl;
        }
    }

    //Program:    Assignment*
    void program() {
        get_token();
        while (!tokens.empty()) {
            assignment();
        }
        for (auto const& x : state)
        {
            cout << x.first  // string (key)
                << " = "
                << x.second // string's value
                << endl;
        }
        //cout << "done\n";
    }

    //Assignment: Identifier = Exp;
    void assignment() {
        if (curr_token.first != identifier) {
            cout << "Not a valid program\n"; exit(-1);
        }
        else {
            string foo = curr_token.second;
            match(identifier);
            match(equals);
            int x = exp();
            state[foo] = x;
            match(terminal);
        }
    }

    //Exp': + Exp | - Exp
    int expPrime() {
        if (curr_token.first == plus_symbol) {
            match(plus_symbol);
            return exp();
        }
        else if (curr_token.first == minus_symbol) {
            match(minus_symbol);
            return -exp();
        }
    }

    //Exp: Term Exp' | Term
    int exp() {
        int i = term();
        if (curr_token.first == plus_symbol || curr_token.first == minus_symbol) {
            i += expPrime();
        }
        return i;
    }

    //Term:   Fact Term'  | Fact
    int term() {
        int i = fact();
        if (curr_token.first == times_symbol) {
            i *= termPrime();
        }
        return i;
    }

    //Term': * Term
    int termPrime() {
        match(times_symbol);
        return term();
    }

    //Fact:   ( Exp ) | - Fact | + Fact | Literal | Identifier
    int fact() {
        if (curr_token.first == lparen) {
            match(lparen);
            int i = exp();
            match(rparen);
            return i;
        }
        else if (curr_token.first == minus_symbol) {
            match(minus_symbol);
            return -fact();
        }
        else if (curr_token.first == plus_symbol) {
            match(plus_symbol);
            return fact();
        }
        else if (curr_token.first == literal) {
            int i = stoi(curr_token.second);
            match(literal);
            return i;
        }
        else if (curr_token.first == identifier) {
            if (state.find(curr_token.second) == state.end()) { //variable not defined
                match(terminal);
                cout << "Variable " << curr_token.second << " was not found.\n"; exit(-1);
            }
            string tmp = curr_token.second;
            match(identifier);
            return state[tmp];
        }
    }
};

int main() {
    string filename = "filestep.txt";
    Lexer p(filename);
    deque<pair<Token, string>> t = p.tokenizer();
    Parser q(t);
    q.program();

    return 0;
}
*/