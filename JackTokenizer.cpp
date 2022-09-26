#include "JackTokenizer.h"

#include "TokenType.h"

JackTokenizer::JackTokenizer(string file) : file(file) { init(); }
void JackTokenizer::init() {
  file.erase(std::remove(file.begin(), file.end(), '\n'), file.end());
  file.erase(std::remove(file.begin(), file.end(), '\t'), file.end());

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
bool JackTokenizer::hasMoreTokens() { return tokens.size() != currentIndex; }
void JackTokenizer::back() {
  currentIndex--;
  string token = tokens[currentIndex];

  // KEYWORD
  if (KEYWORDS.find(token) != KEYWORDS.end()) {
    type = KEYWORD;
    keyword = token;
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
    return;
  }

  // STRING_CONST
  if (token[0] == '"') {
    type = STRING_CONST;
    token.erase(std::remove(token.begin(), token.end(), '"'), token.end());
    stringVal = token;
    return;
  }

  // INT_CONST
  try {
    std::stoi(token);
    type = INT_CONST;
    intVal = token;
    return;
  } catch (const std::exception& e) {
  }

  // IDENTIFIER
  type = IDENTIFIER;
  identifier = token;
  return;
}

void JackTokenizer::advance() {
  string token = tokens[currentIndex];
  currentIndex++;
  // KEYWORD
  if (KEYWORDS.find(token) != KEYWORDS.end()) {
    type = KEYWORD;
    keyword = token;
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
    return;
  }

  // STRING_CONST
  if (token[0] == '"') {
    type = STRING_CONST;
    token.erase(std::remove(token.begin(), token.end(), '"'), token.end());
    stringVal = token;
    return;
  }

  // INT_CONST
  try {
    std::stoi(token);
    type = INT_CONST;
    intVal = token;
    return;
  } catch (const std::exception& e) {
  }

  // IDENTIFIER
  type = IDENTIFIER;
  identifier = token;
  return;
}

TokenType JackTokenizer::getTokenType() { return type; }
string JackTokenizer::getKeyword() { return keyword; }
string JackTokenizer::getSymbol() { return symbol; }
string JackTokenizer::getIdentifier() { return identifier; }
string JackTokenizer::getIntVal() { return intVal; }
string JackTokenizer::getStringVal() { return stringVal; }
