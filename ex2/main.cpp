#include "bits/stdc++.h"
#include "lex.h"
#include "grammar.h"

using namespace std;

int main()
{
    vector<vector<string>> tn;
    // 调用词法分析
    tn = lex_analyse();
    cout << tn.size() << endl;
    // 调用语法分析
    grammar_analyse(tn[0], tn[1]);
    return 0;
}