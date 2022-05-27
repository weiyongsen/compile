#ifndef LEX_H
#define LEX_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

struct res
{
	string name;
	string cname;
	int line;
};

struct eres{
	int line;
	string e;
};

class Lex
{
private:
	int lineNum;
	int state;
	string token;
	string keys[15] = {
		"const",
		"int",
		"char",
		"void",
		"main",
		"if",
		"else",
		"switch",
		"case",
		"default",
		"while",
		"for",
		"scanf",
		"printf",
		"return"};
	string keyIDs[15] = {
		"CONSTTK",
		"INTTK",
		"CHARTK",
		"VOIDTK",
		"MAINTK",
		"IFTK",
		"ELSETK",
		"SWITCHTK",
		"CASETK",
		"DEFAULTTK",
		"WHILETK",
		"FORTK",
		"SCANFTK",
		"PRINTFTK",
		"RETURNTK"};

public:
	vector<res> r;
	Lex();
	bool isletter(char c);
	bool isdigit(char c);
	void addres(string name, string cname);
	void cat(char c);
	int reserve();
	void compile(string s);
};

class Namespace{
	public:
		Namespace * father;
		Namespace * son;
		vector<string> ns;
		vector<string> nstype;
		vector<bool> nsisconst;
		Namespace();
		bool isHave(string s);
		bool findName(string s);
		string findType(string s);
		bool isConst(string s);
};

struct IR{
	vector<string> datas;
	vector<string> text;
};

class Parse
{
private:
	string id_now;
	string op, arg1, arg2, result;
	int index, index_r;
	int tempCount = 0;
	int expCount = 0;
	vector<string> tokens;
	vector<res> rlex;
	map<string, bool> isfuncre;
	map<string, int> funcnum;
	map<string, vector<string>> functype;
	Namespace * names;
	bool isFuncHaveRe;
	string caseType;
	bool haveDefault;
	// 用于判断函数返回错误
	bool isReDe;
	bool isReAc;
	string functypede;
	string functypeac;
	bool isgetretype;

public:
	IR ir;
	vector<string> r;
	vector<eres> errors;
	Parse(vector<string> &t, vector<res> &r);
	bool parse_add();
	bool parse_mul();
	bool parse_rel();
	bool parse_letter();
	bool parse_digit();
	bool parse_char();
	bool parse_string();
	bool parse_pro();
	bool parse_consta();
	bool parse_conde();
	bool parse_uint();
	bool parse_int();
	bool parse_id();
	bool parse_stahead();
	bool parse_const(string type);
	bool parse_varsta();
	bool parse_varde();
	bool parse_vardewoinit();
	bool parse_vardeinit();
	bool parse_subvardewoinit();
	bool parse_subvardeinit(string type);
	bool parse_funcdefre();
	bool parse_classid();
	bool parse_funcdefwore();
	bool parse_compsta(bool isRe);
	bool parse_paratable(string s);
	bool parse_mainfunc();
	bool parse_express(string type);
	bool parse_item(string type);
	bool parse_factor(string type);
	// bool parse_express();
	// bool parse_item();
	// bool parse_factor();
	bool parse_subfactor();
	bool parse_statement(bool isRe);
	bool parse_assign();
	bool parse_condista(bool isRe);
	bool parse_condi();
	bool parse_circusta(bool isRe);
	bool parse_stepsize();
	bool parse_casesta(bool isRe);
	bool parse_casetable(bool isRe, string type);
	bool parse_casesubsta(bool isRe, string type);
	bool parse_default();
	bool parse_funccallstare(string type);
	bool parse_funccallstawore();
	int parse_valparatable(string s);
	bool parse_statecol(bool isRe);
	bool parse_readsta();
	bool parse_writesta();
	bool parse_returnsta(bool isRe);
	bool test_char(char c);
	bool test_string(string s);
	void error(int line, string s);
	bool findAssign();
};

// class TreeNode{
// 	public:
// 		TreeNode* father;
// 		string name;
// 		string cname;
// 		TreeNode();
// };

// TreeNode::TreeNode(TreeNode* f = nullptr, string n = ""; string cn = ""){
// 	this->father = f;
// 	this->name = n;
// 	this->cname = cn;
// }

Namespace::Namespace(){
	this->father = nullptr;
	this->son = nullptr;
	this->ns = vector<string>();
	this->nstype = vector<string>();
	this->nsisconst = vector<bool>();
}

bool Namespace::isHave(string s){
	string t = s;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	if (count(this->ns.begin(), this->ns.end(), t)==0) return false;
	else return true;
}

bool Namespace::findName(string s){
	Namespace * temp = this;
	while(temp){
		for (int i = 0; i < temp->ns.size(); i ++){
			if (temp->ns[i]==s) return true;
		}
		temp = temp->father;
	} 
	return false;
}

string Namespace::findType(string s){
	Namespace * temp = this;
	while(temp){
		for (int i = 0; i < temp->ns.size(); i ++){
			if (temp->ns[i]==s) return temp->nstype[i];
		}
		temp = temp->father;
	} 
	return "null";
}

bool Namespace::isConst(string s){
	Namespace * temp = this;
	while(temp){
		for (int i = 0; i < temp->ns.size(); i ++){
			if (temp->ns[i]==s) return temp->nsisconst[i];
		}
		temp = temp->father;
	} 
	return false;
}

Lex::Lex()
{
	this->state = 0;
	this->r = vector<res>();
	this->token = "";
	this->lineNum = 1;
}

bool Lex::isletter(char c)
{
	int t = (int)c;
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return true;
	else
		return false;
}

bool Lex::isdigit(char c)
{
	int t = (int)c;
	if ((c >= 48 && c <= 57))
		return true;
	else
		return false;
}

void Lex::addres(string name, string cname)
{
	this->r.push_back({name, cname, this->lineNum});
}

void Lex::cat(char c)
{
	this->token += c;
}

int Lex::reserve()
{
	string t = token;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	for (int i = 0; i < 15; i++)
	{
		if (this->keys[i] == t)
			return i;
	}
	return -1;
}

