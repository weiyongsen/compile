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
	// �����ļ�
	ifstream infile; 
	infile.open("testfile.txt");
    
	// д��buffer
	infile >> noskipws;
	while (infile.peek()!=EOF){
		infile >> c;
		buffer += c;
	}
	infile.close();  

	string word="";	// ����ʶ��ĵ��ʣ�c���ַ�
	int forward = 0; 	// ��ǰָ��
	int buffer_size = buffer.size();	// �ܳ���

	// ��ʼ���ַ��ж�
	while(forward < buffer_size){
		word += buffer[forward];  //����token

		// �����ַ�  +=*/:=;,()[]{}
		if(signal_char.find(word)!=signal_char.npos){
			wordname.emplace_back(word);
			category.emplace_back(table[word]);
		}

		// �Ƚ������    ���ж� <,>,=,! ���ж� <=,>=,==,!=
		if(signal_comparison.find(word)!=signal_comparison.npos){
			word += buffer[++forward];
			if(find(double_cocmparison.begin(),double_cocmparison.end(),word) != double_cocmparison.end()){
				wordname.emplace_back(word);
				category.emplace_back(table[word]);
			}else{
				word.erase(1,1);	// ɾ���ڶ����ַ�
				wordname.emplace_back(word);
				category.emplace_back(table[word]);
				--forward;
			}
		}

		// �ж����γ���
		if(isdigit(buffer[forward])){
			while(isdigit(buffer[++forward])){
				word += buffer[forward];
			}
			--forward;
			wordname.emplace_back(word);
			category.emplace_back(table["���γ���"]);
		}
		
		// �ж��ַ�����
		if(word=="\'"){
			// cout << "��ʼ�ַ��ж�..." ;
			while(buffer[++forward] !='\''){
				word+=buffer[forward];
			} 
			word.erase(0,1);  // ȥ����ͷ��  ' 
			// cout << "��ǰtoken: " << word << "����: " << table["�ַ�����"] <<  endl;
			wordname.emplace_back(word);
			category.emplace_back(table["�ַ�����"]);
		}

		// �ж��ַ���
		if(word=="\""){
			// cout << "��ʼ�ַ����ж�...." ;
			while(buffer[++forward] !='\"'){
				word+=buffer[forward];
			} 
			word.erase(0,1);  // ȥ����ͷ��  " 
			// cout << "��ǰtoken: " << word << ".... "<< table["�ַ���"];
			wordname.emplace_back(word);
			category.emplace_back(table["�ַ���"]);
			// cout << "����ӽ�����" << endl;
		}
		
		// �жϹؼ��� �� ��ʶ��
		if(isalpha(buffer[forward]) || buffer[forward]=='_'){
			while(isalnum(buffer[++forward]) || buffer[forward]=='_'){
				word += buffer[forward];
			}
			--forward;
			string temp = word;	// ����tokenԭ�и�ʽ����name����д
			transform(word.begin(),word.end(),word.begin(),::tolower);	// token��ΪСд,�ؼ���ʶ����Сд
			if(find(key_word.begin(),key_word.end(),word) != key_word.end()){
				wordname.emplace_back(temp);
				category.emplace_back(table[word]);
			}else{
				wordname.emplace_back(temp);
				category.emplace_back(table["��ʶ��"]);
			}
		}
		// ����token, ָ�����
		word = "";
		++forward;
	}

	print_tokens();
	print_wordname();

	tokenandname.emplace_back(category);
	tokenandname.emplace_back(wordname);

	// cout << "����:" <<category.size() << " " << wordname.size() << endl;
    return tokenandname;
}