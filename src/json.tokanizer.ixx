module;

#include <map>
#include <string>
#include <string_view>

using namespace std;

export module json.tokanizer;

namespace json {

export enum class TokenType {
  String,
  Number,
  Boolean,
  Null,
  ObjectStart,
  ObjectEnd,
  ArrayStart,
  ArrayEnd,
  Comma,
  Colon,
  EndOfFile,
  StartOfFile,
  Error
};

export struct Token {
  TokenType type;
  string_view value;
};

export class Tokanizer {
 public:
  Tokanizer(string_view json) : json_(json) {}

  Token NextToken() {
    Token token;

    json_.compare("{");

    strcmp(json_.data(), "test");
    string_view str;
  }

 private:
  string_view json_;
};

}  // namespace json