void Lex::compile(string s)
{
	int len = s.size();
	for (int i = 0; i < len; i++)
	{
		switch (state)
		{
		case 0:
		{
			if (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\r'){
				if (s[i] == '\n')  this->lineNum++;
				break;
			}
			this->token = "";
			if (isletter(s[i]) || s[i] == '_')
			{
				cat(s[i]);
				state = 1;
				break;
			}
			if (isdigit(s[i]))
			{
				cat(s[i]);
				state = 2;
				break;
			}
			switch (s[i])
			{
			case '<':
			{
				state = 8;
				cat(s[i]);
				break;
			}
			case '>':
			{
				state = 9;
				cat(s[i]);
				break;
			}
			case '\'':
			{
				state = 12;
				break;
			}
			case '\"':
			{
				state = 13;
				break;
			}
			case ':':
			{
				state = 0;
				addres(":", "COLON");
				break;
			}
			case '=':
			{
				state = 10;
				cat(s[i]);
				break;
			}
			case ';':
			{
				state = 0;
				addres(";", "SEMICN");
				break;
			}
			case ',':
			{
				state = 0;
				addres(",", "COMMA");
				break;
			}
			case '(':
			{
				state = 0;
				addres("(", "LPARENT");
				break;
			}
			case ')':
			{
				state = 0;
				addres(")", "RPARENT");
				break;
			}
			case '[':
			{
				state = 0;
				addres("[", "LBRACK");
				break;
			}
			case ']':
			{
				state = 0;
				addres("]", "RBRACK");
				break;
			}
			case '{':
			{
				state = 0;
				addres("{", "LBRACE");
				break;
			}
			case '}':
			{
				state = 0;
				addres("}", "RBRACE");
				break;
			}
			case '+':
			{
				state = 0;
				addres("+", "PLUS");
				break;
			}
			case '-':
			{
				state = 0;
				addres("-", "MINU");
				break;
			}
			case '*':
			{
				state = 0;
				addres("*", "MULT");
				break;
			}
			case '/':
			{
				state = 0;
				addres("/", "DIV");
				break;
			}
			case '!':
			{
				state = 11;
				cat(s[i]);
				break;
			}
			default:
			{
				state = 14;
				break;
			}
			}
			break;
		}
		case 1:
		{
			if (isletter(s[i]) || isdigit(s[i]) || s[i] == '_')
			{
				state = 1;
				cat(s[i]);
			}
			else
			{
				i--;
				state = 0;
				int index = reserve();
				if (index >= 0)
				{
					addres(this->token, this->keyIDs[index]);
				}
				else
				{
					addres(this->token, "IDENFR");
				}
			}
			break;
		}
		case 2:
		{
			if (isdigit(s[i]))
			{
				state = 2;
				cat(s[i]);
			}
			else
			{
				i--;
				state = 0;
				addres(token, "INTCON");
			}
			break;
		}
		case 8:
		{
			switch (s[i])
			{
			case '=':
			{
				cat(s[i]);
				state = 0;
				addres("<=", "LEQ");
				break;
			}
			default:
			{
				i--;
				state = 0;
				addres("<", "LSS");
				break;
			}
			}
			break;
		}
		case 9:
		{
			switch (s[i])
			{
			case '=':
			{
				cat(s[i]);
				state = 0;
				addres(">=", "GEQ");
				break;
			}
			default:
			{
				i--;
				state = 0;
				addres(">", "GRE");
				break;
			}
			}
			break;
		}
		case 10:
		{
			switch (s[i])
			{
			case '=':
			{
				cat(s[i]);
				state = 0;
				addres("==", "EQL");
				break;
			}
			default:
			{
				i--;
				state = 0;
				addres("=", "ASSIGN");
				break;
			}
			}
			break;
		}
		case 11:
		{
			switch (s[i])
			{
			case '=':
			{
				cat(s[i]);
				state = 0;
				addres("!=", "NEQ");
				break;
			}
			default:
			{ //未处理
				state = 0;
				break;
			}
			}
			break;
		}
		case 12:
		{
			if (s[i] == '\'')
			{
				state = 0;
				addres(this->token, "CHARCON");
			}
			else
			{ //已经读入一个字符
				state = 15;
				cat(s[i]);
			}
			break;
		}
		case 15:
		{
			if (s[i] == '\'')
			{
				state = 0;
				addres(this->token, "CHARCON");
			}
			else
			{ //错误的处理
				state = 14;
				i--;
			}
			break;
		}
		case 13:
		{
			if (s[i] == '\"')
			{
				state = 0;
				addres(this->token, "STRCON");
			}
			else
			{
				state = 13;
				cat(s[i]);
			}
			break;
		}
		}
	}
}

Parse::Parse(vector<string> &t, vector<res> &r)
{
	this->index = 0;
	this->index_r = 0;
	this->tokens = t;
	this->rlex = r;
	this->names = new Namespace();
}

bool Parse::parse_add()
{
	if (this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	return true;
}

bool Parse::parse_mul()
{
	if (this->tokens[this->index] == "MULT" || this->tokens[this->index] == "DIV")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	return true;
}

bool Parse::parse_rel()
{
	if (this->tokens[this->index] == "LSS" || this->tokens[this->index] == "LEQ" || this->tokens[this->index] == "GRE" || this->tokens[this->index] == "GEQ" || this->tokens[this->index] == "EQL" || this->tokens[this->index] == "NEQ")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	return true;
}

bool Parse::parse_letter()
{
	return true;
}

bool Parse::parse_digit()
{
	return true;
}

bool Parse::test_char(char c)
{
	int t = (int)c;
	if ((c >= 48 && c <= 57) || (c >= 97 && c <= 122) || (c >= 65 && c <= 90) || c == 43 || c == 45 || c == 42 || c == 47 || c==95)
		return true;
	else
		return false;
}

bool Parse::parse_char()
{
	if (this->tokens[this->index] == "CHARCON")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		if (!this->test_char(this->rlex[this->index_r].name[0])) this->error(this->rlex[this->index_r].line, "a");
		this->index_r++;
		this->index++;
	}
	else
		return false;
	return true;
}

bool Parse::test_string(string s){
	if (s.size()==0) return false;
	for (int i = 0; i < s.size(); i++){
		if (s[i]==' ') continue;
		if ((s[i]<32)||s[i]>126) {return false;}
	}
	return true;
}

bool Parse::parse_string()
{
	if (this->tokens[this->index] == "STRCON")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		string o = ":= ", a1 = "*\""+this->rlex[this->index_r].name+"\"* ", r = "__temp"+to_string(this->tempCount++);
		this->ir.datas.push_back(o+a1+r);
		cout << o+a1+r << endl;
		this->id_now = r;
		if (!this->test_string(this->rlex[this->index_r].name)) this->error(this->rlex[this->index_r].line, "a");
		this->index_r++;
		this->index++;
	}
	else
		return false;
	cout << "<字符串>" << endl;
	this->r.push_back("<字符串>");
	return true;
}

bool Parse::parse_pro()
{ // 逻辑？？？
	bool isDefre = true;
	if (this->tokens[this->index] == "CONSTTK")
	{
		if (!this->parse_consta())
			return false;
	}
	if ((this->tokens[this->index] == "CHARTK"&&(this->tokens[this->index+2] == "ASSIGN"||this->tokens[this->index+2] == "LBRACK"||this->tokens[this->index+2] == "SEMICN"||this->tokens[this->index+2] == "COMMA")) || (this->tokens[this->index] == "INTTK"&&(this->tokens[this->index+2] == "ASSIGN"||this->tokens[this->index+2] == "LBRACK"||this->tokens[this->index+2] == "SEMICN"||this->tokens[this->index+2] == "COMMA")))
	{
		if (!this->parse_varsta())
			return false;
	}
	while ((this->tokens[this->index] == "INTTK" || this->tokens[this->index] == "CHARTK") || (this->tokens[this->index] == "VOIDTK" && this->tokens[this->index + 1] == "IDENFR"))
	{
		if (this->tokens[this->index] == "INTTK" || this->tokens[this->index] == "CHARTK")
		{
			if (!this->parse_funcdefre())
				return false;
		}
		else if (this->tokens[this->index] == "VOIDTK" && this->tokens[this->index + 1] == "IDENFR")
		{
			if (!this->parse_funcdefwore())
				return false;
		}
	}
	if (this->tokens[this->index] == "VOIDTK" && this->tokens[this->index + 1] == "MAINTK")
	{
		if (!this->parse_mainfunc())
			return false;
	}
	cout << "<程序>" << endl;
	this->r.push_back("<程序>");
	return true;
}

