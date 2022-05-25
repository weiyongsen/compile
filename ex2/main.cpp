#include "bits/stdc++.h"
#include "lex.h"
#include "grammar.h"

using namespace std;

int main()
{
    vector<vector<string>> tn;
    tn = lex_analyse();
    cout << tn.size() << endl;
    grammar_analyse(tn[0], tn[1]);
    
    return 0;
}