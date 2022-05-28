#pragma once
#include "bits/stdc++.h"
#include "table.h"

using namespace std;


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
void item();
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


vector<string> ans;     // 记录每次的识别结果
vector<string> tokens;  // 类别码, 实验一结果传进来
vector<string> wordnames;   // 单词名称， 实验一结果传值
map<string, bool> functions;  // 记录函数是否由返回值
int len = 0;    // tokens长度
int pos;        // token指针位置
string token = "";      // 当前取出的类别码 tokens[pos]



// 指针前进
void Forward()
{
    if (pos + 1 < len)
    {
        token = tokens[++pos];
    }
}

// 指针回退一格
void Retrack()
{
    if (pos - 1 >= 0)
    {
        token = tokens[--pos];
    }
}

// 添加当前  类别码 ， 单词名称
void ADD()
{
    ans.emplace_back(token + " " + wordnames[pos]);
}

// 报错信息
void error(string s)
{
    // cout << s + " error!" << endl;
    ans.emplace_back(s + " error!——!");
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

// 判断是否为标识符
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
        Forward();
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
        Forward();
    }
    if (tokens[pos + 2] != table["("] && (token == table["int"] || token == table["char"]))
    { // 应该是0
        blsm();
        Forward();
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
        Forward();
    }
    Retrack();
    main_func();
    ans.emplace_back("<程序>");
}

void clsm()
{
    while (token == table["const"])
    {
        CONST();

        Forward();
        cldy();

        Forward();
        SEMICN();

        Forward();
    }
    Retrack();
    ans.emplace_back("<常量说明>");
}