bool Parse::parse_consta()
{
	do
	{
		if (this->tokens[this->index] == "CONSTTK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;

		if (!this->parse_conde())
			return false;

		if (this->tokens[this->index] == "SEMICN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r-1].line, "k");
		}
	} while (this->tokens[this->index] == "CONSTTK");

	cout << "<常量说明>" << endl;
	this->r.push_back("<常量说明>");
	return true;
}

bool Parse::parse_conde()
{
	if (this->tokens[this->index] == "INTTK")
	{
		do
		{
			//四元式初始化
			this->op = ":= ";
			this->arg2 = "";

			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;

			// 判断是否重复定义，并更新namespace
			string t = this->rlex[this->index_r].name;
			transform(t.begin(), t.end(), t.begin(), ::tolower);
			if (this->names->isHave(t)) this->error(this->rlex[this->index_r].line, "b");
			else {
				string t = this->rlex[this->index_r].name;
				transform(t.begin(), t.end(), t.begin(), ::tolower);
				this->names->ns.push_back(t);
				this->names->nstype.push_back("INTTK");
				this->names->nsisconst.push_back(true);
			}

			if (!this->parse_id())
				return false;

			// 四元式 result
			result = this->id_now;

			if (this->tokens[this->index] == "ASSIGN")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else
				return false;
			if (!this->parse_int())
				return false;
			
			//四元式 arg1
			arg1 = id_now+" ";
			this->ir.datas.push_back(op+arg1+arg2+result);
			cout << op+arg1+arg2+result << endl;
		} while (this->tokens[this->index] == "COMMA");

		cout << "<常量定义>" << endl;
		this->r.push_back("<常量定义>");
		return true;
	}
	else if (this->tokens[this->index] == "CHARTK")
	{
		do
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
			
			// 判断是否重复定义，并更新namespace
			string t = this->rlex[this->index_r].name;
			transform(t.begin(), t.end(), t.begin(), ::tolower);
			if (this->names->isHave(t)) this->error(this->rlex[this->index_r].line, "b");
			else {
				string t = this->rlex[this->index_r].name;
				transform(t.begin(), t.end(), t.begin(), ::tolower);
				this->names->ns.push_back(t);
				this->names->nstype.push_back("CHARTK");
				this->names->nsisconst.push_back(true);
			}

			if (!this->parse_id())
				return false;
			if (this->tokens[this->index] == "ASSIGN")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else
				return false;
			if (!this->parse_char())
				return false;
		} while (this->tokens[this->index] == "COMMA");

		cout << "<常量定义>" << endl;
		this->r.push_back("<常量定义>");
		return true;
	}
	else
		return false;
}

bool Parse::parse_uint()
{ //???
	if (this->tokens[this->index] == "INTCON")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		id_now = this->rlex[this->index_r].name;
		this->index_r++;
		this->index++;
	}
	else
		return false;

	cout << "<无符号整数>" << endl;
	this->r.push_back("<无符号整数>");
	return true;
}

