#include "table.h"
#include "bits/stdc++.h"
using namespace std;

int pos = 0;  // tokenָ��λ��



vector<string> ans;
vector<string> tokens={
    "CONSTTK",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "LPARENT",
    "INTTK",
    "IDENFR",
    "RPARENT",
    "LBRACE",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "FORTK",
    "LPARENT",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "IDENFR",
    "LSS",
    "IDENFR",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "PLUS",
    "INTCON",
    "RPARENT",
    "LBRACE",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "PLUS",
    "IDENFR",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "SEMICN",
    "RBRACE",
    "RETURNTK",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "SEMICN",
    "RBRACE",
    "INTTK",
    "IDENFR",
    "LPARENT",
    "INTTK",
    "IDENFR",
    "RPARENT",
    "LBRACE",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "FORTK",
    "LPARENT",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "MINU",
    "INTCON",
    "SEMICN",
    "IDENFR",
    "GRE",
    "MINU",
    "INTCON",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "MINU",
    "INTCON",
    "RPARENT",
    "LBRACE",
    "IFTK",
    "LPARENT",
    "IDENFR",
    "EQL",
    "INTCON",
    "RPARENT",
    "LBRACE",
    "RETURNTK",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "SEMICN",
    "RBRACE",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "PLUS",
    "IDENFR",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "SEMICN",
    "RBRACE",
    "RETURNTK",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "SEMICN",
    "RBRACE",
    "INTTK",
    "IDENFR",
    "LPARENT",
    "INTTK",
    "IDENFR",
    "RPARENT",
    "LBRACE",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "WHILETK",
    "LPARENT",
    "IDENFR",
    "LEQ",
    "IDENFR",
    "MINU",
    "INTCON",
    "RPARENT",
    "LBRACE",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "PLUS",
    "IDENFR",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "IDENFR",
    "PLUS",
    "INTCON",
    "SEMICN",
    "RBRACE",
    "RETURNTK",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "SEMICN",
    "RBRACE",
    "CHARTK",
    "IDENFR",
    "LPARENT",
    "RPARENT",
    "LBRACE",
    "RETURNTK",
    "LPARENT",
    "CHARCON",
    "RPARENT",
    "SEMICN",
    "RBRACE",
    "VOIDTK",
    "MAINTK",
    "LPARENT",
    "RPARENT",
    "LBRACE",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "INTTK",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "LPARENT",
    "RPARENT",
    "RPARENT",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "RPARENT",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "RPARENT",
    "SEMICN",
    "IFTK",
    "LPARENT",
    "IDENFR",
    "GEQ",
    "INTCON",
    "RPARENT",
    "LBRACE",
    "PRINTFTK",
    "LPARENT",
    "INTCON",
    "RPARENT",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "LPARENT",
    "INTCON",
    "RPARENT",
    "RPARENT",
    "SEMICN",
    "RBRACE",
    "ELSETK",
    "LBRACE",
    "IFTK",
    "LPARENT",
    "IDENFR",
    "NEQ",
    "INTCON",
    "RPARENT",
    "LBRACE",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "RPARENT",
    "SEMICN",
    "RBRACE",
    "ELSETK",
    "LBRACE",
    "RBRACE",
    "RBRACE",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "RPARENT",
    "SEMICN",
    "IDENFR",
    "ASSIGN",
    "INTCON",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "SEMICN",
    "PRINTFTK",
    "LPARENT",
    "IDENFR",
    "LPARENT",
    "IDENFR",
    "RPARENT",
    "RPARENT",
    "SEMICN",
    "RETURNTK",
    "SEMICN",
    "RBRACE"
};



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

int len = tokens.size();
string token=tokens[0];

void error(string s){
    // cout << s + " error!" << endl;
    ans.emplace_back(s+" error!����!");
}

void NEXT(){
    if( pos+1 < len){
        token = tokens[++pos];
    }
}

void BACK(){
    if(pos-1 >= 0){
        token = tokens[--pos];
    }
}

void ADD(){
    ans.emplace_back(token);
}

void OP_PM(){
    if(token != table["+"] && token != table["-"]){
        error("OP_PM()");
    }
}

void OP_PD(){
    if(token != table["*"] && token != table["/"]){
        error("OP_PD()");
    }
}

void OP_COM(){
    if(token != table["<"] && token != table["<="] && token != table[">"] && token != table[">="] && token != table["!="] && token != table["=="]){
        error("OP_COM()");
    }else{
        ADD();
    }
}

void LBRACE(){
    if(token != table["{"]){
        error("LBRACE()");
    }else{
        ADD();
    }
}