void cldy()
{
    if (token == table["int"])
    {
        ADD();

        Forward();
        IDENFR();

        Forward();
        ASSIGN();

        Forward();
        INTCON();

        Forward();
        while (token == table[","])
        {
            ADD();

            Forward();
            IDENFR();

            Forward();
            ASSIGN();

            Forward();
            INTCON();

            Forward(); // 查看之后一个是不是‘，’，判断循环
        }
        Retrack();
        ans.emplace_back("<常量定义>");
    }
    else if (token == table["char"])
    {
        ADD();

        Forward();
        IDENFR();

        Forward();
        ASSIGN();

        Forward();
        CHARCON();

        Forward();
        while (token == table[","])
        {
            ADD();

            Forward();
            IDENFR();

            Forward();
            ASSIGN();

            Forward();
            CHARCON();

            Forward();
        }
        Retrack();
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

        Forward();
        IDENFR();
        
        ans.emplace_back("<声明头部>");
    }
    else if (token == table["char"])
    {
        ADD();

        Forward();
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

    Forward();
    SEMICN();

    Forward();
    while ((token == table["int"] || token == table["char"]) && tokens[pos + 2] != table["("])
    {
        bldy();

        Forward();
        SEMICN();

        Forward();
    }

    Retrack();
    ans.emplace_back("<变量说明>");
}

void bldy()
{
    if (pos + 2 < len && tokens[pos + 2] == table["="])
    {
        bldy_init();
    }
    else if (pos + 5 < len && tokens[pos + 2] == table["["] && tokens[pos + 5] == table["="])
    {
        bldy_init();
    }
    else if (pos + 8 < len && tokens[pos + 2] == table["["] && tokens[pos + 5] == table["["] && tokens[pos + 8] == table["="])
    {
        bldy_init();
    }
    else
    {
        bldy_uninit();
    }

    ans.emplace_back("<变量定义>");
}

// 变量定义无初始化
void bldy_uninit()
{
    if (token == table["int"] || token == table["char"])
    {
        ADD();

        Forward();
        if (token == table["标识符"])
        {
            ADD();

            Forward();
            if (token == table["["])
            {
                ADD();

                Forward();
                unsigned_int();

                Forward();
                if (token == table["]"])
                {
                    ADD();
                }

                Forward();
                if (token == table["["])
                {
                    ADD();

                    Forward();
                    unsigned_int();

                    Forward();
                    if (token == table["]"])
                    {
                        ADD();
                    }
                }
                else
                {
                    Retrack();
                }
            }
            else
            {
                Retrack();
            }
        }
    }

    Forward();
    while (token == table[","])
    {
        ADD();
        Forward();
        if (token == table["标识符"])
        {
            ADD();

            Forward();
            if (token == table["["])
            {
                ADD();

                Forward();
                unsigned_int();

                Forward();
                RBRACK();

                Forward();
                if (token == table["["])
                {
                    ADD();

                    Forward();
                    unsigned_int();

                    Forward();
                    RBRACK();
                }
                else
                {
                    Retrack();
                }
            }
            else
            {
                Retrack();
            }
        }
        Forward();
    }
    Retrack();
    ans.emplace_back("<变量定义无初始化>");
}

void bldy_init()
{
    if (token == table["int"] || token == table["char"])
    {
        ADD();

        Forward();
        IDENFR();

        Forward();
        if (token == table["="])
        {
            ADD();

            Forward();
            ICCON();
        }
        else if (token == table["["])
        {
            ADD();
            Forward();
            unsigned_int();
            Forward();
            RBRACK();

            Forward();
            if (token == table["="])
            {
                ADD();
                Forward();
                LBRACE();

                Forward();
                ICCON();

                Forward();
                while (token == table[","])
                {
                    ADD();

                    Forward();
                    ICCON();

                    Forward();
                } // 遇到 } 才会退出
                RBRACE();
            }
            else if (token == table["["])
            {
                ADD(); // [
                Forward();
                unsigned_int(); // 无符号整数
                Forward();
                RBRACK(); // ]

                Forward();
                ASSIGN(); // =

                Forward();
                LBRACE(); // {

                Forward();
                LBRACE(); // {

                Forward();
                ICCON();

                Forward();
                while (token == table[","])
                {
                    ADD();

                    Forward();
                    ICCON();

                    Forward();
                }
                // 跳出说明遇到了 }
                RBRACE();

                Forward();
                while (token == table[","])
                {
                    ADD();

                    Forward();
                    LBRACE();
                    Forward();
                    ICCON();

                    Forward();
                    while (token == table[","])
                    {
                        ADD();
                        Forward();
                        ICCON();

                        Forward();
                    }
                    // 跳出说明遇到了 }
                    RBRACE();
                    Forward();
                }
                // 跳出说明遇到了 }
                RBRACE();
            }
        }
        ans.emplace_back("<变量定义及初始化>");
    }
}

// 有返回值函数定义
void func_with_return_def()
{
    if(token == table["int"] || token == table["char"]){
        // 记录有返回值
        functions[wordnames[pos+1]] = true;
        smtb();

        Forward();        LPARENT();

        Forward();        csb();

        Forward();        RPARENT();

        Forward();        LBRACE();

        Forward();        fhyj();

        Forward();        RBRACE();

        ans.emplace_back("<有返回值函数定义>");
    }
    
}

void func_without_return_def()
{
    if (token == table["void"])
    {
        functions[wordnames[pos+1]] = false;
        ADD();

        Forward();
        IDENFR();

        Forward();
        LPARENT();

        Forward();
        csb();

        Forward();
        RPARENT();

        Forward();
        LBRACE();

        Forward();
        fhyj();

        Forward();
        RBRACE();

        ans.emplace_back("<无返回值函数定义>");
    }
    else
    {
        error("无返回值函数定义");
    }
}

// 复合语句
void fhyj()
{
    if (token == table["const"])
    {
        clsm();
        Forward();
    }
    if ((token == table["int"] || token == table["char"]) && (tokens[pos + 2] != table["("]))
    {
        blsm();
        Forward();
    }
    state_list();
    ans.emplace_back("<复合语句>");
}

void csb()
{ // TODO 测试出现死循环
    if (token == table["int"] || token == table["char"])
    {
        ADD();

        Forward();
        IDENFR();

        Forward();
        while (token == table[","])
        {
            ADD();
            Forward();
            if (token == table["int"] || token == table["char"])
            {
                ADD();

                Forward();
                IDENFR();
            }
            Forward();
        }
        Retrack();
        ans.emplace_back("<参数表>");
    }
    else if (token == table[")"])
    { // 参数为 空， 直接读取 ) 。需要回退一位
        Retrack();
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

        Forward();
        if (token == table["main"])
        {
            ADD();

            Forward();
            LPARENT();

            Forward();
            RPARENT();

            Forward();
            LBRACE();

            Forward();
            fhyj();

            Forward();
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

// 表达式
void expression()
{
    if (token == table["+"] || token == table["-"])
    {
        ADD();
        Forward();
    }
    item();

    Forward();
    while (token == table["+"] || token == table["-"])
    {
        ADD();

        Forward();
        item();

        Forward();
    }
    Retrack();
    ans.emplace_back("<表达式>");
}

// 项
void item()
{
    factor();

    Forward();
    while (token == table["*"] || token == table["/"])
    {
        ADD();

        Forward();
        factor();

        Forward();
    }
    Retrack();

    ans.emplace_back("<项>");
}

// 因子
void factor()
{
    if (token == table["标识符"])
    {
        IDENFR();
        Forward();
        if (token == table["["])
        {
            ADD();

            Forward();
            expression();

            Forward();
            RBRACK();

            Forward();
            if (token == table["["])
            {
                ADD();

                Forward();
                expression();

                Forward();
                RBRACK();
            }
            else
            {
                Retrack();
            }
        }
        else if (token == table["("])
        {
            Retrack();
            ans.pop_back();
            func_with_return();
        }
        else
        {
            Retrack();
        }
        ans.emplace_back("<因子>");
    }
    else if (token == table["("])
    {
        ADD();

        Forward();
        expression();

        Forward();
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
        loop_state();   //循环语句
        ans.emplace_back("<语句>");
    }
    else if (token == table["if"])
    {
        condi_state();
        ans.emplace_back("<语句>");
    }
    else if (token == table["标识符"] && (tokens[pos + 1] == table["="] || tokens[pos + 1] == table["["]))
    {
        assign_state(); // 赋值语句
        Forward();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["标识符"])
    {
        map<string, bool>::iterator iter;
        iter = functions.find(token); // 查找是否有返回值
        if(iter->second)
            func_with_return();
        else
            func_without_return();
        Forward();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["scanf"])
    {
        read_state();
        Forward();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["printf"])
    {
        write_state();
        Forward();
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else if (token == table["return"])
    {
        return_state();
        Forward();
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
        Forward();
        state_list();
        Forward();
        RBRACE();
        ans.emplace_back("<语句>");
    }
    else if (token == table[";"])   // 空语句
    {
        SEMICN();
        ans.emplace_back("<语句>");
    }
    else    // 出错
    {
        error("state()");
    }
}

// 赋值语句
void assign_state()
{
    if (token == table["标识符"])
    {
        ADD();

        Forward();
        if (token == table["="])
        {
            ADD();
            Forward();
            expression();
            ans.emplace_back("<赋值语句>");
        }
        else if (token == table["["])
        {
            ADD();
            Forward();
            expression();
            Forward();
            RBRACK();

            Forward();
            if (token == table["["])
            {
                ADD();
                Forward();
                expression();
                Forward();
                RBRACK();
                Forward();
            }
            ASSIGN();
            Forward();
            expression();
            ans.emplace_back("<赋值语句>");
        }
        else
        {
            error("assign_state()");
        }
    }
}
// 条件语句
void condi_state()
{
    if (token == table["if"])
    {
        ADD();

        Forward();
        LPARENT();
        Forward();
        condition();
        Forward();
        RPARENT();
        Forward();
        statement();
        Forward();
        if (token == table["else"])
        {
            ADD();
            Forward();
            statement();
            Forward();
        }
        Retrack();
        ans.emplace_back("<条件语句>");
    }
}
// 条件
void condition()
{
    expression();
    Forward();
    OP_COM();
    Forward();
    expression();
    ans.emplace_back("<条件>");
}
// 循环语句
void loop_state()
{
    if (token == table["while"])
    {
        ADD();
        Forward();
        LPARENT();
        Forward();
        condition();
        Forward();
        RPARENT();
        Forward();
        statement();
        ans.emplace_back("<循环语句>");
    }
    else if (token == table["for"])
    {
        ADD();
        Forward();
        LPARENT();
        Forward();
        IDENFR();
        Forward();
        ASSIGN();
        Forward();
        expression();
        Forward();
        SEMICN();
        Forward();
        condition();
        Forward();
        SEMICN();
        Forward();
        IDENFR();
        Forward();
        ASSIGN();
        Forward();
        IDENFR();
        Forward();
        if (token == table["+"] || token == table["-"])
        {
            ADD();
        }
        Forward();
        step_size();
        Forward();
        RPARENT();
        Forward();
        statement();
        ans.emplace_back("<循环语句>");
    }
    else
    {
        error("loop_state()");
    }
}
// 步长
void step_size()
{
    unsigned_int();
    ans.emplace_back("<步长>");
}
// 条件语句
void case_state()
{
    if (token == table["switch"])
    {
        ADD();
        Forward();
        LPARENT();
        Forward();
        expression();
        Forward();
        RPARENT();
        Forward();
        LBRACE();
        Forward();
        case_table();
        Forward();
        case_default();
        Forward();
        RBRACE();
        ans.emplace_back("<情况语句>");
    }
    else
    {
        error("case_state()");
    }
}
// 条件表
void case_table()
{
    case_sub();
    Forward();
    while (token == table["case"])
    {
        case_sub();
        Forward();
    }
    Retrack();
    ans.emplace_back("<情况表>");
}
// 条件子语句
void case_sub()
{
    if (token == table["case"])
    {
        ADD();
        Forward();
        ICCON();
        Forward();
        COLON();
        Forward();
        statement();
        ans.emplace_back("<情况子语句>");
    }
}
// 缺省
void case_default()
{
    if (token == table["default"])
    {
        ADD();
        Forward();
        COLON();
        Forward();
        statement();
        ans.emplace_back("<缺省>");
    }
}
// 有返回值函数调用
void func_with_return()
{
    IDENFR();
    Forward();
    LPARENT();
    Forward();
    param_list();
    Forward();
    RPARENT();
    ans.emplace_back("<有返回值函数调用语句>");
}
// 无返回值函数调用
void func_without_return()
{
    IDENFR();
    Forward();
    LPARENT();
    ans.emplace_back("<值参数表>");
    Forward();
    RPARENT();
    ans.emplace_back("<无返回值函数调用语句>");
}
// 参数表
void param_list()
{
    if (token == table["+"] || token == table["-"] || token == table["标识符"] || token == table["("] || token == table["整形常量"] || token == table["字符常量"])
    {
        expression();
        Forward();
        while (token == table[","])
        {
            ADD();
            Forward();
            expression();
            Forward();
        }
        Retrack();
        ans.emplace_back("<值参数表>");
    }
    else if (token == table[")"])
    {
        Retrack(); //会退一个，  )会有之后函数单独处理
        ans.emplace_back("<值参数表>");
    }
    else
    {
        error("param_list()");
    }
}
// 语句列
void state_list()
{
    while (token == table["while"] || token == table["for"] || token == table["if"] || token == table["标识符"] || token == table["scanf"] || token == table["printf"] || token == table["return"] || token == table["switch"] || token == table["{"] || token == table[";"])
    {
        statement();
        Forward();
    }
    Retrack();
    ans.emplace_back("<语句列>");
}
// 读语句
void read_state()
{
    if (token == table["scanf"])
    {
        ADD();
        Forward();
        LPARENT();
        Forward();
        IDENFR();
        Forward();
        RPARENT();
        ans.emplace_back("<读语句>");
    }
}
// 写语句
void write_state()
{
    if (token == table["printf"])
    {
        ADD();
        Forward();
        LPARENT();
        Forward();
        if (token == table["字符串"])
        {
            STRCON();
            Forward();
            if (token == table[","])
            {
                ADD();
                Forward();
                expression();
                Forward();
                RPARENT();
            }
            else if (token == table[")"])
            {
                RPARENT();
            }
            else
            {
                Retrack();
            }
        }
        else if (token == table["+"] || token == table["-"] || token == table["标识符"] || token == table["("] || token == table["整形常量"] || token == table["字符常量"])
        {
            expression();
            Forward();
            RPARENT();
        }
        ans.emplace_back("<写语句>");
    }
}
// 返回语句
void return_state()
{
    if (token == table["return"])
    {
        ADD();
        Forward();
        if (token == table["("])
        {
            LPARENT();
            Forward();
            expression();
            Forward();
            RPARENT();
            Forward();
        }
        Retrack();
        ans.emplace_back("<返回语句>");
    }
    else
    {
        error("return_state()");
    }
}
// 打印结果到文件
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
// 语法分析
int grammar_analyse(vector<string> &t, vector<string> &w)
{
    // // 读取数据
    // char str[100];
    // FILE * fp;
    // fp = fopen("tokens.txt", "r");
    // while(!feof(fp)){
    //     fgets(str,100,fp);
    //     // cout << str << endl;
    //     tokens.emplace_back(str);
    // }
    // fclose(fp);

    // fp = fopen("wordnames.txt", "r");
    // while(!feof(fp)){
    //     fgets(str,100,fp);
    //     // cout << str << endl;
    //     wordnames.emplace_back(str);
    // }
    // fclose(fp);
    tokens = t;
    wordnames = w;
    cout << tokens.size() << " " << wordnames.size() << endl;

    // 语法分析
    len = tokens.size();
    token = tokens[0];
    pos = 0;

    program();

    print_ans();
    return 0;
}
