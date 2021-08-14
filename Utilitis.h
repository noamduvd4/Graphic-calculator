
#ifndef UTILITIS_H
#define UTILITIS_H
#include <stdbool.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <map>
#include <set>
#include <iostream>
#include <vector>

const char SPLITER=',';
const char WHITE_SPACE=' ';
const char PLUS ='+';
const char INTERSECTION='^';
const char SUBTRACTION ='-';
const char ASTERISK='*';
const char OPEN_NEW_GRAPH='{';
const char CLOSE_NEW_GRAPH='}';
const char LESS_THAN_SIGN='<';
const char MORE_THAN_SIGN='>';
const char OPEN_PARENTHESIS='[';
const char CLOSE_PARENTHESIS=']';
const char CLOSE_CYRCLE_PARENTHESIS=')';
const char OPEN_CYRCLE_PARENTHESIS='(';
const char NOT='!';
const char EQUAL='=';
const std::string VALID_GRAPH_NAME=" G1 ";
const std::string DELETE_COMMAND="delete";
const std::string PRINT_COMMAND="print";
const std::string WHO_COMMAND="who";
const std::string RESET_COMMAND="reset";
const std::string QUIT_COMMAND="quit";
const std::string SAVE_COMMAND="save";
const std::string LOAD_COMMAND="load";
const std::set<char> VALID_OPERATORS_SET= {PLUS,INTERSECTION,SUBTRACTION,ASTERISK};
const char COMMA=';';
const std::set <std::string> SAVED_WORD={DELETE_COMMAND,PRINT_COMMAND,WHO_COMMAND,RESET_COMMAND,QUIT_COMMAND,SAVE_COMMAND};
void RemoveSpacesFromBeginAndEnd(std::string & name);
std::vector<std::string> SplitToArry(const std::string &data,char split_char);
#endif //UTILITIS_H