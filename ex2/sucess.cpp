#include "bits/stdc++.h"
#include "table.h"
#define MAX_LINE 1024
using namespace std;
vector<string> wordname;
vector<string> tokens;

void print_tokens()
{
    ofstream outfile;
    outfile.open("tokens.txt");
    for (int i = 0; i < wordname.size(); i++)
    {
        outfile << tokens[i] << endl;
    }
    outfile.close();
}

void print_wordname()
{
    ofstream outfile;
    outfile.open("wordnames.txt");
    for (int i = 0; i < wordname.size(); i++)
    {
        outfile << wordname[i] << endl;
    }
    outfile.close();
}

int lex_analyse()
{
    char c = '\0';
    string buffer;
    // 读入文件
    ifstream infile;
    infile.open("testfile.txt");

    // 写入buffer
    infile >> noskipws;
    while (infile.peek() != EOF)
    {
        infile >> c;
        buffer += c;
    }
    infile.close();

    string word = "";                // 正在识别的单词，c是字符
    int forward = 0;                 // 向前指针
    int buffer_size = buffer.size(); // 总长度

    // 开始逐字符判断
    while (forward < buffer_size)
    {
        word += buffer[forward]; //更新token

        // 特殊字符  +=*/:=;,()[]{}
        if (signal_char.find(word) != signal_char.npos)
        {
            wordname.emplace_back(word);
            tokens.emplace_back(table[word]);
        }

        // 比较运算符    先判断 <,>,=,! 再判断 <=,>=,==,!=
        if (signal_comparison.find(word) != signal_comparison.npos)
        {
            word += buffer[++forward];
            if (find(double_cocmparison.begin(), double_cocmparison.end(), word) != double_cocmparison.end())
            {
                wordname.emplace_back(word);
                tokens.emplace_back(table[word]);
            }
            else
            {
                word.erase(1, 1); // 删除第二个字符
                wordname.emplace_back(word);
                tokens.emplace_back(table[word]);
                --forward;
            }
        }

        // 判断整形常量
        if (isdigit(buffer[forward]))
        {
            while (isdigit(buffer[++forward]))
            {
                word += buffer[forward];
            }
            --forward;
            wordname.emplace_back(word);
            tokens.emplace_back(table["整形常量"]);
        }

        // 判断字符常量
        if (word == "\'")
        {
            // cout << "开始字符判断..." ;
            while (buffer[++forward] != '\'')
            {
                word += buffer[forward];
            }
            word.erase(0, 1); // 去掉开头的  '
            // cout << "当前token: " << word << "类型: " << table["字符常量"] <<  endl;
            wordname.emplace_back(word);
            tokens.emplace_back(table["字符常量"]);
        }

        // 判断字符串
        if (word == "\"")
        {
            // cout << "开始字符串判断...." ;
            while (buffer[++forward] != '\"')
            {
                word += buffer[forward];
            }
            word.erase(0, 1); // 去掉开头的  "
            // cout << "当前token: " << word << ".... "<< table["字符串"];
            wordname.emplace_back(word);
            tokens.emplace_back(table["字符串"]);
            // cout << "已添加进容器" << endl;
        }

        // 判断关键字 或 标识符
        if (isalpha(buffer[forward]) || buffer[forward] == '_')
        {
            while (isalnum(buffer[++forward]) || buffer[forward] == '_')
            {
                word += buffer[forward];
            }
            --forward;
            string temp = word;                                           // 保留token原有格式，向name中填写
            transform(word.begin(), word.end(), word.begin(), ::tolower); // token变为小写,关键字识别用小写
            if (find(key_word.begin(), key_word.end(), word) != key_word.end())
            {
                wordname.emplace_back(temp);
                tokens.emplace_back(table[word]);
            }
            else
            {
                wordname.emplace_back(temp);
                tokens.emplace_back(table["标识符"]);
            }
        }
        // 重置token, 指针后移
        word = "";
        ++forward;
    }

    print_tokens();
    print_wordname();
    // cout << "长度:" <<tokens.size() << " " << wordname.size() << endl;
    return 0;
}

int pos = -1; // token指针位置
vector<string> ans;

