module;

#include <map>
#include <string>
#include <variant>
#include <vector>

using namespace std;

export module json.parser;

namespace json {

struct Blob;
using Item_t = variant<monostate, bool, int, double, string, Blob>;
using List_t = vector<Item_t>;
using Object_t = variant<Item_t, List_t>;

struct Blob {
  map<string, Object_t> objects;
};

export class Parser {
 public:
  Parser() = default;
  ~Parser() = default;

  void parse(const string& json) {}

 private:
  Blob root;
};
}  // namespace json