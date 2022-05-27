#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "table.h"

#define MAX_LINE 1024
using namespace std;
vector<string> wordname;
vector<string> category;
vector<int> row_line;

void print_lex_ans() {
	ofstream outfile;
	outfile.open("output_lex.txt");
	for (int i = 0; i < wordname.size(); i++) {
		outfile << category[i] << " " << wordname[i] << " " << row_line[i] << endl;
	}
	outfile.close();
}

void lex_analyse(vector<string> &tokens, vector<string> &name, vector<int> &rows) {
	cout<< "开始词法分析:" << endl;
	vector<int> row_char;	// 记录每个字符的行数
	char c = '\0';
	string buffer;
	// 读入文件
	ifstream infile;
	infile.open("testfile.txt");

	// 记录当前行数
	int row = 1;

	// 写入buffer
	infile >> noskipws;
	while (infile.peek() != EOF) {
		infile >> c;
		buffer += c;
		row_char.emplace_back(row);
		if (c=='\n')
			++row;
	}
	infile.close();

	string word = "";	// 正在识别的单词，c是字符
	int forward = 0; 	// 向前指针
	int buffer_size = buffer.size();	// 总长度

	// 开始逐字符判断
	while (forward < buffer_size) {
		word += buffer[forward];  //更新token

		// 特殊字符  +=*/:=;,()[]{}
		if (signal_char.find(word) != signal_char.npos) {
			wordname.emplace_back(word);
			category.emplace_back(table[word]);
			row_line.emplace_back(row_char[forward]);
		}

		// 比较运算符    先判断 <,>,=,! 再判断 <=,>=,==,!=
		if (signal_comparison.find(word) != signal_comparison.npos) {
			word += buffer[++forward];
			if (find(double_cocmparison.begin(), double_cocmparison.end(), word) != double_cocmparison.end()) {
				wordname.emplace_back(word);
				category.emplace_back(table[word]);
				row_line.emplace_back(row_char[forward]);
			}
			else {
				word.erase(1, 1);	// 删除第二个字符
				wordname.emplace_back(word);
				category.emplace_back(table[word]);
				
				--forward;
				row_line.emplace_back(row_char[forward]);
			}
		}

		// 判断整形常量
		if (isdigit(buffer[forward])) {
			while (isdigit(buffer[++forward])) {
				word += buffer[forward];
			}
			--forward;
			wordname.emplace_back(word);
			category.emplace_back(table["整形常量"]);
			row_line.emplace_back(row_char[forward]);
		}

		// 判断字符常量
		if (word == "\'") {
			// cout << "开始字符判断..." ;
			while (buffer[++forward] != '\'') {
				word += buffer[forward];
			}
			word.erase(0, 1);  // 去掉开头的  '
			// cout << "当前token: " << word << "类型: " << table["字符常量"] <<  endl;
			wordname.emplace_back(word);
			category.emplace_back(table["字符常量"]);
			row_line.emplace_back(row_char[forward]);
		}

		// 判断字符串
		if (word == "\"") {
			// cout << "开始字符串判断...." ;
			while (buffer[++forward] != '\"') {
				word += buffer[forward];
			}
			word.erase(0, 1);  // 去掉开头的  "
			// cout << "当前token: " << word << ".... "<< table["字符串"];
			wordname.emplace_back(word);
			category.emplace_back(table["字符串"]);
			row_line.emplace_back(row_char[forward]);
			// cout << "已添加进容器" << endl;
		}

		// 判断关键字 或 标识符
		if (isalpha(buffer[forward]) || buffer[forward] == '_') {
			while (isalnum(buffer[++forward]) || buffer[forward] == '_') {
				word += buffer[forward];
			}
			--forward;
			string temp = word;	// 保留token原有格式，向name中填写
			transform(word.begin(), word.end(), word.begin(), ::tolower);	// token变为小写,关键字识别用小写
			if (find(key_word.begin(), key_word.end(), word) != key_word.end()) {
				wordname.emplace_back(temp);
				category.emplace_back(table[word]);
				row_line.emplace_back(row_char[forward]);
			}
			else {
				wordname.emplace_back(temp);
				category.emplace_back(table["标识符"]);
				row_line.emplace_back(row_char[forward]);
			}
		}
		// 重置token, 指针后移
		word = "";
		++forward;
	}

	print_lex_ans();
	tokens = category;
	name = wordname;
	rows = row_line;
	// cout << "长度:" <<category.size() << " " << wordname.size() << endl;
}