void program();
void clsm();
void cldy();
void blsm();
void bldy();
void bldy_uninit();
void bldy_init();
void func_with_return_def();
void func_without_return_def();
void fhyj();
void csb();
void main_func();
void expression();
void xiang();
void factor();
void statement();
void assign_state();
void condi_state();
void condition();
void loop_state();
void step_size();
void case_state();
void case_table();
void case_sub();
void case_default();
void func_with_return();
void func_without_return();
void param_list();
void state_list();
void read_state();
void write_state();
void return_state();

string token = "";

void error(string s)
{
    // cout << s + " error!" << endl;
    ans.emplace_back(s + " error!——!");
}

void NEXT()
{
    token = tokens[++pos];
}

void BACK()
{
    if (pos - 1 >= 0)
    {
        token = tokens[--pos];
    }
}

void ADD()
{
    ans.emplace_back(token + " " + wordname[pos]);
    cout << token << " " << wordname[pos] << " " << pos << endl;
}

void OP_PM()
{
    if (token != table["+"] && token != table["-"])
    {
        error("OP_PM()");
    }
}

void OP_PD()
{
    if (token != table["*"] && token != table["/"])
    {
        error("OP_PD()");
    }
}

void OP_COM()
{
    if (token != table["<"] && token != table["<="] && token != table[">"] && token != table[">="] && token != table["!="] && token != table["=="])
    {
        error("OP_COM()");
    }
    else
    {
        ADD();
    }
}

void LBRACE()
{
    if (token != table["{"])
    {
        error("LBRACE()");
    }
    else
    {
        ADD();
    }
}

void RBRACE()
{
    if (token != table["}"])
    {
        error("RBRACE()");
    }
    else
    {
        ADD();
    }
}

void LBRACK()
{
    if (token != table["["])
    {
        error("LBRACK()");
    }
    else
    {
        ADD();
    }
}

void RBRACK()
{
    if (token != table["]"])
    {
        error("RBRACK()");
    }
    else
    {
        ADD();
    }
}

void LPARENT()
{
    if (token != table["("])
    {
        error("LPARENT()");
    }
    else
    {
        ADD();
    }
}

void RPARENT()
{
    if (token != table[")"])
    {
        error("RPARENT()");
    }
    else
    {
        ADD();
    }
}

void ALPHA()
{
    if (token != table["字符常量"])
    {
        error("ALPHA()");
    }
    else
    {
        ADD();
    }
}

void STRCON()
{
    if (token != table["字符串"])
    {
        error("STRCON()");
    }
    else
    {
        ADD();
        ans.emplace_back("<字符串>");
    }
}

void CONST()
{
    if (token != table["const"])
    {
        error("CONST()");
    }
    else
    {
        ADD();
    }
}

void SEMICN()
{
    if (token != table[";"])
    {
        error("SEMICN()");
    }
    else
    {
        ADD();
    }
}

void COLON()
{
    if (token != table[":"])
    {
        error("COLON()");
    }
    else
    {
        ADD();
    }
}

void ASSIGN()
{
    if (token != table["="])
    {
        error("ASSIGN()");
    }
    else
    {
        ADD();
    }
}
void IDENFR()
{
    if (token != table["标识符"])
    {
        error("IDENFR()");
    }
    else
    {
        ADD();
    }
}

void unsigned_int()
{
    if (token != table["整形常量"])
    {
        error("unsigned_int()");
    }
    else
    {
        ADD();
        ans.emplace_back("<无符号整数>");
    }
}

void INTCON()
{
    if (token == table["+"] || token == table["-"])
    {
        ADD();
        NEXT();
        unsigned_int();
        ans.emplace_back("<整数>");
    }
    else if (token == table["整形常量"])
    {
        unsigned_int();
        ans.emplace_back("<整数>");
    }
    else
    {
        error("INTCON()");
    }
}

void CHARCON()
{
    if (token != table["字符常量"])
    {
        error("CHARCON()");
    }
    else
    {
        ADD();
    }
}

void program()
{
    if (token == table["const"])
    {
        clsm();
        NEXT();
    }
    if (tokens[pos + 2] != table["("] && (token == table["int"] || token == table["char"]))
    { // 应该是0
        blsm();
        NEXT();
    }
    while (tokens[pos + 2] == table["("] && (token == table["int"] || token == table["char"] || token == table["void"]))
    { // 应该是1
        if (token == table["int"] || token == table["char"])
        {
            func_with_return_def();
        }
        if (token == table["void"] && tokens[pos + 1] != table["main"])
        { // 不能是主函数
            func_without_return_def();
        }
        NEXT();
    }
    BACK();
    main_func();
    ans.emplace_back("<程序>");
}

