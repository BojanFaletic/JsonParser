import json.parser;
import json.tokanizer;

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <format>

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

	int i = 0;
	while (true) {
		auto token = tokanizer.NextToken();
		if (token.type == json::TokenType::Error || token.type == json::TokenType::EndOfFile) {
			break;
		}
		std::cout << std::format("cnt: {:<5} name: {:<10} value: {}\n", i, token.name, token.value);
		i++;
	}

	json::Parser parser(str);

	int value = parser.Get("Hello").value_or(0);


	cout << "Hello World!\n";

	return 0;
}