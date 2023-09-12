/*
1 - Single Responsibility Principle
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::endl;
using std::ofstream;
using std::string;
using std::to_string;
using std::vector;

struct Journal {
  string title{};
  vector<string> entries{};
  explicit Journal(const string &title_str) : title{title_str} {};
  void add(const string &entry);
  // save is not Journal's responsibility
  void save(const string &filename);
};

void Journal::add(const string &entry) {
  static int count = 1;
  entries.push_back(to_string(count++) + ": " + entry);
}

void Journal::save(const string &filename) {
  ofstream ofs{filename};
  for (auto &s : entries) {
    ofs << s << endl;
  }
}

int main() {
  Journal journal{"Dear Diary"};
  journal.add("I ate a bug");
  journal.add("I cried today");

  journal.save("test.txt");
  return 0;
}
