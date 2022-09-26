#ifndef JACK_TOKENIZER_H
#define JACK_TOKENIZER_H
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>

#include "TokenType.h"
using std::stringstream;
using std::vector;
namespace fs = std::filesystem;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::unordered_set;
using std::vector;

class JackTokenizer {
 public:
  JackTokenizer(string file);
  bool hasMoreTokens();
  void advance();
  void back();

  TokenType getTokenType();
  string getKeyword();
  string getSymbol();
  string getIdentifier();
  string getIntVal();
  string getStringVal();

 private:
  TokenType type;
  string keyword;
  string symbol;
  string stringVal;
  string file;
  string identifier;
  vector<string> tokens;
  string intVal;
  int currentIndex = 0;

  const unordered_set<char> DELIMITERS = {'{', '}', '(', ')', '[', ']', '.',
                                          ',', ';', '+', '-', '*', '/', '&',
                                          '|', '<', '>', '=', '~', ' '};
  const unordered_set<string> SYMBOLS = {"{", "}", "(", ")", "[", "]", ".",
                                         ",", ";", "+", "-", "*", "/", "&",
                                         "|", "<", ">", "=", "~"};
  const unordered_set<string> KEYWORDS = {
      "class", "constructor", "function", "method",  "field", "static",
      "var",   "int",         "char",     "boolean", "void",  "true",
      "false", "null",        "this",     "let",     "do",    "if",
      "else",  "while",       "return"};
  void init();
};

#endif
