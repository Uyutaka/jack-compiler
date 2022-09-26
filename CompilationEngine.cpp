#include "CompilationEngine.h"

CompilationEngine::CompilationEngine(JackTokenizer jt, string fileName)
    : jt(jt) {
  outfile.open(fileName);

  compileClass();

  outfile.close();
}
void CompilationEngine::compileClass(void) {
  outfile << "<class>" << endl;

  // class
  jt.advance();
  outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;

  // className
  jt.advance();
  outfile << "<identifier> " << jt.getIdentifier() << " </identifier>" << endl;

  // {
  jt.advance();
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  jt.advance();
  while ((jt.getTokenType() == KEYWORD) &&
         (jt.getKeyword() == "static" || jt.getKeyword() == "field" ||
          jt.getKeyword() == "constructor" || jt.getKeyword() == "function" ||
          jt.getKeyword() == "method")) {
    if (jt.getKeyword() == "static" || jt.getKeyword() == "field") {
      compileClassVarDec();
    }
    if (jt.getKeyword() == "constructor" || jt.getKeyword() == "function" ||
        jt.getKeyword() == "method") {
      compileSubroutine();
    }
  }

  // }
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  outfile << "</class>" << endl;
}

void CompilationEngine::compileClassVarDec(void) {
  outfile << "<classVarDec>" << endl;
  // static or field
  outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;

  // type (int, char, boolean, or className)
  jt.advance();
  switch (jt.getTokenType()) {
    case KEYWORD:  // int, char, boolean
      outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;
      break;
    case IDENTIFIER:  // className
      outfile << "<identifier> " << jt.getIdentifier() << " </identifier>"
              << endl;
      break;
    default:
      break;
  }

  // varName
  jt.advance();
  while (!(jt.getTokenType() == SYMBOL && jt.getSymbol() == ";")) {
    switch (jt.getTokenType()) {
      case IDENTIFIER:
        outfile << "<identifier> " << jt.getIdentifier() << " </identifier>"
                << endl;
        break;
      case SYMBOL:  // ,
        outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
        break;
      default:
        break;
    }
    jt.advance();
  }

  // ;
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  outfile << "</classVarDec>" << endl;
  jt.advance();
}

void CompilationEngine::compileSubroutine(void) {
  outfile << "<subroutineDec>" << endl;

  // constructor, function, method
  outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;

  // void or type
  jt.advance();
  switch (jt.getTokenType()) {
    case KEYWORD:
      outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;
      break;
    case IDENTIFIER:
      outfile << "<identifier> " << jt.getIdentifier() << " </identifier>"
              << endl;
      break;
    default:
      break;
  }

  // subroutineName
  jt.advance();
  outfile << "<identifier> " << jt.getIdentifier() << " </identifier>" << endl;

  // (
  jt.advance();
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // parameterList
  jt.advance();
  compileParameterList();

  // )
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // {
  jt.advance();
  compileSubroutineBody();

  outfile << "</subroutineDec>" << endl;
  jt.advance();
}

void CompilationEngine::compileParameterList(void) {
  outfile << "<parameterList>" << endl;
  // type
  while (!(jt.getTokenType() == SYMBOL && jt.getSymbol() == ")")) {
    switch (jt.getTokenType()) {
      case KEYWORD:
        outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;
        break;
      case IDENTIFIER:
        outfile << "<identifier> " << jt.getIdentifier() << " </identifier>"
                << endl;
        break;
      case SYMBOL:
        outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
        break;
      default:
        break;
    }
    // type, varName, or ","
    jt.advance();
  }
  outfile << "</parameterList>" << endl;
}

void CompilationEngine::compileSubroutineBody(void) {
  outfile << "<subroutineBody>" << endl;

  // {
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // varDec or statements
  jt.advance();
  while (jt.getTokenType() == KEYWORD && jt.getKeyword() == "var") {
    compileVarDec();
  }

  compileStatements();

  // }
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  outfile << "</subroutineBody>" << endl;
}