void clsm()
{
    while (token == table["const"])
    {
        CONST();

        NEXT();
        cldy();

        NEXT();
        SEMICN();

        NEXT();
    }
    BACK();
    ans.emplace_back("<常量说明>");
}

void cldy()
{
    if (token == table["int"])
    {
        ADD();

        NEXT();
        IDENFR();

        NEXT();
        ASSIGN();

        NEXT();
        INTCON();

        NEXT();
        while (token == table[","])
        {
            ADD();

            NEXT();
            IDENFR();

            NEXT();
            ASSIGN();

            NEXT();
            INTCON();

            NEXT(); // 查看之后一个是不是‘，’，判断循环
        }
        BACK();
        ans.emplace_back("<常量定义>");
    }
    else if (token == table["char"])
    {
        ADD();

        NEXT();
        IDENFR();

        NEXT();
        ASSIGN();

        NEXT();
        CHARCON();

        NEXT();
        while (token == table[","])
        {
            ADD();

            NEXT();
            IDENFR();

            NEXT();
            ASSIGN();

            NEXT();
            CHARCON();

            NEXT();
        }
        BACK();
        ans.emplace_back("<常量定义>");
    }
    else
    {
        error("cldy()");
    }
}

void smtb()
{
    if (token == table["int"])
    {
        ADD();

        NEXT();
        IDENFR();
        ans.emplace_back("<声明头部>");
    }
    else if (token == table["char"])
    {
        ADD();

        NEXT();
        IDENFR();
        ans.emplace_back("<声明头部>");
    }
    else
    {
        error("smtb()");
    }
}

void ICCON()
{ // 常量
    if (token == table["字符常量"])
    {
        ADD();
        ans.emplace_back("<常量>");
    }
    else if (token == table["+"] || token == table["-"] || token == table["整形常量"])
    {
        INTCON();
        ans.emplace_back("<常量>");
    }
    else
    {
        error("ICCON()");
    }
}

void blsm()
{
    bldy();

    NEXT();
    SEMICN();

    NEXT();
    while ((token == table["int"] || token == table["char"]) && tokens[pos + 2] != table["("])
    {
        bldy();

        NEXT();
        SEMICN();

        NEXT();
    }

    BACK();
    ans.emplace_back("<变量说明>");
}

void bldy()
{
    if (tokens[pos + 2] == table["="])
    {
        bldy_init();
    }
    else if (tokens[pos + 2] == table["["] && tokens[pos + 5] == table["="])
    {
        bldy_init();
    }
    else if (tokens[pos + 2] == table["["] && tokens[pos + 5] == table["["] && tokens[pos + 8] == table["="])
    {
        bldy_init();
    }
    else
    {
        bldy_uninit();
    }

    ans.emplace_back("<变量定义>");
}

void bldy_uninit()
{
    if (token == table["int"] || token == table["char"])
    {
        ADD();

        NEXT();
        if (token == table["标识符"])
        {
            ADD();

            NEXT();
            if (token == table["["])
            {
                ADD();

                NEXT();
                unsigned_int();

                NEXT();
                if (token == table["]"])
                {
                    ADD();
                }

                NEXT();
                if (token == table["["])
                {
                    ADD();

                    NEXT();
                    unsigned_int();

                    NEXT();
                    if (token == table["]"])
                    {
                        ADD();
                    }
                }
                else
                {
                    BACK();
                }
            }
            else
            {
                BACK();
            }
        }
    }

    NEXT();
    while (token == table[","])
    {
        ADD();
        NEXT();
        if (token == table["标识符"])
        {
            ADD();

            NEXT();
            if (token == table["["])
            {
                ADD();

                NEXT();
                unsigned_int();

                NEXT();
                if (token == table["]"])
                {
                    ADD();
                }

                NEXT();
                if (token == table["["])
                {
                    ADD();

                    NEXT();
                    unsigned_int();

                    NEXT();
                    if (token == table["]"])
                    {
                        ADD();
                    }
                }
                else
                {
                    BACK();
                }
            }
            else
            {
                BACK();
            }
        }

        NEXT();
    }
    BACK();
    ans.emplace_back("<变量定义无初始化>");
}