bool Parse::parse_int()
{
	string fuhao = "";
	if (this->tokens[this->index] == "PLUS")
	{
		fuhao = "";
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	if (this->tokens[this->index] == "MINU")
	{
		fuhao = "-";
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	if (!parse_uint())
		return false;
	
	id_now = fuhao+id_now;

	cout << "<整数>" << endl;
	this->r.push_back("<整数>");
	return true;
}

bool Parse::parse_id()
{
	if (this->tokens[this->index] == "IDENFR")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		id_now = this->rlex[this->index_r].name;
		this->index_r++;
		this->index++;
	}
	else
		return false;
	return true;
}

bool Parse::parse_stahead()
{
	if (this->tokens[this->index] == "INTTK")
	{
		this->functypede = "INTTK";
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (this->tokens[this->index] == "IDENFR")
		{
			// 判断是否重复定义，并更新namespace
			string t = this->rlex[this->index_r].name;
			transform(t.begin(), t.end(), t.begin(), ::tolower);
			if (this->names->isHave(t)) this->error(this->rlex[this->index_r].line, "b");
			
			//增加命名表元素
			t = this->rlex[this->index_r].name;
			transform(t.begin(), t.end(), t.begin(), ::tolower);
			this->names->ns.push_back(t);
			this->names->nstype.push_back("INTTK");
			this->names->nsisconst.push_back(false);

			this->isfuncre[this->rlex[this->index_r].name] = true;
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;
		cout << "<声明头部>" << endl;
		this->r.push_back("<声明头部>");
		return true;
	}
	else if (this->tokens[this->index] == "CHARTK")
	{
		this->functypede = "CHARTK";
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (this->tokens[this->index] == "IDENFR")
		{

			// 判断是否重复定义，并更新namespace
			string t = this->rlex[this->index_r].name;
			transform(t.begin(), t.end(), t.begin(), ::tolower);
			if (this->names->isHave(t)) this->error(this->rlex[this->index_r].line, "b");
			
			//增加命名表元素
			t = this->rlex[this->index_r].name;
			transform(t.begin(), t.end(), t.begin(), ::tolower);
			this->names->ns.push_back(t);
			this->names->nstype.push_back("CHARTK");
			this->names->nsisconst.push_back(false);

			this->isfuncre[this->rlex[this->index_r].name] = true;
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			
			return false;
		}
		cout << "<声明头部>" << endl;
		this->r.push_back("<声明头部>");
		return true;
	}
	else
		return false;
}

bool Parse::parse_const(string s)
{
	if (this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU" || this->tokens[this->index] == "INTCON")
	{
		if (!this->parse_int())
			return false;

		cout << "<常量>" << endl;
		this->r.push_back("<常量>");
		
		if (s=="INTTK") return true;
		else {
			this->error(this->rlex[this->index_r].line, "o");
			return true;
		}
	}
	else if (this->tokens[this->index] == "CHARCON")
	{
		if (!this->parse_char())
			return false;

		cout << "<常量>" << endl;
		this->r.push_back("<常量>");
		
		if (s=="CHARTK") return true;
		else {
			this->error(this->rlex[this->index_r].line, "o");
			return true;
		}
	}
	else
		return false;
}

bool Parse::parse_varsta()
{
	do
	{
		if (!this->parse_varde())
			return false;
		if (this->tokens[this->index] == "SEMICN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r-1].line, "k");
		}
	} while (((this->tokens[this->index] == "INTTK" || this->tokens[this->index] == "CHARTK") && this->tokens[this->index + 1] == "IDENFR") &&
			 (this->tokens[this->index + 2] != "LPARENT"));
	cout << "<变量说明>" << endl;
	this->r.push_back("<变量说明>");
	return true;
}

bool Parse::findAssign(){
	for (int i = this->index+2; i < this->tokens.size(); i++){
		if (this->tokens[i] == "SEMICN"||this->tokens[i] == "INTTK"||this->tokens[i] == "CHARTK"||this->tokens[i] == "IDENFR") break;
		if (this->tokens[i]=="ASSIGN") return true;
	}
	return false;
}

bool Parse::parse_varde()
{
	if (!this->findAssign())
	{
		if (this->parse_vardewoinit())
		{
			cout << "<变量定义>" << endl;
			this->r.push_back("<变量定义>");
			return true;
		}
		else
			return false;
	}
	else
	{
		if (this->parse_vardeinit())
		{
			cout << "<变量定义>" << endl;
			this->r.push_back("<变量定义>");
			return true;
		}
		else
			return false;
	}
}

bool Parse::parse_vardewoinit()
{ // 小括号？？

	// 四元式初始化
	this->op = ":= ";
	this->arg2 = "";

	if (!parse_classid())
		return false;
	string classstr = this->tokens[this->index-1];

	// 判断是否重复定义，并更新namespace
	if (this->tokens[this->index] != "IDENFR") return false;
	string t = this->rlex[this->index_r].name;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	if (this->names->isHave(t)) this->error(this->rlex[this->index_r].line, "b");
	else {
		string t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		this->names->ns.push_back(t);
		this->names->nstype.push_back(this->tokens[this->index-1]);
		this->names->nsisconst.push_back(false);
	}

	if (!parse_id())
		return false;
	this->result = t;
	if (!parse_subvardewoinit())
		return false;
	this->arg1 = "0 ";
	this->ir.datas.push_back(op+arg1+arg2+result);
	cout << op+arg1+arg2+result << endl;
	while (this->tokens[this->index] == "COMMA")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;

		// 判断是否重复定义，并更新namespace
		if (this->tokens[this->index] != "IDENFR") return false;
		t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (this->names->isHave(t)) this->error(this->rlex[this->index_r].line, "b");
		else {
			t = this->rlex[this->index_r].name;
			transform(t.begin(), t.end(), t.begin(), ::tolower);
			this->names->ns.push_back(t);
			this->names->nstype.push_back(classstr);
			this->names->nsisconst.push_back(false);
		}
		this->result = t;
		if (!parse_id())
			return false;
		if (!parse_subvardewoinit())
			return false;

		this->arg1 = "0 ";
		this->ir.datas.push_back(op+arg1+arg2+result);
		cout << op+arg1+arg2+result << endl;
	}
	cout << "<变量定义无初始化>" << endl;
	this->r.push_back("<变量定义无初始化>");
	return true;
}

bool Parse::parse_subvardewoinit()
{

	if (this->tokens[this->index] == "LBRACK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (!parse_uint()){
			this->error(this->rlex[this->index_r].line, "i");
			this->index_r++;
			this->index++;
		}
		if (this->tokens[this->index] == "RBRACK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r].line, "m");
		}

		if (this->tokens[this->index] == "LBRACK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
			if (!parse_uint()){
				this->error(this->rlex[this->index_r].line, "i");
				this->index_r++;
				this->index++;
			}
			if (this->tokens[this->index] == "RBRACK")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else{
			this->error(this->rlex[this->index_r].line, "m");
		}
		}
	}
	else
		return true;
	return true;
}

bool Parse::parse_vardeinit()
{
	// 四元式初始化
	this->op = ":= ";
	this->arg2 = "";

	if (!parse_classid())
		return false;
	
	// 判断是否重复定义，并更新namespace
	if (this->tokens[this->index] != "IDENFR") return false;
	string t = this->rlex[this->index_r].name;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	if (this->names->isHave(t)) this->error(this->rlex[this->index_r].line, "b");
	else {
		string t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		this->names->ns.push_back(t);
		this->names->nstype.push_back(this->tokens[this->index-1]);
		this->names->nsisconst.push_back(false);
	}

	// 四元式 result
	result = t;

	if (!parse_id())
		return false;
	if (!parse_subvardeinit(this->tokens[this->index-2]))
		return false;

	this->ir.datas.push_back(op+arg1+arg2+result);
	cout << op+arg1+arg2+result << endl;

	cout << "<变量定义及初始化>" << endl;
	this->r.push_back("<变量定义及初始化>");
	return true;
}

bool Parse::parse_subvardeinit(string s)
{
	if (this->tokens[this->index] == "ASSIGN")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		;
		if (!this->parse_const(s))
			return false;
		
		//四元式 arg1
		this->arg1 = id_now+" ";
	}
	else if (this->tokens[this->index] == "LBRACK")
	{
		int countxde = 0;
		int countyde = 0;
		int countx = 0;
		int county = 0;
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (!parse_uint()){
			this->error(this->rlex[this->index_r].line, "i");
			this->index_r++;
			this->index++;
		}

		if (this->tokens[this->index-1] == "INTCON") countxde = atoi(this->rlex[this->index_r-1].name.c_str());
		
		if (this->tokens[this->index] == "RBRACK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r].line, "m");
		}
		if (this->tokens[this->index] == "ASSIGN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
			if (this->tokens[this->index] == "LBRACE")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else
				return false;
			if (!parse_const(s))
				return false;
			countx++;
			while (this->tokens[this->index] == "COMMA")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
				if (!parse_const(s))
					return false;
				countx++;
			}
			if (this->tokens[this->index] == "RBRACE")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else
				return false;
		}
		else if (this->tokens[this->index] == "LBRACK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
			if (!parse_uint()){
				this->error(this->rlex[this->index_r].line, "i");
				this->index_r++;
				this->index++;
			}
			if (this->tokens[this->index-1] == "INTCON") countyde = atoi(this->rlex[this->index_r-1].name.c_str());

			if (this->tokens[this->index] == "RBRACK")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else{
			this->error(this->rlex[this->index_r].line, "m");
		}
			if (this->tokens[this->index] == "ASSIGN")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else
				return false;
			if (this->tokens[this->index] == "LBRACE")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else
				return false;
			if (this->tokens[this->index] == "LBRACE")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else
				return false;
			if (!parse_const(s))
				return false;
			county++;

			while (this->tokens[this->index] == "COMMA")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
				if (!parse_const(s))
					return false;
				county++;
			}
			if (this->tokens[this->index] == "RBRACE")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else
				return false;
			if (countyde != county) this->error(this->rlex[this->index_r].line, "n");
			countx++;
			county = 0;

			while (this->tokens[this->index] == "COMMA")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
				if (this->tokens[this->index] == "LBRACE")
				{
					cout << this->tokens[this->index] << endl;
					this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
					this->index_r++;
					this->index++;
				}
				else
					return false;
				if (!parse_const(s))
					return false;
				county++;
				while (this->tokens[this->index] == "COMMA")
				{
					cout << this->tokens[this->index] << endl;
					this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
					this->index_r++;
					this->index++;
					if (!parse_const(s))
						return false;
					county++;
				}
				if (this->tokens[this->index] == "RBRACE")
				{
					cout << this->tokens[this->index] << endl;
					this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
					this->index_r++;
					this->index++;
				}
				else
					return false;
				if (countyde != county) this->error(this->rlex[this->index_r].line, "n");
				countx++;
				county = 0;
			}
			if (this->tokens[this->index] == "RBRACE")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else
				return false;
		}
		
		if (countxde != countx) this->error(this->rlex[this->index_r].line, "n");
	}
	else
		return false;
	return true;
}

bool Parse::parse_classid()
{
	if (this->tokens[this->index] == "INTTK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		return true;
	}
	else if (this->tokens[this->index] == "CHARTK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		return true;
	}
	return false;
}

bool Parse::parse_funcdefre()
{
	string idstr;
	this->isReDe = true;
	this->isReAc = false;
	this->isFuncHaveRe = false;
	if (this->tokens[this->index+1] == "IDENFR"){
		idstr = this->rlex[this->index_r+1].name;
	}
	if (!this->parse_stahead())
		return false;

	if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	
	// namespace 增加子树
	this->names->son = new Namespace();
	this->names->son->father = this->names;
	this->names = this->names->son;

	if (!this->parse_paratable(idstr))
		return false;

	if (this->tokens[this->index] == "RPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else{
		this->error(this->rlex[this->index_r].line, "l");
	}

	if (this->tokens[this->index] == "LBRACE")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	if (!this->parse_compsta(true))
		return false;

	if (!this->isFuncHaveRe) if (this->isReDe&&!this->isReAc) this->error(this->rlex[this->index_r].line, "h");
	
	if (this->tokens[this->index] == "RBRACE")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	// namespace 返回父亲节点
	this->names = this->names->father;

	cout << "<有返回值函数定义>" << endl;
	this->r.push_back("<有返回值函数定义>");
	return true;
}

