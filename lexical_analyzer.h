
#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include "read_input.cpp"
#include "DFA.cpp"
vector<Node*> lexical_analysis(string relative_path, read_input& r);
#endif //LEXICAL_ANALYZER_H
