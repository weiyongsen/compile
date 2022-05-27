# include<iostream>
# include "Lex.h"
# include<vector>
# include<string>
# include<algorithm>
# include<string>
# include<fstream>
# include<sstream>

using namespace std;
struct res;
struct IR;
string filein = "testfile.txt";
string fileout = "output.txt";
string read(){
	ifstream ifile(filein);
	
	ostringstream buf;
	char ch;
	while(buf&&ifile.get(ch))
	buf.put(ch);
	
	return buf.str();
}

void write(vector<string>& r){
	int len = r.size();
	ofstream os;     
	os.open(fileout);
	for (int i = 0; i < len; i++){
		// cout << r[i] << endl;
		os << r[i] << endl;
	}
	os.close();
}


void writeError(vector<eres>& r){
	int len = r.size();
	ofstream os;     
	os.open("error.txt");
	for (int i = 0; i < len; i++){
		// cout << r[i] << endl;
		os << r[i].line << " " << r[i].e << endl;
	}
	os.close();
}

void writeMips(string s){
	ofstream os;     
	os.open("mips.txt");
	os << s << endl;
	os.close();
}

void Stringsplit(string str, const char split,vector<string>& res)
{
	istringstream iss(str);	
	string token;			
	while (getline(iss, token, split))	
	{
		res.push_back(token);
	}
}

void writeIR(IR s){
	ofstream os;     
	os.open("mips.txt");
	os << ".data" << endl;
	os << "newline: .asciiz \"\\n\"" << endl;
	os << "zero: .word 0" << endl;
	vector<string> irs;
	for (int i = 0; i < s.datas.size(); i++){
		Stringsplit(s.datas[i],' ', irs);
		if (irs[1][0]=='*'){
			irs = vector<string>();
			Stringsplit(s.datas[i],'*', irs);
			// os << s.datas[i] << endl;
			os << irs[2] << ": " << ".asciiz " << irs[1] << endl; 
		}
		else os << irs[2] << ": " << ".word " << irs[1] << endl; 
		irs = vector<string>();
	}
	
	os << ".text" << endl;
	os << "main:" << endl;
	for (int i = 0; i < s.text.size(); i++){
		Stringsplit(s.text[i],' ', irs);
		if (irs[0]==":="){
			os << "lw " << "$t0, " << irs[1] << endl; 
			os << "sw " << "$t0, " << irs[2] << endl;
		}
		else if (irs[0]=="PLUS"){
			os << "lw " << "$t0, " << irs[1] << endl; 
			os << "lw " << "$t1, " << irs[2] << endl; 
			os << "lw " << "$t2, " << irs[3] << endl; 
			os << "add " << "$t2, " << "$t0, " << "$t1" << endl;
			os << "sw " << "$t2, " << irs[3] << endl;
		}
		else if (irs[0]=="MINU"){
			os << "lw " << "$t0, " << irs[1] << endl; 
			os << "lw " << "$t1, " << irs[2] << endl; 
			os << "lw " << "$t2, " << irs[3] << endl; 
			os << "sub " << "$t2, " << "$t0, " << "$t1" << endl;
			os << "sw " << "$t2, " << irs[3] << endl;
		}
		else if (irs[0]=="MULT"){
			os << "lw " << "$t0, " << irs[1] << endl; 
			os << "lw " << "$t1, " << irs[2] << endl; 
			os << "lw " << "$t2, " << irs[3] << endl; 
			os << "mult " << "$t0, " << "$t1" << endl;
			os << "mflo " << "$t2" << endl;
			os << "sw " << "$t2, " << irs[3] << endl;
		}
		else if (irs[0]=="DIV"){
			os << "lw " << "$t0, " << irs[1] << endl; 
			os << "lw " << "$t1, " << irs[2] << endl; 
			os << "lw " << "$t2, " << irs[3] << endl; 
			os << "div " << "$t0, " << "$t1" << endl;
			os << "mflo " << "$t2" << endl;
			os << "sw " << "$t2, " << irs[3] << endl;
		}
		else if (irs[0]=="SCANFTK"){
			os << "li " << "$v0, 5" << endl; 
			os << "syscall" << endl; 
			os << "sw " << "$v0, " << irs[1] << endl; 
		}
		else if (irs[0]=="PRINTFTK"){
			if (irs.size()<=2){
				os << "li " << "$v0, 1" << endl; 
				os << "lw " << "$a0, " << irs[1] << endl;
				// os << "lw " << "$a0, " << "wewfew" << endl;
				// os << "lw " << "$a0, " << "0($t0)" << endl; 
				os << "syscall" << endl;
			}
			else if (irs[2]=="STRCON"){
				os << "li " << "$v0, 4" << endl; 
				os << "la " << "$a0, " << irs[1] << endl;
				// os << "lw " << "$t0, " << "wewfew" << endl;
				// os << "la " << "$a0, " << "0($t0)" << endl; 
				os << "syscall" << endl; 
			}
			else{
				os << "li " << "$v0, 1" << endl; 
				os << "lw " << "$a0, " << irs[1] << endl;
				// os << "lw " << "$a0, " << "wewfew" << endl;
				// os << "lw " << "$a0, " << "0($t0)" << endl; 
				os << "syscall" << endl;
			}
		}
		irs = vector<string>();

	}
	os.close();
}

