#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>

#include "TokenType.h";
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
  JackTokenizer(string file) : file(file) { init(); }
  void init() {
    file.erase(std::remove(file.begin(), file.end(), '\n'), file.end());
    string tmp;
    bool isStrConst = false;
    for (int i = 0; i < file.length(); i++) {
      if (file.at(i) == '"' && !isStrConst) {
        isStrConst = true;
        tmp += file.at(i);
        continue;
      }
      if (file.at(i) == '"' && isStrConst) {
        isStrConst = false;
      }

      if (DELIMITERS.find(file.at(i)) != DELIMITERS.end()) {
        if (isStrConst) {
          tmp += file.at(i);
          continue;
        }
        if (0 < tmp.length()) {
          tokens.push_back(tmp);
        }
        if (file.at(i) != ' ') {
          tokens.push_back(string{file.at(i)});
        }
        tmp = "";
      } else {
        tmp += file.at(i);
      }
    }
  }
  bool hasMoreTokens() { return tokens.size() != currentIndex; }
  void advance() {
    string token = tokens[currentIndex];
    // KEYWORD
    if (KEYWORDS.find(token) != KEYWORDS.end()) {
      type = KEYWORD;
      keyword = token;
      currentIndex++;
      return;
    }

    // SYMBOL
    if (SYMBOLS.find(token) != SYMBOLS.end()) {
      type = SYMBOL;
      symbol = token;
      // Escape
      if (token == "<") {
        symbol = "&lt;";
      }
      if (token == ">") {
        symbol = "&gt;";
      }
      if (token == "&") {
        symbol = "&amp;";
      }
      currentIndex++;
      return;
    }

    // STRING_CONST
    if (token[0] == '"') {
      type = STRING_CONST;
      token.erase(std::remove(token.begin(), token.end(), '"'), token.end());
      stringVal = token;
      currentIndex++;
      return;
    }

    // INT_CONST
    try {
      int intV = std::stoi(token);
      type = INT_CONST;
      intVal = token;
      currentIndex++;
      return;
    } catch (const std::exception& e) {
    }

    // IDENTIFIER
    type = IDENTIFIER;
    identifier = token;
    currentIndex++;
    return;
  }

  TokenType getTokenType() { return type; }
  string getKeyword() { return keyword; }
  string getSymbol() { return symbol; }
  string getIdentifier() { return identifier; }
  string getIntVal() { return intVal; }
  string getStringVal() { return stringVal; }

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
};
