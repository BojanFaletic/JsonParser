import json.parser;

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

  // read file
  string line;
  while (getline(test, line)) {
    cout << line << endl;
  }

  cout << "Hello World!\n";

  return 0;
}