bool Parse::parse_funcdefwore()
{
	this->isReDe = false;
	this->isReAc = false;
	this->functypede = "VOIDTK";
	string idstr;
	if (this->tokens[this->index] == "VOIDTK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	if (this->tokens[this->index] == "IDENFR"){
		
		this->isfuncre[this->rlex[this->index_r].name] = false;
		//增加命名表元素
		string t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (this->names->isHave(t)) this->error(this->rlex[this->index_r].line, "b");
		this->names->ns.push_back(t);
		this->names->nstype.push_back("VOIDTK");
		this->names->nsisconst.push_back(false);
		idstr = this->rlex[this->index_r].name;
	}
	if (!this->parse_id())
		return false;

	// namespace 增加子树
	this->names->son = new Namespace();
	this->names->son->father = this->names;
	this->names = this->names->son;

	if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	if (!this->parse_paratable(idstr))
		return false;

	if (this->tokens[this->index] == "RPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else{
		this->error(this->rlex[this->index_r].line, "l");
	}

	if (this->tokens[this->index] == "LBRACE")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	if (!this->parse_compsta(false))
		return false;
	if (this->tokens[this->index] == "RBRACE")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	// namespace 返回父亲节点
	this->names = this->names->father;

	cout << "<无返回值函数定义>" << endl;
	this->r.push_back("<无返回值函数定义>");
	return true;
}

bool Parse::parse_compsta(bool isRe)
{ // 中括号？？

	if (this->tokens[this->index] == "CONSTTK")
	{
		if (!this->parse_consta())
			return false;
	}
	if ((this->tokens[this->index] == "INTTK") || (this->tokens[this->index] == "CHARTK"))
	{
		if (!this->parse_varsta())
			return false;
	}
	if (!this->parse_statecol(isRe))
		return false;
	cout << "<复合语句>" << endl;
	this->r.push_back("<复合语句>");
	return true;
}

bool Parse::parse_paratable(string s)
{

	int count = 0;
	this->functype[s] = vector<string>();
	if (this->tokens[this->index] == "INTTK" || this->tokens[this->index] == "CHARTK")
	{
		if (!this->parse_classid())
			return false;
		
		// 增加namespace 元素
		if (this->tokens[this->index] != "IDENFR") return false;
		string t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		this->names->ns.push_back(t);
		this->names->nstype.push_back(this->tokens[this->index-1]);
		this->names->nsisconst.push_back(false);
		this->functype[s].push_back(this->tokens[this->index-1]);

		if (!this->parse_id())
			return false;
		count++;
		while (this->tokens[this->index] == "COMMA")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
			if (!this->parse_classid())
				return false;

			// 增加namespace 元素
			if (this->tokens[this->index] != "IDENFR") return false;
			string t = this->rlex[this->index_r].name;
			transform(t.begin(), t.end(), t.begin(), ::tolower);
			this->names->ns.push_back(t);
			this->names->nstype.push_back(this->tokens[this->index-1]);
			this->names->nsisconst.push_back(false);
			this->functype[s].push_back(this->tokens[this->index-1]);

			if (!this->parse_id())
				return false;
			count++;
		}

		this->funcnum[s] = count;
		cout << "<参数表>" << endl;
		this->r.push_back("<参数表>");
		return true;
	}
	else
	{
		this->funcnum[s] = count;
		cout << "<参数表>" << endl;
		this->r.push_back("<参数表>");
		return true;
	}
}

