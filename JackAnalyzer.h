#ifndef JACK_ANALYZER_H
#define JACK_ANALYZER_H

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
  JackAnalyzer(const std::vector<std::filesystem::path>& paths);

 private:
  ifstream infile;
  ofstream outfile;
  stringstream ss;

  void extractJackLines();
};
#endif
