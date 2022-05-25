#include "bits/stdc++.h"
using namespace std;

string signal_char = "+-*/:;,()[]{}";   // 单个处理的字符
string signal_comparison = "<>=!";      // 单目比较运算字符 
vector<string> double_cocmparison {"<=",">=","==","!="};    // 双目比较运算字符 
vector<string> key_word{"const","int","char","void",
"main","if","else","switch","case",
"default","while","for",
"scanf","printf","return"}; // 关键字列表

map<string,string> table = {    // 词类编码表
    {"标识符",	"IDENFR"},	
    {"else",	"ELSETK"},	
    {"-",	"MINU"},	
    {"=",	"ASSIGN"},
    {"整形常量",	"INTCON"},	
    {"switch",	"SWITCHTK"},	
    {"*",	"MULT"},	
    {";",	"SEMICN"},
    {"字符常量",	"CHARCON"},	
    {"case",	"CASETK"},	
    {"/",	"DIV"},	
    {",",	"COMMA"},
    {"字符串",	"STRCON"},	
    {"default",	"DEFAULTTK"},	
    {"<",	"LSS"},	
    {"(",	"LPARENT"},
    {"const",	"CONSTTK"},		
    {"while",	"WHILETK"},	
    {"<=",	"LEQ"},	
    {")",	"RPARENT"},
    {"int",	"INTTK"},	
    {"for",	"FORTK"},	
    {">",	"GRE"},	
    {"[",	"LBRACK"},
    {"char",	"CHARTK"},	
    {"scanf",	"SCANFTK"},	
    {">=",	"GEQ"},	
    {"]",	"RBRACK"},
    {"void",	"VOIDTK"},	
    {"printf",	"PRINTFTK"},	
    {"==",	"EQL"},	
    {"{",	"LBRACE"},
    {"main",	"MAINTK"},	
    {"return",	"RETURNTK"},	
    {"!=",	"NEQ"},	
    {"}",	"RBRACE"},
    {"if",	"IFTK"},	
    {"+",	"PLUS"},	
    {":",	"COLON"},
    {"!",   "非"},
};