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
  Error
};
}  // namespace json