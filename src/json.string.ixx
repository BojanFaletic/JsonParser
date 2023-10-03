module;

#include <string>
#include <string_view>
#include <cstdint>

using namespace std;

export module json.string;

namespace json {
	export class String {
		const string str_;
		uint64_t start_ = 0;
	public:
		explicit String(const string& str) noexcept : str_(str) {}
		String(String&& str) noexcept : str_(move(str.str_)), start_(str.start_) {}
		String(const String& str) noexcept : str_(str.str_), start_(str.start_) {}
		~String() = default;


		inline void Erase(size_t length) noexcept {
			start_ = static_cast<uint64_t>(min(start_ + length, str_.size()));
		}

		inline size_t Size() const noexcept {
			return str_.size() - start_;
		}

		inline const char* Data() const noexcept {
			return str_.data() + start_;
		}

		inline string_view Get() const noexcept {
			return string_view(str_).substr(start_);
		}

	private:
		String& operator=(const String& str) = delete;
		String& operator=(String&& str) = delete;
	};
}