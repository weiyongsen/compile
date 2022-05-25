#pragma once
#include<iostream>
#include<string.h>
#include<map>
#include<vector>
using namespace std;
#define BUFFER_SIZE 2048
class Lexical
{
private:
	FILE *fin;										// 输入文件指针
	FILE *fout;										// 输出文件指针
	int flag;										// 为1表示左缓冲区为空，为2表示右缓冲区为空
	int stop;										// 为1表示停止词法分析
	map<string, string> category_code;				// 保存单词及其类别码
	int state = 0;									// 当前状态
	char cur_char;									// 当前读入的字符
	char token[1025];								// 当前正在识别的单词字符串
	char *lexemebegin;								// 当前单词在输入缓冲区中的开始位置
	char *forward;									// 向前指针
	char buffer[BUFFER_SIZE + 2];					// 输入缓冲区
	vector<pair<string, string>> lexical_results;   // 保存词法分析的结果

public:
	Lexical(FILE *fin, FILE *fout);					// 构造函数
	void load_buffer();								// 加载输入缓冲区
	void get_next_char();							// 根据向前指针读取缓冲区下一个字符，并保存至cur_char
	bool get_nbc();									// 检查当前字符是否为空格
	void update_begin_p();							// 更新开始指针
	void cat();										// 拼接token和当前字符
	bool isletter();								// 判断当前字符是否为字母
	bool isdigit();									// 判断当前字符是否为数字
	void retract();									// 向前指针退后一个字符
	void error();									// 错误处理函数（目前仅输出错误状态）
	vector<pair<string, string>> analyse();			// 词法分析函数
	void output(char *c);							// 输出函数
};

Lexical::Lexical(FILE *fin, FILE *fout)
{
	this->fin = fin;
	this->fout = fout;
	flag = 1;
	stop = 0;
	load_buffer();
	forward = buffer;
	category_code.insert(pair<string, string>("const", "CONSTTK"));
	category_code.insert(pair<string, string>("int", "INTTK"));
	category_code.insert(pair<string, string>("char", "CHARTK"));
	category_code.insert(pair<string, string>("void", "VOIDTK"));
	category_code.insert(pair<string, string>("main", "MAINTK"));
	category_code.insert(pair<string, string>("if", "IFTK"));
	category_code.insert(pair<string, string>("else", "ELSETK"));
	category_code.insert(pair<string, string>("switch", "SWITCHTK"));
	category_code.insert(pair<string, string>("case", "CASETK"));
	category_code.insert(pair<string, string>("default", "DEFAULTTK"));
	category_code.insert(pair<string, string>("while", "WHILETK"));
	category_code.insert(pair<string, string>("for", "FORTK"));
	category_code.insert(pair<string, string>("scanf", "SCANFTK"));
	category_code.insert(pair<string, string>("printf", "PRINTFTK"));
	category_code.insert(pair<string, string>("return", "RETURNTK"));
	category_code.insert(pair<string, string>("+", "PLUS"));
	category_code.insert(pair<string, string>("-", "MINU"));
	category_code.insert(pair<string, string>("*", "MULT"));
	category_code.insert(pair<string, string>("/", "DIV"));
	category_code.insert(pair<string, string>("<", "LSS"));
	category_code.insert(pair<string, string>("<=", "LEQ"));
	category_code.insert(pair<string, string>(">", "GRE"));
	category_code.insert(pair<string, string>(">=", "GEQ"));
	category_code.insert(pair<string, string>("==", "EQL"));
	category_code.insert(pair<string, string>("!=", "NEQ"));
	category_code.insert(pair<string, string>(":", "COLON"));
	category_code.insert(pair<string, string>("=", "ASSIGN"));
	category_code.insert(pair<string, string>(";", "SEMICN"));
	category_code.insert(pair<string, string>(",", "COMMA"));
	category_code.insert(pair<string, string>("(", "LPARENT"));
	category_code.insert(pair<string, string>(")", "RPARENT"));
	category_code.insert(pair<string, string>("[", "LBRACK"));
	category_code.insert(pair<string, string>("]", "RBRACK"));
	category_code.insert(pair<string, string>("{", "LBRACE"));
	category_code.insert(pair<string, string>("}", "RBRACE"));
}

void Lexical::load_buffer()
{
	buffer[BUFFER_SIZE / 2] = EOF;
	buffer[BUFFER_SIZE + 1] = EOF;
	// 加载左缓冲区
	if (flag == 1) {
		for (int i = 0; i < BUFFER_SIZE / 2; i++)
		{
			char ch = fgetc(fin);
			buffer[i] = ch;
			if (ch == EOF)
			{
				break;
			}
		}
		flag = 2;
	}
	// 加载右缓冲区
	else if (flag == 2) {
		for (int i = 0; i < BUFFER_SIZE / 2; i++)
		{
			char ch = fgetc(fin);
			buffer[i + BUFFER_SIZE / 2 + 1] = ch;
			if (ch == EOF)
			{
				break;
			}
		}
		flag = 1;
	}
}

void Lexical::get_next_char()
{
	cur_char = *forward;
	if (cur_char == EOF)
	{
		// 当前为左缓冲区末尾
		if (forward - buffer == BUFFER_SIZE / 2)
		{
			load_buffer();
			forward += 1;
			cur_char = *forward;
			forward += 1;
			stop = 0;
		}
		// 当前为右缓冲区末尾
		else if (forward - buffer == BUFFER_SIZE + 1)
		{
			load_buffer();
			forward = buffer;
			cur_char = *forward;
			forward += 1;
			stop = 0;
		}
		// 当前为代码末尾
		else
		{
			stop = 1;
			fclose(fin);
			fclose(fout);
		}
	}
	else
		forward += 1;
}

