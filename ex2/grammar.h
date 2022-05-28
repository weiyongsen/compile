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


vector<string> ans;     // ��¼ÿ�ε�ʶ����
vector<string> tokens;  // �����, ʵ��һ���������
vector<string> wordnames;   // �������ƣ� ʵ��һ�����ֵ
map<string, bool> functions;  // ��¼�����Ƿ��ɷ���ֵ
int len = 0;    // tokens����
int pos;        // tokenָ��λ��
string token = "";      // ��ǰȡ��������� tokens[pos]



// ָ��ǰ��
void Forward()
{
    if (pos + 1 < len)
    {
        token = tokens[++pos];
    }
}

// ָ�����һ��
void Retrack()
{
    if (pos - 1 >= 0)
    {
        token = tokens[--pos];
    }
}

// ��ӵ�ǰ  ����� �� ��������
void ADD()
{
    ans.emplace_back(token + " " + wordnames[pos]);
}

// ������Ϣ
void error(string s)
{
    // cout << s + " error!" << endl;
    ans.emplace_back(s + " error!����!");
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
    if (token != table["�ַ�����"])
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
    if (token != table["�ַ���"])
    {
        error("STRCON()");
    }
    else
    {
        ADD();
        ans.emplace_back("<�ַ���>");
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

// �ж��Ƿ�Ϊ��ʶ��
void IDENFR()
{
    if (token != table["��ʶ��"])
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
    if (token != table["���γ���"])
    {
        error("unsigned_int()");
    }
    else
    {
        ADD();
        ans.emplace_back("<�޷�������>");
    }
}

void INTCON()
{
    if (token == table["+"] || token == table["-"])
    {
        ADD();
        Forward();
        unsigned_int();
        ans.emplace_back("<����>");
    }
    else if (token == table["���γ���"])
    {
        unsigned_int();
        ans.emplace_back("<����>");
    }
    else
    {
        error("INTCON()");
    }
}

void CHARCON()
{
    if (token != table["�ַ�����"])
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
    { // Ӧ����0
        blsm();
        Forward();
    }
    while (tokens[pos + 2] == table["("] && (token == table["int"] || token == table["char"] || token == table["void"]))
    { // Ӧ����1
        if (token == table["int"] || token == table["char"])
        {
            func_with_return_def();
        }
        if (token == table["void"] && tokens[pos + 1] != table["main"])
        { // ������������
            func_without_return_def();
        }
        Forward();
    }
    Retrack();
    main_func();
    ans.emplace_back("<����>");
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
    ans.emplace_back("<����˵��>");
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

            Forward(); // �鿴֮��һ���ǲ��ǡ��������ж�ѭ��
        }
        Retrack();
        ans.emplace_back("<��������>");
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
        ans.emplace_back("<��������>");
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
        
        ans.emplace_back("<����ͷ��>");
    }
    else if (token == table["char"])
    {
        ADD();

        Forward();
        IDENFR();
        ans.emplace_back("<����ͷ��>");
    }
    else
    {
        error("smtb()");
    }
}

void ICCON()
{ // ����
    if (token == table["�ַ�����"])
    {
        ADD();
        ans.emplace_back("<����>");
    }
    else if (token == table["+"] || token == table["-"] || token == table["���γ���"])
    {
        INTCON();
        ans.emplace_back("<����>");
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
    ans.emplace_back("<����˵��>");
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

    ans.emplace_back("<��������>");
}

// ���������޳�ʼ��
void bldy_uninit()
{
    if (token == table["int"] || token == table["char"])
    {
        ADD();

        Forward();
        if (token == table["��ʶ��"])
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
        if (token == table["��ʶ��"])
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
    ans.emplace_back("<���������޳�ʼ��>");
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
                } // ���� } �Ż��˳�
                RBRACE();
            }
            else if (token == table["["])
            {
                ADD(); // [
                Forward();
                unsigned_int(); // �޷�������
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
                // ����˵�������� }
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
                    // ����˵�������� }
                    RBRACE();
                    Forward();
                }
                // ����˵�������� }
                RBRACE();
            }
        }
        ans.emplace_back("<�������弰��ʼ��>");
    }
}

// �з���ֵ��������
void func_with_return_def()
{
    if(token == table["int"] || token == table["char"]){
        // ��¼�з���ֵ
        functions[wordnames[pos+1]] = true;
        smtb();

        Forward();        LPARENT();

        Forward();        csb();

        Forward();        RPARENT();

        Forward();        LBRACE();

        Forward();        fhyj();

        Forward();        RBRACE();

        ans.emplace_back("<�з���ֵ��������>");
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

        ans.emplace_back("<�޷���ֵ��������>");
    }
    else
    {
        error("�޷���ֵ��������");
    }
}

// �������
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
    ans.emplace_back("<�������>");
}

void csb()
{ // TODO ���Գ�����ѭ��
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
        ans.emplace_back("<������>");
    }
    else if (token == table[")"])
    { // ����Ϊ �գ� ֱ�Ӷ�ȡ ) ����Ҫ����һλ
        Retrack();
        ans.emplace_back("<������>");
    }
    else
    {
        error("������");
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
            ans.emplace_back("<������>");
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

// ���ʽ
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
    ans.emplace_back("<���ʽ>");
}

// ��
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

    ans.emplace_back("<��>");
}