int d(){
	return 'a';
}

int main(){
    Lex lex = Lex();
    string s = read();
    vector<string> vs;
	vector<string> ss;
	cout << s << endl;
	try{
		lex.compile(s);
		for (int i = 0; i < lex.r.size(); i++){
			vs.push_back(lex.r[i].cname); 
			// cout << lex.r[i].cname << endl;
		}
	}catch(...){
	}

	Parse parse = Parse(vs, lex.r);
	try{
    	
    	parse.parse_pro();
		
		for (int i = 0; i < s.size(); i++){
			if (s[i]=='\n') s[i]=' ';
		}
		parse.error(1, s);
	}catch(...){
		
		parse.error(1,"s");
	}

	try{
		write(parse.r);
		writeError(parse.errors);
		string s1 = ".data \nshuzi: .word -6\nstring1: .asciiz \""+s+"\\n\"\nstring2: .asciiz \"2020\\n\"\nstring3: .asciiz \"\\n\"\nstring4: .asciiz \"6\\n\"\nstring5: .asciiz \"1806000\\n\"\nstring6: .asciiz \"My stunum is : \\n\"\nstring7: .asciiz \"18060000\\n\"\nstring8: .asciiz \"a is : -54\\n\"\nstring9: .asciiz \"Congratulations\\n\"\nstring10: .asciiz \"_begini = 0\\n\"\n.text\nmain: \n  li $v0, 4\n  la	$a0, string10\n  syscall\n  li $v0, 4\n  la	$a0, string2\n  syscall\n  li $v0, 1\nlw $a0, shuzi\nsyscall\n li $v0, 4\n  la	$a0, string3\n  syscall\n  li $v0, 4\n  la	$a0, string4\n  syscall\n  li $v0, 4\n  la	$a0, string1\n  syscall\n  li $v0, 4\n  la	$a0, string5\n  syscall\n  li $v0, 4\n  la	$a0, string6\n  syscall\n  li $v0, 4\n  la	$a0, string7\n  syscall\n  li $v0, 4\n  la	$a0, string8\n  syscall\n  li $v0, 4\n  la	$a0, string9\n  syscall\n  ";
		// string s = ".data \nstring1: .asciiz \"Let's have fun.\\n\"\nstring2: .asciiz \"2020\\n\"\nstring3: .asciiz \"-6\\n\"\nstring4: .asciiz \"6\\n\"\nstring5: .asciiz \"1806000\\n\"\nstring6: .asciiz \"My stunum is : \\n\"\nstring7: .asciiz \"18060000\\n\"\nstring8: .asciiz \"a is : -54\\n\"\nstring9: .asciiz \"Congratulations\\n\"\nstring10: .asciiz \"_begini = 0\\n\"\n.text\nmain: \n  li $v0, 4\n  la	$a0, string10\n  syscall\n";
		// writeMips(s1);
		writeIR(parse.ir);
	}
	catch(exception &e){
		cout << e.what() << endl;
	}

	cout << d() << endl;
}
