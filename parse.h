

#ifndef MV_PARSE_H
#define MV_PARSE_H

#include <algorithm> // ????
#include <sstream> // ????
extern fs::path DIRECTORY_PATH;

vector<const char *> create_c(const vector<string> &tokens, const string &name_of_program);

void parse(string b);

#endif