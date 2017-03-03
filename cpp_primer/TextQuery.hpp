#ifndef _TEXTQUERY_H_
#define _TEXTQUERY_H_

#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace primer {
void runQueries(std::ifstream &infile);

class QueryResult;

class TextQuery {
public:
  using line_no = std::vector<std::string>::size_type;
  explicit TextQuery(std::ifstream &);
  QueryResult query(const std::string &) const;

private:
  std::shared_ptr<std::vector<std::string>> file; // Input file
  // Map of each word to the set of the lines in which that word appears
  std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
  friend std::ostream &print(std::ostream &, const QueryResult &);

public:
  QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p,
              std::shared_ptr<std::vector<std::string>> f)
      : sought(s), lines(p), file(f) {}

private:
  std::string sought;
  std::shared_ptr<std::set<TextQuery::line_no>> lines;
  std::shared_ptr<std::vector<std::string>> file;
};
}

#endif