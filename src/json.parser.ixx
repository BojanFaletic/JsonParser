module;

#include <map>
#include <string>
#include <variant>
#include <vector>
#include <optional>

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
		const string json_;
		uint32_t pos_ = 0;

	public:
		Parser(const string json) : json_(json) {}
		~Parser() = default;

		void parse() {

		}

		optional<List_t> GetArray(const string& key) {
			return nullopt;
		}

		optional<int> Get(const string& key) {
			return nullopt;
		}

	private:
		Blob root;
	};
}  // namespace json