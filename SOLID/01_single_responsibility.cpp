/*
1 - Single Responsibility Principle
*/
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::endl;
using std::ofstream;
using std::replace;
using std::string;
using std::to_string;
using std::vector;

/* Poem struct only responsible to control the content of a poem*/

struct Poem {
  string title{};
  vector<string> entries{};
  int count{0};
  explicit Poem(const string &new_title) : title{new_title} {};

  // "add" method is Poem's Responsibility
  void add(const string &sentence);
  // but "save" method is a separate concern
  void save(const string &filename);
};

// defining Poem's add method
void Poem::add(const string &sentence) {
  entries.push_back(to_string(count++) + ": " + sentence);
}

// defining Poem's save method
void Poem::save(const string &filename) {
  ofstream ofs{filename};
  for (string entry : entries) {
    ofs << entry << endl;
  }
}

/* Collection Manager helps to manage the poem files*/
struct CollectionManager {
  static void save(const Poem &poem, string filename) {
    replace(filename.begin(), filename.end(), ' ', '_');
    ofstream ofs{filename};
    for (string entry : poem.entries) {
      ofs << entry << endl;
    }
  }
};

/* Main program*/
int main() {
  string title = "Today is a good day";
  Poem poem{title};
  poem.add("The weather is good,");
  poem.add("The people is nice,");
  poem.add("But the wallet is void.");
  // poem.save("test.txt"); // Poem struct should not manage saving tasks

  CollectionManager cm;
  cm.save(poem, title + ".txt");
  return 0;
}
