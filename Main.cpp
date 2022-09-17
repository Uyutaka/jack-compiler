#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "JackAnalyzer.cpp";
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
namespace fs = std::filesystem;
int main(int argc, char *argv[]) {
  // fs::path path = "project10/ArrayTest/Main.jack";  // File
  fs::path path = "project10/Square";  // Directory

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