void bldy_init()
{
    if (token == table["int"] || token == table["char"])
    {
        ADD();

        NEXT();
        IDENFR();

        NEXT();
        if (token == table["="])
        {
            ADD();

            NEXT();
            ICCON();
        }
        else if (token == table["["])
        {
            ADD();
            NEXT();
            unsigned_int();
            NEXT();
            RBRACK();

            NEXT();
            if (token == table["="])
            {
                ADD();
                NEXT();
                LBRACE();

                NEXT();
                ICCON();

                NEXT();
                while (token == table[","])
                {
                    ADD();

                    NEXT();
                    ICCON();

                    NEXT();
                } // 遇到 } 才会退出
                RBRACE();
            }
            else if (token == table["["])
            {
                ADD(); // [
                NEXT();
                unsigned_int(); // 无符号整数
                NEXT();
                RBRACK(); // ]

                NEXT();
                ASSIGN(); // =

                NEXT();
                LBRACE(); // {

                NEXT();
                LBRACE(); // {

                NEXT();
                ICCON();

                NEXT();
                while (token == table[","])
                {
                    ADD();

                    NEXT();
                    ICCON();

                    NEXT();
                }
                // 跳出说明遇到了 }
                RBRACE();

                NEXT();
                while (token == table[","])
                {
                    ADD();

                    NEXT();
                    LBRACE();
                    NEXT();
                    ICCON();

                    NEXT();
                    while (token == table[","])
                    {
                        ADD();
                        NEXT();
                        ICCON();

                        NEXT();
                    }
                    // 跳出说明遇到了 }
                    RBRACE();
                    NEXT();
                }
                // 跳出说明遇到了 }
                RBRACE();
            }
        }
        ans.emplace_back("<变量定义及初始化>");
    }
}

void func_with_return_def()
{
    smtb();

    NEXT();
    LPARENT();

    NEXT();
    csb();

    NEXT();
    RPARENT();

    NEXT();
    LBRACE();

    NEXT();
    fhyj();

    NEXT();
    RBRACE();

    ans.emplace_back("<有返回值函数定义>");
}

void func_without_return_def()
{
    if (token == table["void"])
    {
        ADD();

        NEXT();
        IDENFR();

        NEXT();
        LPARENT();

        NEXT();
        csb();

        NEXT();
        RPARENT();

        NEXT();
        LBRACE();

        NEXT();
        fhyj();

        NEXT();
        RBRACE();

        ans.emplace_back("<无返回值函数定义>");
    }
    else
    {
        error("无返回值函数定义");
    }
}

void fhyj()
{
    if (token == table["const"])
    {
        clsm();
        NEXT();
    }
    if ((token == table["int"] || token == table["char"]) && (tokens[pos + 2] != table["("]))
    {
        blsm();
        NEXT();
    }
    state_list();
    ans.emplace_back("<复合语句>");
}

void csb()
{ // 死循环
    if (token == table["int"] || token == table["char"])
    {
        ADD();

        NEXT();
        IDENFR();

        NEXT();
        while (token == table[","])
        {
            ADD();
            NEXT();
            if (token == table["int"] || token == table["char"])
            {
                ADD();

                NEXT();
                IDENFR();
            }
            NEXT();
        }
        BACK();
        ans.emplace_back("<参数表>");
    }
    else if (token == table[")"])
    { // 参数为 空， 直接读取 ) 。需要回退一位
        BACK();
        ans.emplace_back("<参数表>");
    }
    else
    {
        error("参数表");
    }
}

void main_func()
{
    if (token == table["void"])
    {
        ADD();

        NEXT();
        if (token == table["main"])
        {
            ADD();

            NEXT();
            LPARENT();

            NEXT();
            RPARENT();

            NEXT();
            LBRACE();

            NEXT();
            fhyj();

            NEXT();
            RBRACE();
            ans.emplace_back("<主函数>");
        }
        else
        {
            error("main");
        }
    }
    else
    {
        error("main");
    }
}

void expression()
{
    if (token == table["+"] || token == table["-"])
    {
        ADD();
        NEXT();
    }
    xiang();

    NEXT();
    while (token == table["+"] || token == table["-"])
    {
        ADD();

        NEXT();
        xiang();

        NEXT();
    }
    BACK();
    ans.emplace_back("<表达式>");
}

void xiang()
{
    factor();

    NEXT();
    while (token == table["*"] || token == table["/"])
    {
        ADD();

        NEXT();
        factor();

        NEXT();
    }
    BACK();

    ans.emplace_back("<项>");
}

