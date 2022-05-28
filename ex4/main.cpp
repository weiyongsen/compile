#include <iostream>
#include <vector>
#include <string>
#include "lex.h"
// #include "grammar.h"
// #include "error.h"
#include "mips.h"

using namespace std;

void writeIR(vector<fe> &m, map<string,bool> &iden);

int main() {
	/*vector<vector<string>> tn;
	tn = lex_analyse();
	cout << tn.size() << endl;
	grammar_analyse(tn[0], tn[1]);*/
	vector<string> tokens;
	vector<string> names;
	vector<int> rows;
	vector<fe> m_code;

	lex_analyse(tokens, names, rows);
	
	mips_generate(tokens, names, rows, m_code);
	cout << "four_element:" << endl;
	for (int i = 0; i < m_code.size(); i++){
		cout << m_code[i].op << ", " << m_code[i].arg1 << ", " << m_code[i].arg2 << ", " << m_code[i].result << endl;
	}

	map<string, bool> all_iden;
	for (map<string,bool>::iterator i = identifiers.begin(); i !=identifiers.end() ;i++){
		all_iden[i->first] = i->second;
	}
	for (map<string,bool>::iterator i = identifiers_local.begin(); i !=identifiers_local.end() ;i++){
		all_iden[i->first] = i->second;
	}
	writeIR(m_code, all_iden);

	for (map<string,bool>::iterator i = all_iden.begin(); i !=all_iden.end() ;i++){
		cout << i->first << " " << i->second << endl;
	}
	

	return 0;
}


void writeIR(vector<fe> &m, map<string,bool> &iden){
	ofstream os;     
	os.open("mips.txt");
	// 赋初值
	os << ".data" << endl;
	os << "newline: .asciiz \"\\n\"" << endl;
	os << "zero: .word 0" << endl;
	for (int i = 0; i < m.size();i++){
		if(m[i].op == table["="]){
			bool is_find, is_int;
			string pre_name = m[i].arg1;
			string name = m[i].result;

			map<string, bool>::iterator iter;
			iter = iden.find(name);

			if(iter != iden.end()){
				is_int = iter->second;
				// pre_name不是标识符
				if(iden.find(pre_name) == iden.end()){
					os << m[i].result << ": " << ".word " << m[i].arg1 << endl;
				}
			}else{		// 没找到就将其将其添加到变量中
				if(m[i].arg1==""){
					os << m[i].result << ": " << ".word " << "0" << endl;
					iden[name] = 1;
				}else if(m[i].arg1[0] == '\"' ){	// 说明是字符串
					os << m[i].result << ": " << ".asciiz " << m[i].arg1 << endl;
					iden[name] = 0;
				}else{	// 和pre_name 一个类型
					iter = iden.find(pre_name);
					if(iter != iden.end()){
						is_int = iter->second;
						if(is_int){
							os << m[i].result << ": " << ".word " << "0" << endl;
							iden[name] = 1;
						}else{
							os << m[i].result << ": " << ".asciiz " << "\"\"" << endl;
							iden[name] = 0;
						}
					}
					else{
						os << m[i].result << ": " << ".word " << m[i].arg1 << endl;
							iden[name] = 1;
					}

					
				}
			}
			
		}else if(m[i].op == table["+"] || m[i].op==table["-"] || m[i].op==table["*"] || m[i].op==table["/"]){
			bool is_int;
			string pre_name = m[i].arg1;
			string name = m[i].result;

			map<string, bool>::iterator iter;
			iter = iden.find(pre_name);

			if(iter != iden.end()){
				is_int = iter->second;

				// 添加到iden
				if(is_int){
					os << m[i].result << ": " << ".word " << "0" << endl;
					iden[name] = is_int;
				}else{
					os << m[i].result << ": " << ".asciiz " << "\"\"" << endl;
					iden[name] = is_int;
				}
				
			}else if(pre_name=="zero"){
				os << m[i].result << ": " << ".word " << "0" << endl;
				iden[name] = 1;
			}
		}
	}

	// 运算
	os << ".text" << endl;
	os << "main:" << endl;
	for (int i = 0; i < m.size(); i++){
		// cout << m[i].op << ", " << m[i].arg1 << ", " << m[i].arg2 << ", " << m[i].result << endl;
		if (m[i].op==table["="]){
			string pre_name = m[i].arg1;
			map<string, bool>::iterator iter;
			iter = iden.find(pre_name);
			if(iter!=iden.end()){
				os << "lw " << "$t0, " << m[i].arg1 << endl; 
				os << "sw " << "$t0, " << m[i].result << endl;
			}
		}
		else if (m[i].op==table["+"]){
			os << "lw " << "$t0, " << m[i].arg1 << endl; 
			os << "lw " << "$t1, " << m[i].arg2 << endl; 
			os << "lw " << "$t2, " << m[i].result << endl; 
			os << "add " << "$t2, " << "$t0, " << "$t1" << endl;
			os << "sw " << "$t2, " << m[i].result << endl;
		}
		else if (m[i].op==table["-"]){
			os << "lw " << "$t0, " << m[i].arg1 << endl; 
			os << "lw " << "$t1, " << m[i].arg2 << endl; 
			os << "lw " << "$t2, " << m[i].result << endl; 
			os << "sub " << "$t2, " << "$t0, " << "$t1" << endl;
			os << "sw " << "$t2, " << m[i].result << endl;
		}
		else if (m[i].op==table["*"]){
			os << "lw " << "$t0, " << m[i].arg1 << endl; 
			os << "lw " << "$t1, " << m[i].arg2 << endl; 
			os << "lw " << "$t2, " << m[i].result << endl; 
			os << "mult " << "$t0, " << "$t1" << endl;
			os << "mflo " << "$t2" << endl;
			os << "sw " << "$t2, " << m[i].result << endl;
		}
		else if (m[i].op==table["/"]){
			os << "lw " << "$t0, " << m[i].arg1 << endl; 
			os << "lw " << "$t1, " << m[i].arg2 << endl; 
			os << "lw " << "$t2, " << m[i].result << endl; 
			os << "div " << "$t0, " << "$t1" << endl;
			os << "mflo " << "$t2" << endl;
			os << "sw " << "$t2, " << m[i].result << endl;
		}
		else if (m[i].op==table["scanf"]){
			os << "li " << "$v0, 5" << endl; 
			os << "syscall" << endl; 
			os << "sw " << "$v0, " << m[i].result << endl; 
		}
		else if (m[i].op==table["printf"]){
			if(m[i].result=="newline"){
				os << "li " << "$v0, 4" << endl; 
				os << "la " << "$a0, " << m[i].result << endl;
				os << "syscall" << endl;
				continue;
			}
			// 判断类型
			bool is_int = false;
			map<string, bool>::iterator iter;
			iter = iden.find(m[i].result);
			is_int = iter->second;
			
			//
			if (!is_int){
				// 字符串
				os << "li " << "$v0, 4" << endl; 
				os << "la " << "$a0, " << m[i].result << endl;
				os << "syscall" << endl;
			}
			else{
				// 整形常量
				os << "li " << "$v0, 1" << endl; 
				os << "lw " << "$a0, " << m[i].result << endl;
				os << "syscall" << endl;
			}

		}
	}
	os.close();
}