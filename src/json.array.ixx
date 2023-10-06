module;

#include <map>
#include <string>
#include <vector>

using namespace std;

export module json.array;

namespace json {

export class JsonObject {
  map<string, string> stringValues;
  map<string, JsonObject> objectValues;

 public:
  JsonObject() = default;

  void AddString(const string& key, const string& value) {
    stringValues[key] = value;
  }

  void AddObject(const string& key, const JsonObject& value) {
    objectValues[key] = value;
  }

  bool HasString(const string& key) const noexcept {
    return stringValues.find(key) != stringValues.end();
  }

  bool HasObject(const string& key) const noexcept {
    return objectValues.find(key) != objectValues.end();
  }

  string GetString(const string& key) const noexcept {
    if (HasString(key)) return stringValues.at(key);
    return {};
  }

  JsonObject GetObject(const string& key) const noexcept {
    if (HasObject(key)) return objectValues.at(key);
    return {};
  }
};

export class JsonArray {
  vector<JsonObject> object;

 public:
  JsonArray() = default;

  void Add(const JsonObject& blob) { object.push_back(blob); }
  size_t Size() const noexcept { return object.size(); }
  JsonObject Get(size_t idx) const noexcept {
    if (idx >= Size()) return {};
    return object[idx];
  }
};
};  // namespace json