void factor()
{
    if (token == table["标识符"])
    {
        IDENFR();
        NEXT();
        if (token == table["["])
        {
            ADD();

            NEXT();
            expression();

            NEXT();
            RBRACK();

            NEXT();
            if (token == table["["])
            {
                ADD();

                NEXT();
                expression();

                NEXT();
                RBRACK();
            }
            else
            {
                BACK();
            }
        }
        else if (token == table["("])
        {
            BACK();
            ans.pop_back();
            func_with_return();
        }
        else
        {
            BACK();
        }
        ans.emplace_back("<因子>");
    }
    else if (token == table["("])
    {
        ADD();

        NEXT();
        expression();

        NEXT();
        RPARENT();
        ans.emplace_back("<因子>");
    }
    else if (token == table["整形常量"] || token == table["+"] || token == table["-"])
    {
        INTCON();
        ans.emplace_back("<因子>");
    }
    else if (token == table["字符常量"])
    {
        CHARCON();
        ans.emplace_back("<因子>");
    }
    else
    {
        error("因子");
    }
}

void statement()
{ // 语句
    if (token == table["while"] || token == table["for"])
    {
        loop_state();
        ans.emplace_back("<语句>");
    }
    else if (token == table["if"])
    {
        condi_state();
        ans.emplace_back("<语句>");
    }
    else if (token == table["标识符"] && tokens[pos + 2] == table[")"])
    {
        func_without_return();
        NEXT();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["标识符"] && (tokens[pos + 1] == table["="] || tokens[pos + 1] == table["["]))
    {
        assign_state();
        NEXT();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["标识符"] && tokens[pos + 2] != table[")"])
    {
        func_with_return();
        NEXT();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["scanf"])
    {
        read_state();
        NEXT();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["printf"])
    {
        write_state();
        NEXT();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["return"])
    {
        return_state();
        NEXT();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["switch"])
    {
        case_state();
        ans.emplace_back("<语句>");
    }
    else if (token == table["{"])
    {
        LBRACE();
        NEXT();
        state_list();
        NEXT();
        RBRACE();
        ans.emplace_back("<语句>");
    }
    else if (token == table[";"])
    {
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else
    {
        error("state()");
    }
}

void assign_state()
{
    if (token == table["标识符"])
    {
        ADD();

        NEXT();
        if (token == table["="])
        {
            ADD();
            NEXT();
            expression();
            ans.emplace_back("<赋值语句>");
        }
        else if (token == table["["])
        {
            ADD();
            NEXT();
            expression();
            NEXT();
            RBRACK();

            NEXT();
            if (token == table["["])
            {
                ADD();
                NEXT();
                expression();
                NEXT();
                RBRACK();
                NEXT();
            }
            ASSIGN();
            NEXT();
            expression();
            ans.emplace_back("<赋值语句>");
        }
        else
        {
            error("assign_state()");
        }
    }
}

void condi_state()
{
    if (token == table["if"])
    {
        ADD();

        NEXT();
        LPARENT();
        NEXT();
        condition();
        NEXT();
        RPARENT();
        NEXT();
        statement();
        NEXT();
        if (token == table["else"])
        {
            ADD();
            NEXT();
            statement();
            NEXT();
        }
        BACK();
        ans.emplace_back("<条件语句>");
    }
}

void condition()
{
    expression();
    NEXT();
    OP_COM();
    NEXT();
    expression();
    ans.emplace_back("<条件>");
}

void loop_state()
{
    if (token == table["while"])
    {
        ADD();
        NEXT();
        LPARENT();
        NEXT();
        condition();
        NEXT();
        RPARENT();
        NEXT();
        statement();
        ans.emplace_back("<循环语句>");
    }
    else if (token == table["for"])
    {
        ADD();
        NEXT();
        LPARENT();
        NEXT();
        IDENFR();
        NEXT();
        ASSIGN();
        NEXT();
        expression();
        NEXT();
        SEMICN();
        NEXT();
        condition();
        NEXT();
        SEMICN();
        NEXT();
        IDENFR();
        NEXT();
        ASSIGN();
        NEXT();
        IDENFR();
        NEXT();
        if (token == table["+"] || token == table["-"])
        {
            ADD();
        }
        NEXT();
        step_size();
        NEXT();
        RPARENT();
        NEXT();
        statement();
        ans.emplace_back("<循环语句>");
    }
    else
    {
        error("loop_state()");
    }
}

void step_size()
{
    unsigned_int();
    ans.emplace_back("<步长>");
}

void case_state()
{
    if (token == table["switch"])
    {
        ADD();
        NEXT();
        LPARENT();
        NEXT();
        expression();
        NEXT();
        RPARENT();
        NEXT();
        LBRACE();
        NEXT();
        case_table();
        NEXT();
        case_default();
        NEXT();
        RBRACE();
        ans.emplace_back("<情况语句>");
    }
    else
    {
        error("case_state()");
    }
}

void case_table()
{
    case_sub();
    NEXT();
    if (token == table["case"])
    {
        case_sub();
        NEXT();
    }
    BACK();
    ans.emplace_back("<情况表>");
}

void case_sub()
{
    if (token == table["case"])
    {
        ADD();
        NEXT();
        ICCON();
        NEXT();
        COLON();
        NEXT();
        statement();
        ans.emplace_back("<情况子语句>");
    }
}

void case_default()
{
    if (token == table["default"])
    {
        ADD();
        NEXT();
        COLON();
        NEXT();
        statement();
        ans.emplace_back("<缺省>");
    }
}

void func_with_return()
{
    IDENFR();
    NEXT();
    LPARENT();
    NEXT();
    param_list();
    NEXT();
    RPARENT();
    ans.emplace_back("<有返回值函数调用语句>");
}

void func_without_return()
{
    IDENFR();
    NEXT();
    LPARENT();
    ans.emplace_back("<值参数表>");
    NEXT();
    RPARENT();
    ans.emplace_back("<无返回值函数调用语句>");
}

void param_list()
{
    if (token == table["+"] || token == table["-"] || token == table["标识符"] || token == table["("] || token == table["整形常量"] || token == table["字符常量"])
    {
        expression();
        NEXT();
        while (token == table[","])
        {
            ADD();
            NEXT();
            expression();
            NEXT();
        }
        BACK();
        ans.emplace_back("<值参数表>");
    }
    else if (token == table[")"])
    {
        BACK(); //会退一个，  )会有之后函数单独处理
        ans.emplace_back("<值参数表>");
    }
    else
    {
        error("param_list()");
    }
}

void state_list()
{
    while (token == table["while"] || token == table["for"] || token == table["if"] || token == table["标识符"] || token == table["scanf"] || token == table["printf"] || token == table["return"] || token == table["switch"] || token == table["{"] || token == table[";"])
    {
        statement();
        NEXT();
    }
    BACK();
    ans.emplace_back("<语句列>");
}

void read_state()
{
    if (token == table["scanf"])
    {
        ADD();
        NEXT();
        LPARENT();
        NEXT();
        IDENFR();
        NEXT();
        RPARENT();
        ans.emplace_back("<读语句>");
    }
}

void write_state()
{
    if (token == table["printf"])
    {
        ADD();
        NEXT();
        LPARENT();
        NEXT();
        if (token == table["字符串"])
        {
            STRCON();
            NEXT();
            if (token == table[","])
            {
                ADD();
                NEXT();
                expression();
                NEXT();
                RPARENT();
            }
            else if (token == table[")"])
            {
                RPARENT();
            }
            else
            {
                BACK();
            }
        }
        else if (token == table["+"] || token == table["-"] || token == table["标识符"] || token == table["("] || token == table["整形常量"] || token == table["字符常量"])
        {
            expression();
            NEXT();
            RPARENT();
        }
        ans.emplace_back("<写语句>");
    }
}

void return_state()
{
    if (token == table["return"])
    {
        ADD();
        NEXT();
        if (token == table["("])
        {
            LPARENT();
            NEXT();
            expression();
            NEXT();
            RPARENT();
            NEXT();
        }
        BACK();
        ans.emplace_back("<返回语句>");
    }
    else
    {
        error("return_state()");
    }
}

void print_ans()
{
    ofstream outfile;
    outfile.open("output.txt");
    for (int i = 0; i < ans.size(); i++)
    {
        outfile << ans[i] << endl;
    }
    outfile.close();
}

int main()
{
    lex_analyse();
    cout << tokens.size() << " " << wordname.size() << endl;
    NEXT();
    // for(int i=0;i<10;i++){
    //     NEXT();
    //     cout << pos << " " <<  token << endl;
    // }
    program();

    print_ans();
    return 0;
}
