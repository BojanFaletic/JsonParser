module;

#include <charconv>
#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>

using namespace std;

export module json.tokenizer_v2;

import json.string;

namespace json {

enum class StaticTokenType {
  ObjectStart,
  ObjectEnd,
  ArrayStart,
  ArrayEnd,
  Comma,
  Colon,
  NewLine,
  Space,
  Tab,
  CarriageReturn,
  True,
  False,
  Null
};

enum class DynamicTokenType {
  String,
  Number,
  NumberDecimal,
  Boolean,
};

const unordered_map<StaticTokenType, const string_view> StaticTokenMap{
    {StaticTokenType::ObjectStart, "{"},
    {StaticTokenType::ObjectEnd, "}"},
    {StaticTokenType::ArrayStart, "["},
    {StaticTokenType::ArrayEnd, "]"},
    {StaticTokenType::Comma, ","},
    {StaticTokenType::Colon, ":"},
    {StaticTokenType::NewLine, "\n"},
    {StaticTokenType::Space, " "},
    {StaticTokenType::Tab, "\t"},
    {StaticTokenType::CarriageReturn, "\r"},
    {StaticTokenType::True, "true"},
    {StaticTokenType::False, "false"},
    {StaticTokenType::Null, "null"},
};

const unordered_map<StaticTokenType, const string_view> StaticTokenPrint{
    {StaticTokenType::ObjectStart, "ObjectStart"},
    {StaticTokenType::ObjectEnd, "ObjectEnd"},
    {StaticTokenType::ArrayStart, "ArrayStart"},
    {StaticTokenType::ArrayEnd, "ArrayEnd"},
    {StaticTokenType::Comma, "Comma"},
    {StaticTokenType::Colon, "Colon"},
    {StaticTokenType::NewLine, "NewLine"},
    {StaticTokenType::Space, "Space"},
    {StaticTokenType::Tab, "Tab"},
    {StaticTokenType::CarriageReturn, "CarriageReturn"},
    {StaticTokenType::True, "True"},
    {StaticTokenType::False, "False"},
    {StaticTokenType::Null, "Null"},
};

const unordered_map<DynamicTokenType, const string_view> DynamicTokenPrint{
    {DynamicTokenType::String, "String"},
    {DynamicTokenType::Number, "Number"},
    {DynamicTokenType::NumberDecimal, "NumberDecimal"},
    {DynamicTokenType::Boolean, "Boolean"},
};

bool tokenize(String &str, const StaticTokenType token) {
  string_view name = StaticTokenMap.at(token);
  if (strncmp(str.Data(), name.data(), name.size()) == 0) {
    str.Erase(name.size());
    return true;
  }
  return false;
}

optional<StaticTokenType> decode(
    String &str, const vector<StaticTokenType> &tokens) noexcept {
  for (const StaticTokenType &token : tokens) {
    if (tokenize(str, token)) {
      return token;
    }
  }
  return nullopt;
}

optional<int> DecodeNumber(String &data) noexcept {
  if (data.Size() == 0) {
    return nullopt;
  }

  uint32_t size = 1;
  if (!(isdigit((char)data.Data()[0]) || data.Get()[0] != '-')) {
    return nullopt;
  }

  while (data.Size() > size) {
    if (!isdigit((char)data.Data()[size])) {
      string_view str_data{data.Data(), size};
      data.Erase(size - 1);

      int result;
      if (from_chars(str_data.data(), str_data.data() + str_data.size(), result)
              .ec == errc()) {
        return result;
      }
      return nullopt;
    }
    size++;
  }
  data.Erase(size);
  return nullopt;
}

optional<float> DecodeDecimalNumber(String &data) noexcept {
  if (data.Size() == 0) return nullopt;

  auto isDecimalFirstSymbol = [](const char c) {
    return c == '.' || c == '-' || isdigit(c);
  };
  auto isDecimalSymbol = [](const char c) { return c == '.' || isdigit(c); };

  uint32_t size = 1;
  if (!isDecimalFirstSymbol(data.Get()[0])) return nullopt;

  while (data.Size() > size) {
    if (!isDecimalSymbol(data.Data()[size])) {
      string_view str_data{data.Data(), size};
      data.Erase(size - 1);

      float result;
      if (from_chars(str_data.data(), str_data.data() + str_data.size(), result)
              .ec == errc()) {
        return result;
      }
      return nullopt;
    }
    size++;
  }
  data.Erase(size);
  return nullopt;
}

inline bool stringCompare(const string_view str1,
                          const string_view str2) noexcept {
  return strncmp(str1.data(), str2.data(), str2.length()) == 0;
}

optional<string_view> DecodeString(String &data) noexcept {
  const char stringSybol[] = "\"";

  if (!stringCompare(data.Get(), stringSybol)) return nullopt;
  data.Erase(1);

  uint32_t size = 0;
  while (data.Size() > size) {
    if (data.Data()[size] == *stringSybol) {
      string_view value{data.Data(), size};
      data.Erase(size + 1);
      return value;
    }
    size++;
  }

  data.Erase(size);
  return nullopt;
}
}  // namespace json