void RBRACE(){
    if(token != table["}"]){
        error("RBRACE()");
    }else{
        ADD();
    }
}

void LBRACK(){
    if(token != table["["]){
        error("LBRACK()");
    }else{
        ADD();
    }
}

void RBRACK(){
    if(token != table["]"]){
        error("RBRACK()");
    }else{
        ADD();
    }
}

void LPARENT(){
    if(token != table["("]){
        error("LPARENT()");
    }else{
        ADD();
    }
}

void RPARENT(){
    if(token != table[")"]){
        error("RPARENT()");
    }else{
        ADD();
    }
}

void ALPHA(){
    if(token != table["�ַ�����"]){
        error("ALPHA()");
    }else{
        ADD();
    }
}

void STRCON(){
    if(token != table["�ַ���"]){
        error("STRCON()");
    }else{
        ADD();
        ans.emplace_back("<�ַ���>");
    }
}

void CONST(){
    if(token != table["const"]){
        error("CONST()");
    }else{
        ADD();
    }
}

void SEMICN(){
    if(token != table[";"]){
        error("SEMICN()");
    }else{
        ADD();
    }
}

void COLON(){
    if(token != table[":"]){
        error("COLON()");
    }else{
        ADD();
    }
}

void ASSIGN(){
    if(token != table["="]){
        error("ASSIGN()");
    }else{
        ADD();
    }
}
void IDENFR(){
    if(token != table["��ʶ��"]){
        error("IDENFR()");
    }else{
        ADD();
    }
}

void unsigned_int(){
    if(token != table["���γ���"]){
        error("unsigned_int()");
    }else{
        ADD();
        ans.emplace_back("<�޷�������>");
    }
}

void INTCON(){
    if(token == table["+"] || token == table["-"]){
        ADD();
        NEXT();
        unsigned_int();
        ans.emplace_back("<����>");
    }else if(token == table["���γ���"]){
        unsigned_int();
        ans.emplace_back("<����>");
    }else{
        error("INTCON()");
    }
}

void CHARCON(){
    if(token != table["�ַ�����"]){
        error("CHARCON()");
    }else{
        ADD();
    }
}

void program(){
    if(token==table["const"]){
        clsm();
        NEXT();
    }
    if( tokens[pos+2]!=table["("] && (token==table["int"] || token==table["char"])){	// Ӧ����0 
        blsm();
        NEXT();
    }
    while(tokens[pos+2]==table["("] && (token==table["int"] || token==table["char"] || token==table["void"])){	// Ӧ����1 
        if(token==table["int"] || token==table["char"]){
            func_with_return_def();
        }
        if(token==table["void"] && tokens[pos+1]!=table["main"]){   // ������������
            func_without_return_def();
        }
        NEXT();
    }
    BACK();
    main_func();
    ans.emplace_back("<����>");
}


void clsm(){
    while(token == table["const"]){
        CONST();

        NEXT();
        cldy();

        NEXT();
        SEMICN();

        NEXT();
    }
    BACK();
    ans.emplace_back("<����˵��>");
}

