#include "TextQuery.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {
  auto s = "textquery inputfile";
  if (argc < 2) {
    std::cout << "Error program usage.\nUsage: " << s << '\n';
    return 1;
  }

  auto ifs = std::ifstream(argv[1], std::ios::in);
  if (ifs) {
    primer::runQueries(ifs);
  } else {
    std::cout << "Error open file: " << argv[1] << "\n";
  }
  return 0;
}

void primer::runQueries(std::ifstream &infile) {
  // infile is an ifstream that is the file we want to query
  primer::TextQuery tq(infile);
  while (true) {
    std::cout << "Enter word to look for, or q to quit: ";
    std::string s;
    // stop if we hit EOF or if 'q' is entered
    if (!(std::cin >> s) || s == "q")
      break;
    // run query and print results
    print(std::cout, tq.query(s)) << '\n';
  }
}

primer::TextQuery::TextQuery(std::ifstream &ifs)
    : file(new std::vector<std::string>) {
  std::string text;
  while (std::getline(ifs, text)) {
    file->push_back(text);
    auto n = file->size() - 1;
    auto iss = std::istringstream(text);
    auto word = std::string();
    while (iss >> word) {
      // if word isn't already in wm, subscripting adds a new entry
      auto &lines = wm[word]; // lines is a shared_ptr
      if (!lines) {           // that ptr is null the first time we see word
        lines.reset(new std::set<line_no>);
      }
      lines->insert(n);
    }
  }
}

primer::QueryResult primer::TextQuery::query(const std::string &sought) const {
  // We'll return a pointer to this set if we don't find sought
  static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
  // Use find and not subscript to avoid adding words to wm!
  auto loc = wm.find(sought);
  if (loc == wm.end())
    return QueryResult(sought, nodata, file); // Not found
  else
    return QueryResult(sought, loc->second, file);
}

std::ostream &primer::print(std::ostream &os, const QueryResult &qr) {
  // if the word was found, print the count and all occurences
  os << qr.sought << " occurs " << qr.lines->size() << " "
     << (qr.lines->size() == 0 ? "time" : "times") << '\n';
  // print each line in each the word appeared
  for (auto num : *qr.lines) { // for every element in the set
    // Don't confound the user with text lines starting at 0
    os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << '\n';
  }
  return os;
}