// ����
void factor()
{
    if (token == table["��ʶ��"])
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
        ans.emplace_back("<����>");
    }
    else if (token == table["("])
    {
        ADD();

        Forward();
        expression();

        Forward();
        RPARENT();
        ans.emplace_back("<����>");
    }
    else if (token == table["���γ���"] || token == table["+"] || token == table["-"])
    {
        INTCON();
        ans.emplace_back("<����>");
    }
    else if (token == table["�ַ�����"])
    {
        CHARCON();
        ans.emplace_back("<����>");
    }
    else
    {
        error("����");
    }
}

void statement()
{ // ���
    if (token == table["while"] || token == table["for"])
    {
        loop_state();   //ѭ�����
        ans.emplace_back("<���>");
    }
    else if (token == table["if"])
    {
        condi_state();
        ans.emplace_back("<���>");
    }
    else if (token == table["��ʶ��"] && (tokens[pos + 1] == table["="] || tokens[pos + 1] == table["["]))
    {
        assign_state(); // ��ֵ���
        Forward();
        SEMICN();
        ans.emplace_back("<���>");
    }
    else if (token == table["��ʶ��"])
    {
        map<string, bool>::iterator iter;
        iter = functions.find(token); // �����Ƿ��з���ֵ
        if(iter->second)
            func_with_return();
        else
            func_without_return();
        Forward();
        SEMICN();
        ans.emplace_back("<���>");
    }
    else if (token == table["scanf"])
    {
        read_state();
        Forward();
        SEMICN();
        ans.emplace_back("<���>");
    }
    else if (token == table["printf"])
    {
        write_state();
        Forward();
        SEMICN();
        ans.emplace_back("<���>");
    }
    else if (token == table["return"])
    {
        return_state();
        Forward();
        SEMICN();
        ans.emplace_back("<���>");
    }
    else if (token == table["switch"])
    {
        case_state();
        ans.emplace_back("<���>");
    }
    else if (token == table["{"])
    {
        LBRACE();
        Forward();
        state_list();
        Forward();
        RBRACE();
        ans.emplace_back("<���>");
    }
    else if (token == table[";"])   // �����
    {
        SEMICN();
        ans.emplace_back("<���>");
    }
    else    // ����
    {
        error("state()");
    }
}

// ��ֵ���
void assign_state()
{
    if (token == table["��ʶ��"])
    {
        ADD();

        Forward();
        if (token == table["="])
        {
            ADD();
            Forward();
            expression();
            ans.emplace_back("<��ֵ���>");
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
            ans.emplace_back("<��ֵ���>");
        }
        else
        {
            error("assign_state()");
        }
    }
}
// �������
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
        ans.emplace_back("<�������>");
    }
}
// ����
void condition()
{
    expression();
    Forward();
    OP_COM();
    Forward();
    expression();
    ans.emplace_back("<����>");
}
// ѭ�����
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
        ans.emplace_back("<ѭ�����>");
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
        ans.emplace_back("<ѭ�����>");
    }
    else
    {
        error("loop_state()");
    }
}
// ����
void step_size()
{
    unsigned_int();
    ans.emplace_back("<����>");
}
// �������
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
        ans.emplace_back("<������>");
    }
    else
    {
        error("case_state()");
    }
}
// ������
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
    ans.emplace_back("<�����>");
}
// ���������
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
        ans.emplace_back("<��������>");
    }
}
// ȱʡ
void case_default()
{
    if (token == table["default"])
    {
        ADD();
        Forward();
        COLON();
        Forward();
        statement();
        ans.emplace_back("<ȱʡ>");
    }
}
// �з���ֵ��������
void func_with_return()
{
    IDENFR();
    Forward();
    LPARENT();
    Forward();
    param_list();
    Forward();
    RPARENT();
    ans.emplace_back("<�з���ֵ�����������>");
}
// �޷���ֵ��������
void func_without_return()
{
    IDENFR();
    Forward();
    LPARENT();
    ans.emplace_back("<ֵ������>");
    Forward();
    RPARENT();
    ans.emplace_back("<�޷���ֵ�����������>");
}
// ������
void param_list()
{
    if (token == table["+"] || token == table["-"] || token == table["��ʶ��"] || token == table["("] || token == table["���γ���"] || token == table["�ַ�����"])
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
        ans.emplace_back("<ֵ������>");
    }
    else if (token == table[")"])
    {
        Retrack(); //����һ����  )����֮������������
        ans.emplace_back("<ֵ������>");
    }
    else
    {
        error("param_list()");
    }
}
// �����
void state_list()
{
    while (token == table["while"] || token == table["for"] || token == table["if"] || token == table["��ʶ��"] || token == table["scanf"] || token == table["printf"] || token == table["return"] || token == table["switch"] || token == table["{"] || token == table[";"])
    {
        statement();
        Forward();
    }
    Retrack();
    ans.emplace_back("<�����>");
}
// �����
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
        ans.emplace_back("<�����>");
    }
}
// д���
void write_state()
{
    if (token == table["printf"])
    {
        ADD();
        Forward();
        LPARENT();
        Forward();
        if (token == table["�ַ���"])
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
        else if (token == table["+"] || token == table["-"] || token == table["��ʶ��"] || token == table["("] || token == table["���γ���"] || token == table["�ַ�����"])
        {
            expression();
            Forward();
            RPARENT();
        }
        ans.emplace_back("<д���>");
    }
}
// �������
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
        ans.emplace_back("<�������>");
    }
    else
    {
        error("return_state()");
    }
}
// ��ӡ������ļ�
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
// �﷨����
int grammar_analyse(vector<string> &t, vector<string> &w)
{
    // // ��ȡ����
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

    // �﷨����
    len = tokens.size();
    token = tokens[0];
    pos = 0;

    program();

    print_ans();
    return 0;
}