bool Lexical::get_nbc()
{
	if (cur_char == ' ')
		return true;
	else
		return false;
}

void Lexical::update_begin_p()
{
	lexemebegin = forward - 1;
}

void Lexical::cat()
{
	int len = strlen(token);
	token[len] = cur_char;
	return;
}

bool Lexical::isletter()
{
	if ((cur_char >= 'a' && cur_char <= 'z') || (cur_char >= 'A' && cur_char <= 'Z'))
		return true;
	else
		return false;
}

bool Lexical::isdigit()
{
	if (cur_char >= '0' && cur_char <= '9')
		return true;
	else
		return false;
}

void Lexical::retract()
{
	forward -= 1;
	return;
}

void Lexical::error()
{
	cout << "state=" << state << "出错" << endl;
}

vector<pair<string,string>> Lexical::analyse()
{
	state = 0;
	do {
		switch (state) {
		case 0:
			// 重置当前token
			memset(token, 0, 1025);
			// 获取第一个不为空的字符
			get_next_char();
			while (get_nbc())
			{
				get_next_char();
			}
			update_begin_p();
			char temp_char;
			if ((cur_char >= 'a' && cur_char <= 'z') || (cur_char >= 'A' && cur_char <= 'Z') || cur_char == '_')
				temp_char = 'a';
			else if (cur_char >= '0'&& cur_char <= '9')
				temp_char = '0';
			else
				temp_char = cur_char;
			switch (temp_char) {
			case 'a':
				state = 1;
				break;
			case '\'':
				state = 2;
				break;
			case '"':
				state = 3;
				break;
			case '0':
				state = 4;
				break;
			case '<':
				state = 5;
				break;
			case '>':
				state = 6;
				break;
			case '=':
				state = 7;
				break;
			case '!':
				state = 8;
				break;
			case '+':
			case '-':
			case '*':
			case '/':
			case ';':
			case ':':
			case ',':
			case '(':
			case ')':
			case '[':
			case ']':
			case '{':
			case '}': {
				char temp[2] = { temp_char };
				output(temp);
				state = 0;
				break; }
			case '\n':
				state = 0;
				break;
			default:
				state = 9;
				break;
			}
			break;
		case 1:
			cat();
			get_next_char();
			if (isletter() || isdigit() || cur_char == '_')
				state = 1;
			else
			{
				retract();
				output(token);
				state = 0;
			}
			break;
		case 2:
			cat();
			get_next_char();
			if (isletter() || isdigit())
				state = 2;
			else if (cur_char == '\'')
			{
				// 不输出引号且不回退
				output(token + 1);
				state = 0;
			}
			break;
		case 3:
			cat();
			get_next_char();
			if (isletter() || isdigit())
				state = 3;
			else if (cur_char == '"')
			{
				// 不输出引号且不回退
				output(token + 1);
				state = 0;
			}
			break;
		case 4:
			cat();
			get_next_char();
			if (cur_char >= '0'&& cur_char <= '9')
				state = 4;
			else {
				retract();
				output(token);
				state = 0;
			}
			break;
		case 5:
			cat();
			get_next_char();
			switch (cur_char) {
			case '=':
				cat();
				output(token);
				state = 0;
				break;
			default:
				retract();
				output(token);
				state = 0;
				break;
			}
			break;
		case 6:
			cat();
			get_next_char();
			switch (cur_char) {
			case '=':
				cat();
				output(token);
				state = 0;
				break;
			default:
				retract();
				output(token);
				state = 0;
				break;
			}
			break;
		case 7:
			cat();
			get_next_char();
			switch (cur_char) {
			case '=':
				cat();
				output(token);
				state = 0;
				break;
			default:
				retract();
				output(token);
				state = 0;
				break;
			}
			break;
		case 8:
			cat();
			get_next_char();
			switch (cur_char) {
			case '=':
				cat();
				output(token);
				state = 0;
				break;
			default:
				retract();
				error();
				state = 0;
				break;
			}
			break;
		case 9:
			error();
			state = 0;
			break;
		}

	} while (!stop);
	return lexical_results;
}

void Lexical::output(char *c)
{
	map<string, string>::iterator iter;
	char temp[1025];
	strcpy(temp, c);
	// 将字母全转换为小写后，在map中匹配字符
	for (int i = 0; i < sizeof(temp); i++)
	{
		temp[i] = tolower(temp[i]);
	}
	iter = category_code.find(temp);
	switch (state) {
	case 0:
	case 5:
	case 6:
	case 7:
	case 8:
		if (iter != category_code.end())
		{
			lexical_results.push_back(pair<string, string>(iter->second.c_str(), c));
			fprintf(fout, "%s %s\n", iter->second.c_str(), c);
		}
		else
			fprintf(fout, "%s %s\n", "未匹配字符", c);
		break;
	case 1:
		if (iter != category_code.end())  // 输出关键字
		{
			lexical_results.push_back(pair<string, string>(iter->second.c_str(), c));
			fprintf(fout, "%s %s\n", iter->second.c_str(), c);
		}
		else  // 输出标识符
		{
			lexical_results.push_back(pair<string, string>("IDENFR", c));
			fprintf(fout, "%s %s\n", "IDENFR", c);
		}
		break;
	case 2:
		lexical_results.push_back(pair<string, string>("CHARCON", c));
		fprintf(fout, "%s %s\n", "CHARCON", c);  // 输出字符常量
		break;
	case 3:
		lexical_results.push_back(pair<string, string>("STRCON", c));
		fprintf(fout, "%s %s\n", "STRCON", c);  // 输出字符串常量
		break;
	case 4:
		lexical_results.push_back(pair<string, string>("INTCON", c));
		fprintf(fout, "%s %s\n", "INTCON", c);  // 输出整型常量
		break;
	}
}