void CompilationEngine::compileVarDec(void) {
  outfile << "<varDec>" << endl;

  // var
  outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;

  // var, type, varName, ;, or ","
  jt.advance();
  while (!(jt.getTokenType() == SYMBOL && jt.getSymbol() == ";")) {
    switch (jt.getTokenType()) {
      case KEYWORD:
        outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;
        break;
      case IDENTIFIER:
        outfile << "<identifier> " << jt.getIdentifier() << " </identifier>"
                << endl;
        break;
      case SYMBOL:
        outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
        break;
      default:
        break;
    }
    jt.advance();
  }

  // ;
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // statement or varDec
  jt.advance();

  outfile << "</varDec>" << endl;
}

void CompilationEngine::compileStatements(void) {
  outfile << "<statements>" << endl;
  while (jt.getTokenType() == KEYWORD &&
         (jt.getKeyword() == "let" || jt.getKeyword() == "do" ||
          jt.getKeyword() == "while" || jt.getKeyword() == "return" ||
          jt.getKeyword() == "if")) {
    if (jt.getKeyword() == "let") {
      compileLet();
    } else if (jt.getKeyword() == "do") {
      compileDo();
    } else if (jt.getKeyword() == "while") {
      compileWhile();
    } else if (jt.getKeyword() == "return") {
      compileReturn();
    } else if (jt.getKeyword() == "if") {
      compileIf();
    }
  }

  outfile << "</statements>" << endl;
}
void CompilationEngine::compileDo(void) {
  outfile << "<doStatement> " << endl;
  // do
  outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;
  /*******************
   * subroutineCall  *
   ********************/
  // subroutineName or className, varName
  jt.advance();
  outfile << "<identifier> " << jt.getIdentifier() << " </identifier>" << endl;

  // ( or .
  jt.advance();
  if (jt.getTokenType() == SYMBOL && jt.getSymbol() == "(") {
    // (
    outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

    // expressionList
    jt.advance();
    compileExpressionList();

    // )
    outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
  } else if (jt.getTokenType() == SYMBOL && jt.getSymbol() == ".") {
    // .
    outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

    // subroutineName
    jt.advance();
    outfile << "<identifier> " << jt.getIdentifier() << " </identifier>"
            << endl;

    // (
    jt.advance();
    outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

    // expressionList
    jt.advance();
    compileExpressionList();

    // )
    outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
  }

  // ;
  jt.advance();
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  outfile << " </doStatement>" << endl;

  jt.advance();
}
void CompilationEngine::compileLet(void) {
  outfile << "<letStatement>" << endl;
  // let
  outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;

  // varName
  jt.advance();
  outfile << "<identifier> " << jt.getIdentifier() << " </identifier>" << endl;

  //[ or =
  jt.advance();

  if (jt.getTokenType() == SYMBOL && jt.getSymbol() == "[") {
    outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

    // expression
    jt.advance();
    compileExpression();

    if (jt.getTokenType() == SYMBOL && jt.getSymbol() == "]") {
      outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
      jt.advance();
    }
  }

  if (jt.getTokenType() == SYMBOL && jt.getSymbol() == "=") {
    outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

    // expression
    jt.advance();
    compileExpression();
  }

  // ;
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  outfile << "</letStatement>" << endl;
  jt.advance();
}

void CompilationEngine::compileWhile(void) {
  outfile << "<whileStatement>" << endl;

  // while
  outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;

  // (
  jt.advance();
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // expression
  jt.advance();
  compileExpression();

  // )
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // {
  jt.advance();
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // statements
  jt.advance();
  compileStatements();

  // }
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  outfile << "</whileStatement>" << endl;

  jt.advance();
}

void CompilationEngine::compileReturn(void) {
  outfile << "<returnStatement>" << endl;

  // return
  outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;

  // ; or expression
  jt.advance();

  if (!(jt.getTokenType() == SYMBOL && jt.getSymbol() == ";")) {
    compileExpression();
  }
  //;
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  outfile << "</returnStatement>" << endl;

  jt.advance();
}

void CompilationEngine::compileIf(void) {
  outfile << "<ifStatement>" << endl;
  // if
  outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;

  // (
  jt.advance();
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // expression
  jt.advance();
  compileExpression();

  // )
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // {
  jt.advance();
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // statements
  jt.advance();
  compileStatements();

  // }
  outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

  // check if next token is else
  jt.advance();

  while (jt.getTokenType() == KEYWORD && jt.getKeyword() == "else") {
    // else
    outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;

    // {
    jt.advance();
    outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

    // statements
    jt.advance();
    compileStatements();

    // }
    outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

    jt.advance();
  }

  outfile << "</ifStatement>" << endl;
}