void cldy(){
    if(token == table["int"]){
        ADD();

        NEXT();
        IDENFR();

        NEXT();
        ASSIGN();

        NEXT();
        INTCON();

        NEXT();
        while(token == table[","]){
            ADD();

            NEXT();
            IDENFR();

            NEXT();
            ASSIGN();

            NEXT();
            INTCON();

            NEXT(); // �鿴֮��һ���ǲ��ǡ��������ж�ѭ��
        }
        BACK();
        ans.emplace_back("<��������>");

    }else if(token == table["char"]){
        ADD();

        NEXT();
        IDENFR();

        NEXT();
        ASSIGN();

        NEXT();
        CHARCON();

        NEXT();
        while(token == table[","]){
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
        ans.emplace_back("<��������>");
        
    }else{
        error("cldy()");
    }
}

void smtb(){
    if(token == table["int"]){
        ADD();

        NEXT();
        IDENFR();
        ans.emplace_back("<����ͷ��>");
    }else if(token == table["char"]){
        ADD();

        NEXT();
        IDENFR();
        ans.emplace_back("<����ͷ��>");
    }else{
        error("smtb()");
    }
}

void ICCON(){   // ����
    if(token == table["�ַ�����"]){
        ADD();
        ans.emplace_back("<����>");
    }else if(token==table["+"] || token==table["-"] ||token == table["���γ���"]){
        INTCON();
        ans.emplace_back("<����>");
    }else{
        error("ICCON()");
    }
}

void blsm(){
    bldy();

    NEXT();
    SEMICN();

    NEXT();
    while((token==table["int"] || token==table["char"]) && tokens[pos+2] != table["("]){
        bldy();

        NEXT();
        SEMICN();

        NEXT();
    }

    BACK();
    ans.emplace_back("<����˵��>");
}

void bldy(){
    if(pos+2<len && tokens[pos+2] == table["="]){
        bldy_init();
    }else if(pos+5<len && tokens[pos+2] == table["["] && tokens[pos+5] == table["="]){
        bldy_init();
    }else if(pos+8<len && tokens[pos+2] == table["["] && tokens[pos+5] == table["["] && tokens[pos+8] == table["="]){
        bldy_init();
    }else{
        bldy_uninit();
    }

    ans.emplace_back("<��������>");
}

void bldy_uninit(){
    if(token==table["int"] || token==table["char"]){
        ADD();

        NEXT();
        if(token==table["��ʶ��"]){
            ADD();

            NEXT();
            if(token==table["["]){
                ADD();

                NEXT();
                unsigned_int();

                NEXT();
                if(token==table["]"]){
                    ADD();
                }
                
                NEXT();
                if(token==table["["]){
                    ADD();

                    NEXT();
                    unsigned_int();

                    NEXT();
                    if(token==table["]"]){
                        ADD();
                    }
                }else{
                    BACK();
                }
            }else{
                BACK();
            }
        }

    }

    NEXT();
    while(token==table[","]){
        ADD();
        NEXT();
        if(token==table["��ʶ��"]){
            ADD();

            NEXT();
            if(token==table["["]){
                ADD();

                NEXT();
                unsigned_int();

                NEXT();
                RBRACK();
                
                NEXT();
                if(token==table["["]){
                    ADD();

                    NEXT();
                    unsigned_int();

                    NEXT();
                    RBRACK();
                }else{
                    BACK();
                }
            }else{
                BACK();
            }
        }
        NEXT();
    }
    BACK();
    ans.emplace_back("<���������޳�ʼ��>");
}

void bldy_init(){
    if(token==table["int"] || token==table["char"]){
        ADD();

        NEXT();
        IDENFR();

        NEXT();
        if(token==table["="]){
            ADD();

            NEXT();
            ICCON();
        }else if(token==table["["]){
            ADD();
            NEXT();
            unsigned_int();
            NEXT();
            RBRACK();

            NEXT();
            if(token==table["="]){
                ADD();
                NEXT();
                LBRACE();

                NEXT();
                ICCON();

                NEXT();
                while(token==table[","]){
                    ADD();

                    NEXT();
                    ICCON();

                    NEXT();
                }// ���� } �Ż��˳�
                RBRACE();
            }else if(token==table["["]){
                ADD();          // [
                NEXT();
                unsigned_int(); // �޷�������
                NEXT();
                RBRACK();   // ]

                NEXT();
                ASSIGN();   // =

                NEXT();
                LBRACE();   // {

                NEXT();
                LBRACE();   // {
                
                NEXT();
                ICCON();

                NEXT();
                while(token==table[","]){
                    ADD();

                    NEXT();
                    ICCON();

                    NEXT();
                }
                // ����˵�������� }
                RBRACE();

                NEXT();
                while(token==table[","]){
                    ADD();

                    NEXT();
                    LBRACE();
                    NEXT();
                    ICCON();

                    NEXT();
                    while(token==table[","]){
                        ADD();
                        NEXT();
                        ICCON();

                        NEXT();
                    }
                    // ����˵�������� }
                    RBRACE();
                    NEXT();
                }
                // ����˵�������� }
                RBRACE();
            }
        }
        ans.emplace_back("<�������弰��ʼ��>");
    }
}

void func_with_return_def(){
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

    ans.emplace_back("<�з���ֵ��������>");
}

void func_without_return_def(){
    if(token==table["void"]){
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
        RPARENT();

        ans.emplace_back("<�޷���ֵ��������>");
    }else{
        error("�޷���ֵ��������");
    }
}

void fhyj(){
    if(token==table["const"]){
        clsm();
        NEXT();
    }
    if((token==table["int"] || token==table["char"]) && (tokens[pos+2]!=table["("]) ){
        blsm();
        NEXT();
    }
    state_list();
    ans.emplace_back("<�������>");
}

void csb(){ // ��ѭ��
    if(token==table["int"] || token==table["char"]){
        ADD();

        NEXT();
        IDENFR();

        NEXT();
        while(token==table[","]){
            ADD();
            NEXT();
            if(token==table["int"] || token==table["char"]){
                ADD();

                NEXT();
                IDENFR();
				
            }
            NEXT();
        }
        BACK();
        ans.emplace_back("<������>");
    }else if(token==table[")"]){    // ����Ϊ �գ� ֱ�Ӷ�ȡ ) ����Ҫ����һλ
        BACK();
        ans.emplace_back("<������>");
    }else{
        error("������");
    }
}

void main_func(){
    if(token==table["void"]){
        ADD();

        NEXT();
        if(token==table["main"]){
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
            ans.emplace_back("<������>");
        }else{
            error("main");
        }
    }else{
        error("main");
    }
}

void expression(){
    if(token==table["+"] || token==table["-"]){
        ADD();
        NEXT();
    }
    xiang();

    NEXT();
    while(token==table["+"] || token==table["-"]){
        ADD();

        NEXT();
        xiang();

        NEXT();
    }
    BACK();
    ans.emplace_back("<���ʽ>");
}

void xiang(){
    factor();

    NEXT();
    while(token==table["*"] || token==table["/"]){
        ADD();

        NEXT();
        factor();

        NEXT();
    }
    BACK();

    ans.emplace_back("<��>");
}

void factor(){
    if(token==table["��ʶ��"]){
        IDENFR();
        NEXT();
        if(token==table["["]){
            ADD();

            NEXT();
            expression();

            NEXT();
            RBRACK();

            NEXT();
            if(token==table["["]){
                ADD();

                NEXT();
                expression();

                NEXT();
                RBRACK();
            }else{
                BACK();
            }
        }else if(token==table["("]){
            BACK();
            ans.pop_back();
            func_with_return();
        }else{
            BACK();
        }
        ans.emplace_back("<����>");
    }else if(token==table["("]){
        ADD();

        NEXT();
        expression();

        NEXT();
        RPARENT();
        ans.emplace_back("<����>");
    }else if(token==table["���γ���"] || token==table["+"] || token==table["-"]){
        INTCON();
        ans.emplace_back("<����>");
    }else if(token==table["�ַ�����"]){
        CHARCON();
        ans.emplace_back("<����>");
    }else{
        error("����");
    }
}

void statement(){   // ���
    if(token==table["while"] || token==table["for"]){
        loop_state();
        ans.emplace_back("<���>");
    }
    else if(token==table["if"]){
        condi_state();
        ans.emplace_back("<���>");
    }
    else if(token==table["��ʶ��"] && tokens[pos+2]==table[")"]){
        func_without_return();
        NEXT();SEMICN();
        ans.emplace_back("<���>");
    }
    else if(token==table["��ʶ��"] && (tokens[pos+1]==table["="] || tokens[pos+1]==table["["])){
        assign_state();
        NEXT();SEMICN();
        ans.emplace_back("<���>");
    }
    else if(token==table["��ʶ��"] && tokens[pos+2]!=table[")"]){
        func_with_return();
        NEXT();SEMICN();
        ans.emplace_back("<���>");
    }
    else if(token==table["scanf"]){
        read_state();
        NEXT();SEMICN();
        ans.emplace_back("<���>");
    }
    else if(token==table["printf"]){
        write_state();
        NEXT();SEMICN();
        ans.emplace_back("<���>");
    }
    else if(token==table["return"]){
        return_state();
        NEXT();SEMICN();
        ans.emplace_back("<���>");
    }
    else if(token==table["switch"]){
        case_state();
        ans.emplace_back("<���>");
    }
    else if(token==table["{"]){
        LBRACE();
        NEXT();state_list();
        NEXT();RBRACE();
        ans.emplace_back("<���>");
    }
    else if(token==table[";"]){
        SEMICN();
        ans.emplace_back("<���>");
    }else{
        error("state()");
    }
}

void assign_state(){
    if(token==table["��ʶ��"]){
        ADD();

        NEXT();
        if(token==table["="]){
            ADD();
            NEXT();
            expression();
            ans.emplace_back("<��ֵ���>");
        }else if(token==table["["]){
            ADD();
            NEXT();
            expression();
            NEXT();
            RBRACK();

            NEXT();
            if(token==table["["]){
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
            ans.emplace_back("<��ֵ���>");
        }else{
            error("assign_state()");
        }
    }
}

void condi_state(){
    if(token==table["if"]){
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
        if(token==table["else"]){
            ADD();
            NEXT();
            statement();
            NEXT();
        }
        BACK();
        ans.emplace_back("<�������>");
    }
}

void condition(){
    expression();
    NEXT();
    OP_COM();
    NEXT();
    expression();
    ans.emplace_back("����");
}

void loop_state(){
    if(token==table["while"]){
        ADD();
        NEXT();
        LPARENT();
        NEXT();
        condition();
        NEXT();
        RPARENT();
        NEXT();
        statement();
        ans.emplace_back("<ѭ�����>");
    }else if(token==table["for"]){
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
        if(token==table["+"] || token==table["-"]){
            ADD();
        }
        NEXT();
        step_size();
        NEXT();
        RPARENT();
        NEXT();
        statement();
        ans.emplace_back("<ѭ�����>");
    }else{
        error("loop_state()");
    }
}

void step_size(){
    unsigned_int();
    ans.emplace_back("<����>");
}

void case_state(){
    if(token==table["switch"]){
        ADD();
        NEXT();LPARENT();
        NEXT();expression();
        NEXT();RPARENT();
        NEXT();LBRACE();
        NEXT();case_table();
        NEXT();case_default();
        NEXT();RBRACE();
        ans.emplace_back("<������>");
    }else{
        error("case_state()");
    }
}

void case_table(){
    case_sub();
    NEXT();
    if(token==table["case"]){
        case_sub();
        NEXT();
    }
    BACK();
    ans.emplace_back("<�����>");
}

void case_sub(){
    if(token==table["case"]){
        ADD();
        NEXT();ICCON();
        NEXT();COLON();
        NEXT();statement();
        ans.emplace_back("<��������>");
    }
}

void case_default(){
    if(token==table["default"]){
        ADD();
        NEXT();COLON();
        NEXT();statement();
        ans.emplace_back("<ȱʡ>");
    }
}

void func_with_return(){
    IDENFR();
    NEXT();LPARENT();
    NEXT();param_list();
    NEXT();RPARENT();
    ans.emplace_back("<�з���ֵ�����������>");
}

void func_without_return(){
    IDENFR();
    NEXT();LPARENT();
    ans.emplace_back("<ֵ������>");
    NEXT();RPARENT();
    ans.emplace_back("<�޷���ֵ�����������>");
}

void param_list(){
    if(token==table["+"] || token==table["-"] || token==table["��ʶ��"] || token==table["("] || token==table["���γ���"] || token==table["�ַ�����"]){
        expression();
        NEXT();
        while(token==table[","]){
            ADD();
            NEXT();expression();
            NEXT();
        }
        BACK();
        ans.emplace_back("<ֵ������>");
    }else if(token==table[")"]){
        BACK(); //����һ����  )����֮������������
        ans.emplace_back("<ֵ������>");
    }else{
        error("param_list()");
    }
}

void state_list(){
    while(token==table["while"] || token==table["for"] || token==table["if"] || token==table["��ʶ��"] || token==table["scanf"] || token==table["printf"] || token==table["return"] || token==table["switch"] || token==table["{"]  || token==table[";"]){
        statement();
        NEXT();
    }
    BACK();
    ans.emplace_back("<�����>");
}

void read_state(){
    if(token==table["scanf"]){
        ADD();
        NEXT();LPARENT();
        NEXT();IDENFR();
        NEXT();RPARENT();
        ans.emplace_back("<�����>");
    }
}

void write_state(){
    if(token==table["printf"]){
        ADD();
        NEXT();LPARENT();
        NEXT();
        if(token==table["�ַ���"]){
            STRCON();
            NEXT();
            if(token==table[","]){
                ADD();
                NEXT();expression();
                NEXT();RPARENT();
            }else if(token==table[")"]){
                RPARENT();
            }else{
                BACK();
            }
        }else if(token==table["+"] || token==table["-"] || token==table["��ʶ��"] || token==table["("] || token==table["���γ���"] || token==table["�ַ�����"]){
            expression();
            NEXT();RPARENT();
        }
        ans.emplace_back("<д���>");
    }
}

void return_state(){
    if(token==table["return"]){
        ADD();
        NEXT();
        if(token==table["("]){
            LPARENT();
            NEXT();expression();
            NEXT();RPARENT();
            NEXT();
        }
        BACK();
        ans.emplace_back("<�������>");
    }else{
        error("return_state()");
    }
}

void print_ans(){
	ofstream outfile;
	outfile.open("output.txt");
	for (int i = 0; i < ans.size(); i++){
		outfile << ans[i] << endl;
	}
	outfile.close();
}

int main(){
    program();
    int n=ans.size();
    print_ans();

   return 0;
}



