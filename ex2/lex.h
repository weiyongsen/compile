#pragma once
#include "bits/stdc++.h"
#include "table.h"
#define MAX_LINE 1024
using namespace std;
vector<string> wordname;
vector<string> category;

void print_tokens(){
	ofstream outfile;
	outfile.open("tokens.txt");
	for (int i = 0; i < wordname.size(); i++){
		outfile << category[i] << endl;
	}
	outfile.close();
}

void print_wordname(){
	ofstream outfile;
	outfile.open("wordnames.txt");
	for (int i = 0; i < wordname.size(); i++){
		outfile << wordname[i] << endl;
	}
	outfile.close();
}

vector<vector<string>> lex_analyse(){
	vector<vector<string>> tokenandname;


    char c = '\0';
	string buffer;
	// 读入文件
	ifstream infile; 
	infile.open("testfile.txt");
    
	// 写入buffer
	infile >> noskipws;
	while (infile.peek()!=EOF){
		infile >> c;
		buffer += c;
	}
	infile.close();  

	string word="";	// 正在识别的单词，c是字符
	int forward = 0; 	// 向前指针
	int buffer_size = buffer.size();	// 总长度

	// 开始逐字符判断
	while(forward < buffer_size){
		word += buffer[forward];  //更新token

		// 特殊字符  +=*/:=;,()[]{}
		if(signal_char.find(word)!=signal_char.npos){
			wordname.emplace_back(word);
			category.emplace_back(table[word]);
		}

		// 比较运算符    先判断 <,>,=,! 再判断 <=,>=,==,!=
		if(signal_comparison.find(word)!=signal_comparison.npos){
			word += buffer[++forward];
			if(find(double_cocmparison.begin(),double_cocmparison.end(),word) != double_cocmparison.end()){
				wordname.emplace_back(word);
				category.emplace_back(table[word]);
			}else{
				word.erase(1,1);	// 删除第二个字符
				wordname.emplace_back(word);
				category.emplace_back(table[word]);
				--forward;
			}
		}

		// 判断整形常量
		if(isdigit(buffer[forward])){
			while(isdigit(buffer[++forward])){
				word += buffer[forward];
			}
			--forward;
			wordname.emplace_back(word);
			category.emplace_back(table["整形常量"]);
		}
		
		// 判断字符常量
		if(word=="\'"){
			// cout << "开始字符判断..." ;
			while(buffer[++forward] !='\''){
				word+=buffer[forward];
			} 
			word.erase(0,1);  // 去掉开头的  ' 
			// cout << "当前token: " << word << "类型: " << table["字符常量"] <<  endl;
			wordname.emplace_back(word);
			category.emplace_back(table["字符常量"]);
		}

		// 判断字符串
		if(word=="\""){
			// cout << "开始字符串判断...." ;
			while(buffer[++forward] !='\"'){
				word+=buffer[forward];
			} 
			word.erase(0,1);  // 去掉开头的  " 
			// cout << "当前token: " << word << ".... "<< table["字符串"];
			wordname.emplace_back(word);
			category.emplace_back(table["字符串"]);
			// cout << "已添加进容器" << endl;
		}
		
		// 判断关键字 或 标识符
		if(isalpha(buffer[forward]) || buffer[forward]=='_'){
			while(isalnum(buffer[++forward]) || buffer[forward]=='_'){
				word += buffer[forward];
			}
			--forward;
			string temp = word;	// 保留token原有格式，向name中填写
			transform(word.begin(),word.end(),word.begin(),::tolower);	// token变为小写,关键字识别用小写
			if(find(key_word.begin(),key_word.end(),word) != key_word.end()){
				wordname.emplace_back(temp);
				category.emplace_back(table[word]);
			}else{
				wordname.emplace_back(temp);
				category.emplace_back(table["标识符"]);
			}
		}
		// 重置token, 指针后移
		word = "";
		++forward;
	}

	print_tokens();
	print_wordname();

	tokenandname.emplace_back(category);
	tokenandname.emplace_back(wordname);

	// cout << "长度:" <<category.size() << " " << wordname.size() << endl;
    return tokenandname;
}