void CompilationEngine::compileExpression(void) {
  outfile << "<expression>" << endl;
  compileTerm();

  while (jt.getTokenType() == SYMBOL &&
         (jt.getSymbol() == "+" || jt.getSymbol() == "-" ||
          jt.getSymbol() == "*" || jt.getSymbol() == "/" ||
          jt.getSymbol() == "&amp;" || jt.getSymbol() == "|" ||
          jt.getSymbol() == "&lt;" || jt.getSymbol() == "&gt;" ||
          jt.getSymbol() == "=")) {
    outfile << "<symbol> " << jt.getSymbol() << " </symbol> " << endl;
    // if (jt.getSymbol() == "<") {
    //   outfile << "&lt;";
    // } else if (jt.getSymbol() == ">") {
    //   outfile << "&gt;";
    // } else if (jt.getSymbol() == "&") {
    //   outfile << "&amp;";
    // } else {
    // outfile << jt.getSymbol();
    // }
    // outfile << " </symbol> " << endl;

    // term
    jt.advance();
    compileTerm();
  }
  outfile << "</expression>" << endl;
}

void CompilationEngine::compileTerm(void) {
  outfile << "<term>" << endl;
  switch (jt.getTokenType()) {
    case INT_CONST:
      outfile << "<integerConstant> " << jt.getIntVal() << " </integerConstant>"
              << endl;
      break;
    case STRING_CONST:
      outfile << "<stringConstant> " << jt.getStringVal()
              << " </stringConstant>" << endl;
      break;
    case KEYWORD:
      // keywordConstant (true, false, null, or this)
      outfile << "<keyword> " << jt.getKeyword() << " </keyword>" << endl;
      break;

    case SYMBOL:
      // unaryOp
      if (jt.getSymbol() == "-" || jt.getSymbol() == "~") {
        // - or ~
        outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
        // term
        jt.advance();
        compileTerm();
        break;
      }
      // (expression)
      if (jt.getSymbol() == "(") {
        // (
        outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

        // expression
        jt.advance();
        compileExpression();

        // )
        outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
        break;
      }
      break;

    case IDENTIFIER: {
      // subroutineCall OR varName, varName[expression]

      /* Need to look ahead for distinguishing varName or subroutineCall
        - "("" or "." if subroutineCall
        *******************************************************************/
      JackTokenizer tmpJt = jt;
      tmpJt.advance();
      if (tmpJt.getTokenType() == SYMBOL &&
          (tmpJt.getSymbol() == "(" || tmpJt.getSymbol() == ".")) {
        // subroutineCall
        outfile << "<identifier> " << jt.getIdentifier() << " </identifier>"
                << endl;
        // ( or .
        jt.advance();
        if (jt.getTokenType() == SYMBOL && jt.getSymbol() == "(") {
          // (
          outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

          // expressionList
          jt.advance();
          compileExpressionList();

          // )
          outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
        } else if (jt.getTokenType() == SYMBOL && jt.getSymbol() == ".") {
          // .
          outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

          // subroutineName
          jt.advance();
          outfile << "<identifier> " << jt.getIdentifier() << " </identifier>"
                  << endl;

          // (
          jt.advance();
          outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

          // expressionList
          jt.advance();
          compileExpressionList();

          // )
          outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
        }
      } else {
        // varName or varName[expression]
        outfile << "<identifier> " << jt.getIdentifier() << " </identifier>"
                << endl;
        // check if next token is [
        jt.advance();
        if (jt.getTokenType() == SYMBOL && jt.getSymbol() == "[") {
          // [
          outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;

          // expression
          jt.advance();
          compileExpression();
          // ]
          outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
        } else {
          jt.back();
        }
      }
      break;
    }
    default:
      break;
  }
  outfile << "</term>" << endl;
  jt.advance();
}

void CompilationEngine::compileExpressionList(void) {
  outfile << "<expressionList>" << endl;
  while (!(jt.getTokenType() == SYMBOL && jt.getSymbol() == ")")) {
    compileExpression();
    if (jt.getTokenType() == SYMBOL && jt.getSymbol() == ",") {
      // ,
      outfile << "<symbol> " << jt.getSymbol() << " </symbol>" << endl;
      jt.advance();
    }
  }
  outfile << "</expressionList>" << endl;
}
