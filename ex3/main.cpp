#include <iostream>
#include <vector>
#include <string>
#include "lex.h"
// #include "grammar.h"
#include "error.h"

using namespace std;

int main() {
	/*vector<vector<string>> tn;
	tn = lex_analyse();
	cout << tn.size() << endl;
	grammar_analyse(tn[0], tn[1]);*/
	vector<string> tokens;
	vector<string> names;
	vector<int> rows;

	lex_analyse(tokens, names, rows);
	
	error_analyse(tokens, names, rows);

	return 0;
}