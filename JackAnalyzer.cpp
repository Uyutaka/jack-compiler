#include "JackAnalyzer.h"

#include "CompilationEngine.h"
#include "JackTokenizer.h"

JackAnalyzer::JackAnalyzer(const vector<fs::path>& paths) {
  for (auto path : paths) {
    infile.open(path);
    extractJackLines();
    infile.close();

    // Generate paths for T.XML, .XML
    fs::path tokenPath = path;
    fs::path xmlPath = path;
    tokenPath.replace_filename(tokenPath.stem().string() + "T");
    tokenPath.replace_extension(".out_xml");
    xmlPath.replace_extension(".out_xml");

    //////////////////////////////////////////////
    ////////////////// Tokenize //////////////////
    //////////////////////////////////////////////
    outfile.open(tokenPath);
    outfile << "<tokens>" << endl;
    JackTokenizer tokenizer(ss.str());
    while (tokenizer.hasMoreTokens()) {
      tokenizer.advance();
      switch (tokenizer.getTokenType()) {
        case KEYWORD:
          outfile << "<keyword> " << tokenizer.getKeyword() << " </keyword>"
                  << endl;
          break;
        case SYMBOL:
          outfile << "<symbol> " << tokenizer.getSymbol() << " </symbol>"
                  << endl;
          break;
        case IDENTIFIER:
          outfile << "<identifier> " << tokenizer.getIdentifier()
                  << " </identifier>" << endl;
          break;
        case INT_CONST:
          outfile << "<integerConstant> " << tokenizer.getIntVal()
                  << " </integerConstant>" << endl;
          break;
        case STRING_CONST:
          outfile << "<stringConstant> " << tokenizer.getStringVal()
                  << " </stringConstant>" << endl;
          break;
      }
    }
    outfile << "</tokens>" << endl;
    outfile.close();

    ///////////////////////////////////////////////////////
    ////////////////// CompilationEngine //////////////////
    ///////////////////////////////////////////////////////
    JackTokenizer jt(ss.str());
    CompilationEngine engine(jt, xmlPath.string());
  }
}

void JackAnalyzer::extractJackLines() {
  // Initialize ss
  ss.str(string());
  ss.clear();

  bool isMultiLineComment = false;
  string line;
  while (getline(infile, line)) {
    // For multi-line comment
    if (line.find("/*") != string::npos && line.find("*/") == string::npos) {
      isMultiLineComment = true;
      continue;
    }
    if (line.find("*/") != string::npos) {
      isMultiLineComment = false;
      line = line.substr(line.find("*/") + 2);
    }
    if (isMultiLineComment) {
      continue;
    }

    // Remove newline
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

    // Remove single-line comment (//)
    if (line.find("//") != string::npos) {
      line = line.substr(0, line.find("//"));
    }

    // Remove start-of-line spaces
    while (line.find_first_of(" ") == 0) {
      line = line.substr(1);
    }

    // Remove end-of-line spaces
    while (line.find_last_of(" ") != string::npos &&
           line.find_last_of(" ") == line.size() - 1) {
      line.pop_back();
    }

    // If not empty, push it
    if (line.size() != 0) {
      ss << line << endl;
    }
  }
}
