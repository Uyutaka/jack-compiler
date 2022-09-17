#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
namespace fs = std::filesystem;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
class JackAnalyzer {
 public:
  JackAnalyzer(const std::vector<std::filesystem::path>& paths) {
    for (auto path : paths) {
      infile.open(path);
      extractJackLines();
      infile.close();

      // Tokenize
      /////////////////////////
      // TODO Call tokenizer //
      /////////////////////////
      cout << ss.str() << endl;
      cout << endl << endl;

      // Handle output file
      path.replace_extension(".out_xml");
      outfile.open(path);
      /////////////////////////////////
      // TODO Call CompilationEngine //
      /////////////////////////////////

      outfile.close();
    }
  }

 private:
  ifstream infile;
  ofstream outfile;
  stringstream ss;

  void extractJackLines() {
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
};
