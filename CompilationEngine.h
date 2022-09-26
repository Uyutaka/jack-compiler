#ifndef COMPILATION_ENGINE_H
#define COMPILATION_ENGINE_H

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "JackTokenizer.h"

using std::vector;
namespace fs = std::filesystem;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;

class CompilationEngine {
 public:
  CompilationEngine(JackTokenizer jt, string fileName);
  void compileClass(void);
  void compileClassVarDec(void);
  void compileSubroutine(void);
  void compileParameterList(void);
  void compileSubroutineBody(void);
  void compileVarDec(void);
  void compileStatements(void);
  void compileDo(void);
  void compileLet(void);
  void compileWhile(void);
  void compileReturn(void);
  void compileIf(void);
  void compileExpression(void);
  void compileTerm(void);
  void compileExpressionList(void);

 private:
  JackTokenizer jt;
  ofstream outfile;
};
#endif