bool Parse::parse_mainfunc()
{
	if (this->tokens[this->index] == "VOIDTK")
	{
		this->isReDe = false;
		this->isReAc = false;
		this->functypede = "VOIDTK";
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	if (this->tokens[this->index] == "MAINTK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	if (this->tokens[this->index] == "RPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else{
		this->error(this->rlex[this->index_r].line, "l");
	}

	if (this->tokens[this->index] == "LBRACE")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	// namespace 增加子树
	this->names->son = new Namespace();
	this->names->son->father = this->names;
	this->names = this->names->son;

	if (!this->parse_compsta(false))
		return false;
	if (this->tokens[this->index] == "RBRACE")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	// namespace 返回父亲节点
	this->names = this->names->father;
	
	cout << "<主函数>" << endl;
	this->r.push_back("<主函数>");
	return true;
}

bool Parse::parse_express(string s)
{
	this->expCount++;
	string o, a1, a2, r;
	o = "PLUS ";
	if (this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU")
	{
		o = this->tokens[this->index]+" ";
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	if (!this->parse_item(s))
		return false;
	
	a1 = "__temp"+to_string(--this->tempCount)+" ";
	this->tempCount++;
	r = "__temp"+to_string(this->tempCount++);
	a2 = "zero ";
	this->ir.datas.push_back(":= 0 "+r);
	this->ir.text.push_back(o+a2+a1+r);
	a1 = r+" ";
	o = "";
	a2 = "";
	if (this->tokens[this->index] != "PLUS" && this->tokens[this->index] != "MINU") {
		o = ":= ";
		r = "__temp"+to_string(this->tempCount++);
		string ot = ":= ", a1t = "0 ", a2t = "";
		this->ir.datas.push_back(ot+a1t+a2t+r);
		cout << ot+a1t+a2t+r << endl;
		this->ir.text.push_back(o+a1+a2+r);
	}

	while (this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU")
	{

		o = this->tokens[this->index]+" ";

		if (this->functypede=="CHARTK") this->functypeac = "INTTK";
		if (!this->parse_add())
			return false;
		if (!this->parse_item(s))
			return false;
		
		a2 = "__temp"+to_string(--this->tempCount)+" ";
		this->tempCount++;

		r = "__temp"+to_string(this->tempCount++);
		string ot = ":= ", a1t = "0 ", a2t = "";
		this->ir.datas.push_back(ot+a1t+a2t+r);
		cout << ot+a1t+a2t+r << endl;
		this->ir.text.push_back(o+a1+a2+r);
		cout << o+a1+a2+r << endl;
		a1 = r+" ";
	}

	// r = "__temp"+to_string(this->tempCount++);
	// string ot = ":= ", a1t = "0 ", a2t = "";
	// this->ir.datas.push_back(ot+a1t+a2t+r);
	// cout << ot+a1t+a2t+r << endl;
	// this->ir.text.push_back(o+a1+a2+r);
	// cout << o+a1+a2+r << endl;

	cout << "<表达式>" << endl;
	this->r.push_back("<表达式>");
	return true;
}

bool Parse::parse_item(string s)
{
	string o, a1, a2, r;
	if (!parse_factor(s))
		return false;

	a1 = this->id_now+" ";
	if (this->tokens[this->index] != "MULT" && this->tokens[this->index] != "DIV") {
		o = ":= ";
		r = "__temp"+to_string(this->tempCount++);

		string ot = ":= ", a1t = "0 ", a2t = "";
		this->ir.datas.push_back(ot+a1t+a2t+r);
		cout << ot+a1t+a2t+r << endl;
		this->ir.text.push_back(o+a1+a2+r);
		cout << o+a1+a2+r << endl;
	}
	while (this->tokens[this->index] == "MULT" || this->tokens[this->index] == "DIV")
	{
		o = this->tokens[this->index]+" ";
		if (!parse_mul())
			return false;
		if (!parse_factor(s))
			return false;
		a2 = this->id_now+" ";
		r = "__temp"+to_string(this->tempCount++);

		string ot = ":= ", a1t = "0 ", a2t = "";
		this->ir.datas.push_back(ot+a1t+a2t+r);
		cout << ot+a1t+a2t+r << endl;
		this->ir.text.push_back(o+a1+a2+r);
		cout << o+a1+a2+r << endl;

		a1 = r+" ";
	}
	// r = "__temp"+to_string(this->tempCount++);

	// string ot = ":= ", a1t = "0 ", a2t = "";
	// this->ir.datas.push_back(ot+a1t+a2t+r);
	// cout << ot+a1t+a2t+r << endl;
	// this->ir.text.push_back(o+a1+a2+r);
	// cout << o+a1+a2+r << endl;
	cout << "<项>" << endl;
	this->r.push_back("<项>");
	return true;
}

bool Parse::parse_factor(string s)
{

	if (this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] != "LPARENT")
	{
		string t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (this->tokens[this->index] != "IDENFR") return false;
		if (!this->names->findName(t)){
			this->error(this->rlex[this->index_r].line, "c");
		}

		// 判断是不是想要的标识符类型
		
		t = rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (!this->isgetretype){this->functypeac = this->names->findType(t);this->isgetretype = true;}
		if (s!=""&&this->names->findType(t)!=s.substr(1,s.size()-1)) this->error(this->rlex[this->index_r].line, s.substr(0,1));
		this->caseType = this->names->findType(this->rlex[this->index_r].name);

		this->id_now = t;

		if (!parse_id())
			return false;
		if (!parse_subfactor())
			return false;
		cout << "<因子>" << endl;
		this->r.push_back("<因子>");
		return true;
	}
	else if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (!parse_express(s))
			return false;

		this->id_now = "__temp"+to_string(--this->tempCount);
		this->tempCount++;

		if (this->tokens[this->index] == "RPARENT")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
		this->error(this->rlex[this->index_r].line, "l");
	}
		cout << "<因子>" << endl;
		this->r.push_back("<因子>");
		return true;
	}
	else if (this->tokens[this->index] == "INTCON" || this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU")
	{
		string o, a1, r;
		o = ":= ";
		if (!this->isgetretype){this->functypeac = "INTTK";this->isgetretype = true;}
		if (s!=""&&s.substr(1,s.size()-1)!="INTTK") this->error(this->rlex[this->index_r].line, s.substr(0,1));
		if (!this->parse_int())
			return false;

		a1 = this->id_now+" ";
		r = "__temp"+to_string(this->tempCount++);
		this->id_now = r;
		this->ir.datas.push_back(o+a1+r);
		cout << o+a1+r << endl;
		this->caseType = "INTTK";
		cout << "<因子>" << endl;
		this->r.push_back("<因子>");
		return true;
	}
	else if (this->tokens[this->index] == "CHARCON")
	{
		if (!this->isgetretype){this->functypeac = "CHARTK";this->isgetretype = true;}
		if (s!=""&&s.substr(1,s.size()-1)!="CHARTK") this->error(this->rlex[this->index_r].line, s.substr(0,1));
		if (!this->parse_char())
			return false;
		this->caseType = "CHARTK";
		cout << "<因子>" << endl;
		this->r.push_back("<因子>");
		return true;
	}
	else if (this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "LPARENT")
	{
		// 判断是不是想要的标识符类型
		string t = rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (!this->isgetretype){this->functypeac = this->names->findType(t);this->isgetretype = true;}
		if (s!=""&&this->names->findType(t)!=s.substr(1,s.size()-1)) this->error(this->rlex[this->index_r].line, s.substr(0,1));
		this->caseType = this->names->findType(this->rlex[this->index_r].name);
		if (!this->parse_funccallstare(""))
			return false;
		cout << "<因子>" << endl;
		this->r.push_back("<因子>");
		return true;
	}
	else
		return false;
}

bool Parse::parse_subfactor()
{

	if (this->tokens[this->index] == "LBRACK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (!parse_express("iINTTK"))
			return false;
		if (this->tokens[this->index] == "RBRACK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r].line, "m");
		}
		if (this->tokens[this->index] == "LBRACK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
			if (!parse_express("iINTTK"))
				return false;
			if (this->tokens[this->index] == "RBRACK")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else{
			this->error(this->rlex[this->index_r].line, "m");
		}
		}
		return true;
	}
	else
		return true;
}

bool Parse::parse_statement(bool isRe)
{

	if (this->tokens[this->index] == "WHILETK" || this->tokens[this->index] == "FORTK")
	{
		if (!parse_circusta(isRe))
			return false;
		cout << "<语句>" << endl;
		this->r.push_back("<语句>");
		return true;
	}
	else if (this->tokens[this->index] == "IFTK")
	{
		if (!parse_condista(isRe))
			return false;
		cout << "<语句>" << endl;
		this->r.push_back("<语句>");
		return true;
	}
	else if (this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "LPARENT")
	{
		if (this->names->findName(this->rlex[this->index_r].name)&&this->isfuncre[this->rlex[this->index_r].name]){
			if (!parse_funccallstare(""))
				return false;
			if (this->tokens[this->index] == "SEMICN")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else{
				this->error(this->rlex[this->index_r-1].line, "k");
			}
			cout << "<语句>" << endl;
			this->r.push_back("<语句>");
			return true;
		}
		else{
			if (!parse_funccallstawore())
				return false;
			if (this->tokens[this->index] == "SEMICN")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else{
				this->error(this->rlex[this->index_r-1].line, "k");
			}
			cout << "<语句>" << endl;
			this->r.push_back("<语句>");
			return true;
		}
	}
	else if ((this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "ASSIGN") || (this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "LBRACK"))
	{
		if (!parse_assign())
			return false;
		if (this->tokens[this->index] == "SEMICN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r-1].line, "k");
		}
		cout << "<语句>" << endl;
		this->r.push_back("<语句>");
		return true;
	}
	else if (this->tokens[this->index] == "SCANFTK")
	{
		if (!this->parse_readsta())
			return false;
		if (this->tokens[this->index] == "SEMICN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r-1].line, "k");
		}
		cout << "<语句>" << endl;
		this->r.push_back("<语句>");
		return true;
	}
	else if (this->tokens[this->index] == "PRINTFTK")
	{

		if (!this->parse_writesta())
			return false;
		if (this->tokens[this->index] == "SEMICN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r-1].line, "k");
		}
		cout << "<语句>" << endl;
		this->r.push_back("<语句>");
		return true;
	}
	else if (this->tokens[this->index] == "SWITCHTK")
	{
		if (!this->parse_casesta(isRe))
			return false;
		cout << "<语句>" << endl;
		this->r.push_back("<语句>");
		return true;
	}
	else if (this->tokens[this->index] == "SEMICN")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		cout << "<语句>" << endl;
		this->r.push_back("<语句>");
		return true;
	}
	else if (this->tokens[this->index] == "RETURNTK")
	{
		if (!this->parse_returnsta(isRe))
			return false;
		if (this->tokens[this->index] == "SEMICN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r-1].line, "k");
		}
		this->isFuncHaveRe = true;
		cout << "<语句>" << endl;
		this->r.push_back("<语句>");
		return true;
	}
	else if (this->tokens[this->index] == "LBRACE")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (!this->parse_statecol(isRe))
			return false;
		if (this->tokens[this->index] == "RBRACE")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;
		cout << "<语句>" << endl;
		this->r.push_back("<语句>");
		return true;
	}
	else
		return false;
}

bool Parse::parse_assign()
{
	//四元式初始化
	this->op = ":=";
	this->arg2 = "";
	if (this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "ASSIGN")
	{
		// 引用未定义标识符
		string t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (this->tokens[this->index] != "IDENFR") return false;
		if (!this->names->findName(t)){
			this->error(this->rlex[this->index_r].line, "c");
		}

		if (this->names->isConst(t)) this->error(this->rlex[this->index_r].line, "j");

		if (!this->parse_id())
			return false;

		this->result = t;

		if (this->tokens[this->index] == "ASSIGN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;
		if (!this->parse_express(""))
			return false;
		
		string a1 = "__temp"+to_string(--this->tempCount)+" ";
		this->tempCount++;

		this->ir.text.push_back(":= "+a1+t);
		cout << "<赋值语句>" << endl;
		this->r.push_back("<赋值语句>");
		return true;
	}
	else if (this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "LBRACK")
	{
		// 引用未定义标识符
		string t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (this->tokens[this->index] != "IDENFR") return false;
		if (!this->names->findName(t)){
			this->error(this->rlex[this->index_r].line, "c");
		}

		if (!this->parse_id())
			return false;
		if (this->tokens[this->index] == "LBRACK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;
		if (!this->parse_express("iINTTK"))
			return false;
		if (this->tokens[this->index] == "RBRACK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r].line, "m");
		}
		if (this->tokens[this->index] == "LBRACK")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
			if (!this->parse_express("iINTTK"))
				return false;
			if (this->tokens[this->index] == "RBRACK")
			{
				cout << this->tokens[this->index] << endl;
				this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
				this->index_r++;
				this->index++;
			}
			else{
			this->error(this->rlex[this->index_r].line, "m");
		}
		}
		if (this->tokens[this->index] == "ASSIGN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;
		if (!this->parse_express(""))
			return false;
		cout << "<赋值语句>" << endl;
		this->r.push_back("<赋值语句>");
		return true;
	}
	else
		return false;
}

bool Parse::parse_condista(bool isRe)
{
	if (this->tokens[this->index] == "IFTK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	if (!this->parse_condi())
		return false;
	if (this->tokens[this->index] == "RPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else{
		this->error(this->rlex[this->index_r].line, "l");
	}

	if (!this->parse_statement(isRe))
		return false;
	if (this->tokens[this->index] == "ELSETK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (!this->parse_statement(isRe))
			return false;
	}
	cout << "<条件语句>" << endl;
	this->r.push_back("<条件语句>");
	return true;
}

bool Parse::parse_condi()
{
	if (!this->parse_express("fINTTK"))
		return false;
	if (!this->parse_rel())
		return false;
	if (!this->parse_express("fINTTK"))
		return false;
	cout << "<条件>" << endl;
	this->r.push_back("<条件>");
	return true;
}

bool Parse::parse_circusta(bool isRe)
{
	if (this->tokens[this->index] == "WHILETK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (this->tokens[this->index] == "LPARENT")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;
		if (!this->parse_condi())
			return false;
		if (this->tokens[this->index] == "RPARENT")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
		this->error(this->rlex[this->index_r].line, "l");
	}

		// namespace 增加子树
		this->names->son = new Namespace();
		this->names->son->father = this->names;
		this->names = this->names->son;

		if (!this->parse_statement(isRe))
			return false;

		// namespace 返回父亲节点
		this->names = this->names->father;

		cout << "<循环语句>" << endl;
		this->r.push_back("<循环语句>");
		return true;
	}
	else if (this->tokens[this->index] == "FORTK")
	{
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
		if (this->tokens[this->index] == "LPARENT")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;

		// 引用未定义标识符
		string t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (this->tokens[this->index] != "IDENFR") return false;
		if (!this->names->findName(t)){
			this->error(this->rlex[this->index_r].line, "c");
		}

		if (!this->parse_id())
			return false;
		if (this->tokens[this->index] == "ASSIGN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;
		if (!this->parse_express(""))
			return false;
		if (this->tokens[this->index] == "SEMICN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r-1].line, "k");
		}

		if (!this->parse_condi())
			return false;
		if (this->tokens[this->index] == "SEMICN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
			this->error(this->rlex[this->index_r-1].line, "k");
		}

		// 引用未定义标识符
		t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (this->tokens[this->index] != "IDENFR") return false;
		if (!this->names->findName(t)){
			this->error(this->rlex[this->index_r].line, "c");
		}

		if (!this->parse_id())
			return false;
		if (this->tokens[this->index] == "ASSIGN")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else
			return false;

		// 引用未定义标识符
		t = this->rlex[this->index_r].name;
		transform(t.begin(), t.end(), t.begin(), ::tolower);
		if (this->tokens[this->index] != "IDENFR") return false;
		if (!this->names->findName(t)){
			this->error(this->rlex[this->index_r].line, "c");
		}

		if (!this->parse_id())
			return false;
		if (this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		} // С����
		if (!this->parse_stepsize())
			return false;
		if (this->tokens[this->index] == "RPARENT")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
		this->error(this->rlex[this->index_r].line, "l");
	}

		// namespace 增加子树
		this->names->son = new Namespace();
		this->names->son->father = this->names;
		this->names = this->names->son;

		if (!this->parse_statement(false))
			return false;

		// namespace 返回父亲节点
		this->names = this->names->father;

		cout << "<循环语句>" << endl;
		this->r.push_back("<循环语句>");
		return true;
	}
	else
		return false;
}

bool Parse::parse_stepsize()
{
	if (!this->parse_uint())
		return false;
	cout << "<步长>" << endl;
	this->r.push_back("<步长>");
	return true;
}

bool Parse::parse_casesta(bool isRe)
{
	if (this->tokens[this->index] == "SWITCHTK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	if (!this->parse_express(""))
		return false;

	if (this->tokens[this->index] == "RPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else{
		this->error(this->rlex[this->index_r].line, "l");
	}

	if (this->tokens[this->index] == "LBRACE")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	// namespace 增加子树
	this->names->son = new Namespace();
	this->names->son->father = this->names;
	this->names = this->names->son;

	if (!this->parse_casetable(isRe, this->caseType))
		return false;
	this->haveDefault = false;
	if (this->tokens[this->index] == "DEFAULTTK"&&!this->parse_default())
		return false;
	if (!this->haveDefault) this->error(this->rlex[this->index_r].line, "p");

	if (this->tokens[this->index] == "RBRACE")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;
	
	// namespace 返回父亲节点
	this->names = this->names->father;

	cout << "<情况语句>" << endl;
	this->r.push_back("<情况语句>");
	return true;
}

bool Parse::parse_casetable(bool isRe, string s)
{
	if (!this->parse_casesubsta(isRe, s))
		return false;
	while (this->tokens[this->index] == "CASETK")
	{
		if (!this->parse_casesubsta(isRe, s))
			return false;
	}
	cout << "<情况表>" << endl;
	this->r.push_back("<情况表>");
	return true;
}

bool Parse::parse_casesubsta(bool isRe, string s)
{
	if (this->tokens[this->index] == "CASETK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	if (!this->parse_const(s))
		return false;

	if (this->tokens[this->index] == "COLON")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	// namespace 增加子树
	this->names->son = new Namespace();
	this->names->son->father = this->names;
	this->names = this->names->son;

	if (!this->parse_statement(isRe))
		return false;

	// namespace 返回父亲节点
	this->names = this->names->father;

	cout << "<情况子语句>" << endl;
	this->r.push_back("<情况子语句>");
	return true;
}

bool Parse::parse_default()
{
	if (this->tokens[this->index] == "DEFAULTTK")
	{
		this->haveDefault = true;
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	if (this->tokens[this->index] == "COLON")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	// namespace 增加子树
	this->names->son = new Namespace();
	this->names->son->father = this->names;
	this->names = this->names->son;

	if (!this->parse_statement(false))
		return false;

	// namespace 返回父亲节点
	this->names = this->names->father;

	cout << "<缺省>" << endl;
	this->r.push_back("<缺省>");
	return true;
}

bool Parse::parse_funccallstare(string s)
{
	// 判断是不是想要的标识符类型
	if (s!=""&&this->rlex[this->index_r].cname!=s.substr(1,s.size()-1)) this->error(this->rlex[this->index_r].line, s.substr(0,1));

	string t = this->rlex[this->index_r].name;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	if (this->tokens[this->index] != "IDENFR") return false;
	if (!this->names->findName(t)){
		this->error(this->rlex[this->index_r].line, "c");
	}
	string idstr = this->rlex[this->index_r].name;

	if (!this->parse_id())
		return false;
	if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	int valre = this->parse_valparatable(idstr);
	if (valre==-1) return false;
	if (valre!=this->funcnum[idstr])
		this->error(this->rlex[this->index_r].line, "d");

	if (this->tokens[this->index] == "RPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else{
		this->error(this->rlex[this->index_r].line, "l");
	}

	cout << "<有返回值函数调用语句>" << endl;
	this->r.push_back("<有返回值函数调用语句>");
	return true;
}

bool Parse::parse_funccallstawore()
{
	string t = this->rlex[this->index_r].name;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	if (this->tokens[this->index] != "IDENFR") return false;
	if (!this->names->findName(t)){
		this->error(this->rlex[this->index_r].line, "c");
	}
	string idstr = this->rlex[this->index_r].name;

	if (!this->parse_id())
		return false;
	if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	int valre = this->parse_valparatable(idstr);
	if (valre==-1) return false;
	if (valre!=this->funcnum[idstr])
		this->error(this->rlex[this->index_r].line, "d");

	if (this->tokens[this->index] == "RPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else{
		this->error(this->rlex[this->index_r].line, "l");
	}

	cout << "<无返回值函数调用语句>" << endl;
	this->r.push_back("<无返回值函数调用语句>");
	return true;
}

int Parse::parse_valparatable(string s)
{
	int count = 0;
	vector<string> types = this->functype[s];
	if (this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU" ||
		(this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] != "LPARENT") ||
		this->tokens[this->index] == "LPARENT" || (this->tokens[this->index] == "INTCON" || this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU") ||
		(this->tokens[this->index] == "CHARCON") || (this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "LPARENT"))
	{
		if (types.size()==0){
			if (!this->parse_express(""))
				return -1;
		}
		else{
			if (!this->parse_express("e"+types[count]))
				return -1;
		}
		count++;
		while (this->tokens[this->index] == "COMMA")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
			if (types.size()<=count){
				if (!this->parse_express(""))
					return -1;
			}
			else{
				if (!this->parse_express("e"+types[count]))
					return -1;
			}
			count++;
		}
		cout << "<值参数表>" << endl;
		this->r.push_back("<值参数表>");
		return count;
	}
	else
	{
		cout << "<值参数表>" << endl;
		this->r.push_back("<值参数表>");
		return count;
	}
}

bool Parse::parse_statecol(bool isRe)
{
	while (this->tokens[this->index] == "WHILETK" || this->tokens[this->index] == "FORTK" ||
		   this->tokens[this->index] == "IFTK" ||
		   (this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "LPARENT") ||
		   ((this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "ASSIGN") || (this->tokens[this->index] == "IDENFR" && this->tokens[this->index + 1] == "LBRACK")) ||
		   (this->tokens[this->index] == "SCANFTK") || (this->tokens[this->index] == "SWITCHTK") || (this->tokens[this->index] == "SEMICN") ||
		   (this->tokens[this->index] == "RETURNTK") || (this->tokens[this->index] == "PRINTFTK") || (this->tokens[this->index] == "LBRACE"))
	{
		// // namespace 增加子树
		// this->names->son = new Namespace();
		// this->names->son->father = this->names;
		// this->names = this->names->son;

		if (!this->parse_statement(isRe))
			return false;

		// // namespace 返回父亲节点
		// this->names = this->names->father;
	}
	cout << "<语句列>" << endl;
	this->r.push_back("<语句列>");
	return true;
}

bool Parse::parse_readsta()
{
	string o, a1;
	if (this->tokens[this->index] == "SCANFTK")
	{
		o = this->tokens[this->index]+" ";
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	// 引用未定义标识符
	string t = this->rlex[this->index_r].name;
	transform(t.begin(), t.end(), t.begin(), ::tolower);
	if (this->tokens[this->index] != "IDENFR") return false;
	if (!this->names->findName(t)){
		this->error(this->rlex[this->index_r].line, "c");
	}
	if (this->names->isConst(t)) this->error(this->rlex[this->index_r].line, "j");

	if (!this->parse_id())
		return false;
	
	a1 = this->id_now;

	if (this->tokens[this->index] == "RPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else{
		this->error(this->rlex[this->index_r].line, "l");
	}
	this->ir.text.push_back(o+a1);
	cout << o+a1 << endl;
	cout << "<读语句>" << endl;
	this->r.push_back("<读语句>");
	return true;
}

bool Parse::parse_writesta()
{
	string o, a1;
	if (this->tokens[this->index] == "PRINTFTK")
	{
		o = this->tokens[this->index]+" ";
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	if (this->tokens[this->index] == "LPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	if (this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU" ||
		(this->tokens[this->index] == "IDENFR") ||
		this->tokens[this->index] == "LPARENT" || (this->tokens[this->index] == "INTCON" || this->tokens[this->index] == "PLUS" || this->tokens[this->index] == "MINU") ||
		(this->tokens[this->index] == "CHARCON") ||
		(this->tokens[this->index] == "IDENFR" && this->tokens[this->index] == "LPARENT"))
	{
		if (!this->parse_express(""))
			return false;
		a1 = "__temp"+to_string(--this->tempCount)+" ";
		this->tempCount++;

		this->ir.text.push_back(o+a1+this->functypeac);
		cout << o+a1+this->functypeac << endl;
	}
	else
	{
		if (!this->parse_string())
			return false;
		a1 = this->id_now+" STRCON";
		this->ir.text.push_back(o+a1);
		cout << o+a1 << endl;

		if (this->tokens[this->index] == "COMMA")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;

			if (!this->parse_express(""))
				return false;
			a1 = "__temp"+to_string(--this->tempCount)+" ";
			this->tempCount++;

			this->ir.text.push_back(o+a1+this->functypeac);
			cout << o+a1+this->functypeac << endl;
		}
	}

	if (this->tokens[this->index] == "RPARENT")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else{
		this->error(this->rlex[this->index_r].line, "l");
	}

	a1 = "newline STRCON";
	this->ir.text.push_back(o+a1);
	cout << o+a1 << endl;

	cout << "<写语句>" << endl;
	this->r.push_back("<写语句>");
	return true;
}

bool Parse::parse_returnsta(bool isRe)
{
	if (this->tokens[this->index] == "RETURNTK")
	{
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;
	}
	else
		return false;

	if (this->tokens[this->index] != "LPARENT"){
		this->isReAc = false;
	}
	
	if (this->tokens[this->index] == "LPARENT")
	{
		if (this->tokens[this->index+1] == "RPARENT") this->isReAc = !this->isReDe;
		else this->isReAc = true;
		cout << this->tokens[this->index] << endl;
		this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
		this->index_r++;
		this->index++;

		this->isgetretype = false;
		if (this->tokens[this->index] != "RPARENT"&&!this->parse_express(""))
			return false;

		if (this->tokens[this->index] == "RPARENT")
		{
			cout << this->tokens[this->index] << endl;
			this->r.push_back(this->rlex[this->index_r].cname + " " + this->rlex[this->index_r].name);
			this->index_r++;
			this->index++;
		}
		else{
		this->error(this->rlex[this->index_r].line, "l");
	}
	}

	if (this->isReDe&&!this->isReAc) this->error(this->rlex[this->index_r-1].line, "h");
	if (!this->isReDe&&this->isReAc) this->error(this->rlex[this->index_r-1].line, "g");
	if (this->functypede!="VOIDTK"&&this->functypede!=this->functypeac) this->error(this->rlex[this->index_r-1].line, "h");

	cout << "<返回语句>" << endl;
	this->r.push_back("<返回语句>");
	return true;
}

void Parse::error(int line, string e){
	this->errors.push_back({line, e});
}

#endif
