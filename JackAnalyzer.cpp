
#include "JackAnalyzer.h"

#include "JackTokenizer.h"

JackAnalyzer::JackAnalyzer(const std::vector<std::filesystem::path>& paths) {
  for (auto path : paths) {
    infile.open(path);
    extractJackLines();
    infile.close();

    //////////////////////////////////////////////
    ////////////////// Tokenize //////////////////
    //////////////////////////////////////////////

    // Handle output file for tokenizer
    path.replace_filename(path.stem().string() + "T");
    path.replace_extension(".out_xml");
    outfile.open(path);
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

    /////////////////////////////////
    // TODO Call CompilationEngine //
    /////////////////////////////////
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
