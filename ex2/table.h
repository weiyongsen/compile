#pragma once
#include <iostream>
#include <vector>
#include <map>
using namespace std;

string signal_char = "+-*/:;,()[]{}";   // ����������ַ�
string signal_comparison = "<>=!";      // ��Ŀ�Ƚ������ַ� 
vector<string> double_cocmparison {"<=",">=","==","!="};    // ˫Ŀ�Ƚ������ַ� 
vector<string> key_word{"const","int","char","void",
"main","if","else","switch","case",
"default","while","for",
"scanf","printf","return"}; // �ؼ����б�

map<string, string> table = {    // ��������
    {"��ʶ��",	"IDENFR"},
    {"else",	"ELSETK"},
    {"-",	"MINU"},
    {"=",	"ASSIGN"},
    {"���γ���",	"INTCON"},
    {"switch",	"SWITCHTK"},
    {"*",	"MULT"},
    {";",	"SEMICN"},
    {"�ַ�����",	"CHARCON"},
    {"case",	"CASETK"},
    {"/",	"DIV"},
    {",",	"COMMA"},
    {"�ַ���",	"STRCON"},
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
    {"!",   "��"},
};