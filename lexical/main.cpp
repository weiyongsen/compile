#include<iostream>
#include<string.h>
#include"lexical_analysis.h"
#include"grammar_analysis.h"
#include<map>
using namespace std;
int main()
{
	char FileIn[200] = "testfile.txt";
	char FileOut1[200] = "lex_output.txt";
	char FileOut2[200] = "output.txt";
	FILE *fin, *fout1, *fout2;
	vector<pair<string, string>> lexical_results;
	if ((fin = fopen(FileIn, "r")) == NULL || (fout1 = fopen(FileOut1, "w")) == NULL || (fout2 = fopen(FileOut2, "w")) == NULL)
		cout << "文件不存在！" << endl;
	else {
		Lexical lexical(fin, fout1);
		lexical_results = lexical.analyse();
		Grammar grammar(lexical_results, fout2);
		grammar.program_entry();
	}
}
