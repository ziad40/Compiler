
#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "lexical_rules.cpp"
#include "DFA.cpp"
vector<Node*> lexical_analysis(string relative_path, read_input& r);
#endif //LEXICAL_ANALYZER_H
