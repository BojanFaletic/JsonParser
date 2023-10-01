import json.parser;
import json.tokanizer;

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int main() {
  ifstream test("test.json");
  if (!test.is_open()) {
    throw runtime_error("Could not open file");
  }

  // read full file into string
  string str((istreambuf_iterator<char>(test)), istreambuf_iterator<char>());

  cout << str << endl;

  json::Tokanizer tokanizer(str);
  for (auto const &token : tokanizer) {
    cout << token << endl;
  }
  cout << "Hello World!\n";

  return 0;
}