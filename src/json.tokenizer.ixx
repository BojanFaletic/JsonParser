module;

#include <map>
#include <string>
#include <string_view>
#include <optional>
#include <vector>
#include <array>
#include <tuple>

using namespace std;

export module json.tokanizer;

namespace json {
	/**
	 * @brief The type of token
	 *
	 */
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
		Error,
		Space,
		NewLine
	};

	/**
	 * @brief A token
	 */
	export struct Token {
		const TokenType type;
		const string value;
		const string name;
	};

	/**
	 * @brief Compares if string2 is equal to the first n characters of string1
	 */
	inline bool stringCompare(const string& str1, const string_view str2) {
		return strncmp(str1.data(), str2.data(), str2.length()) == 0;
	}

	/**
	 * @brief A tokanizer for JSON
	 */
	export class Tokanizer {
	private:
		const vector<tuple<string_view, TokenType, string_view>> staticSymbols_{
			{"{", TokenType::ObjectStart, "ObjectStart"},
			{"}", TokenType::ObjectEnd, "ObjectEnd"},
			{"[", TokenType::ArrayStart, "ArrayStart"},
			{"]", TokenType::ArrayEnd, "ArrayEnd"},
			{",", TokenType::Comma, "Comma"},
			{":", TokenType::Colon, "Colon"},
			{"true", TokenType::Boolean, "Boolean"},
			{"false", TokenType::Boolean, "Boolean"},
			{"null", TokenType::Null, "Null"},
			{" ", TokenType::Space, "Space"},
			{"\n", TokenType::NewLine, "NewLine"},
		};

		string json_;

	public:
		Tokanizer(string& json) : json_(json) {}

		/**
		 * @brief Returns the next token in the JSON string
		 */
		Token NextToken() noexcept {
			if (auto token = StaticDecode(); token.has_value()) {
				return token.value();
			}
			else if (auto string = DecodeString(); string.has_value()) {
				return Token{ TokenType::String, string.value(), "String" };
			}
			else if (auto number = DecodeNumber(); number.has_value()) {
				return Token{ TokenType::Number, number.value(), "Number" };
			}
			else if (json_.size() == 0) {
				return { TokenType::EndOfFile, " ", "EndOfFile" };
			}

			return { TokenType::Error, "" };
		}

	private:

		/**
		 * @brief Checks if the JSON starts with a static symbol
		 */
		optional<Token> StaticDecode() noexcept {
			for (const auto& [str2, type, name] : staticSymbols_) {
				if (stringCompare(json_, str2)) {
					json_.erase(0, str2.length());
					return Token{ type, string(str2), string(name) };
				}
			}
			return nullopt;
		}

		/**
		 * @brief Checks if the JSON starts with a number
		 */
		optional<string> DecodeNumber() noexcept {
			// starts with digit
			if (!isdigit((char)json_.data()[0])) {
				return nullopt;
			}

			uint32_t size = 0;
			while (json_.size() > size) {
				if (!isdigit((char)json_.data()[size])) {
					string ss{ json_.substr(0, size) };
					json_.erase(0, size);
					return ss;
				}
				size++;
			}
			json_.erase(0, size);
			return nullopt;
		}

		/**
		 * @brief Checks if the JSON starts with a string
		 */
		optional<string> DecodeString() noexcept {
			const char stringSybol[] = "\"";

			// check if string starts with "
			if (!stringCompare(json_, stringSybol))
			{
				return nullopt;
			}

			json_.erase(0, 1);

			uint32_t size = 0;
			while (json_.length() > size) {
				if (json_.data()[size] == *stringSybol) {
					// end of string
					string str = json_.substr(0, size);
					json_.erase(0, size + 1);
					return str;
				}
				size++;
			}

			json_.erase(0, size);
			return nullopt;
		}
	};

}  // namespace json