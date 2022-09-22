#ifndef TOKEN_TYPE_H_
#define TOKEN_TYPE_H_

enum TokenType {
  KEYWORD,       // EX: class
  SYMBOL,        // EX: {
  IDENTIFIER,    // EX: xx
  INT_CONST,     // EX: 123 (from 0 to 32767 integer)
  STRING_CONST,  // EX: "xxxx"
};

extern enum TokenType tokenType;
#endif
