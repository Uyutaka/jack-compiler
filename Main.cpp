
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "JackAnalyzer.h"
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
namespace fs = std::filesystem;
int main(int argc, char *argv[]) {
  fs::path path;
  vector<fs::path> paths;

  if (argc == 2) {
    path = fs::path(argv[1]);
  }
  if (fs::is_directory(path)) {
    for (const auto &file : fs::directory_iterator(path)) {
      string fullPath = file.path().u8string();
      if (fullPath.find(".jack") != string::npos) {
        paths.push_back(file.path());
      }
    }
  } else {
    paths.push_back(path);
  }

  // Call Analyzer
  JackAnalyzer analyzer(paths);

  return 0;
}
