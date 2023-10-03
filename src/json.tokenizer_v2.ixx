module;

#include <unordered_map>
#include <string>
#include <string_view>
#include <functional>
#include <optional>
#include <charconv>

using namespace std;

export module json.tokenizer_v2;

import json.string;

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
		Space,
		NewLine
	};

	const unordered_map<TokenType, const string_view> StaticTokenMap{
		{TokenType::ObjectStart, "{"},
		{TokenType::ObjectEnd, "}"},
		{TokenType::ArrayStart, "["},
		{TokenType::ArrayEnd, "]"},
		{TokenType::Comma, ","},
		{TokenType::Colon, ":"},
		{TokenType::NewLine, "\n"},
		{TokenType::Space, " "},
		{TokenType::Space, "\t"},
		{TokenType::Space, "\r"},
		{TokenType::Boolean, "true"},
		{TokenType::Boolean, "false"},
		{TokenType::Null, "null"}
	};



	optional<int> DecodeDecimalNumber(String& data) noexcept {
		if (data.Size() == 0) {
			return nullopt;
		}

		uint32_t size = 1;
		if (!(isdigit((char)data.Data()[0]) || data.Get()[0] != '-')) {
			return nullopt;
		}

		while (data.Size() > size) {
			if (!isdigit((char)data.Data()[size])) {
				string str_data{ data.Data(), size };
				data.Erase(size - 1);
				return stoi(str_data);
			}
			size++;
		}
		data.Erase(size);
		return nullopt;
	}

	inline bool stringCompare(const string_view str1, const string_view str2) noexcept {
		return strncmp(str1.data(), str2.data(), str2.length()) == 0;
	}

	optional<string_view> DecodeString(String& data) noexcept {
		const char stringSybol[] = "\"";

		// check if string starts with "
		if (!stringCompare(data.Get(), stringSybol))
		{
			return nullopt;
		}

		data.Erase(1);

		uint32_t size = 0;
		while (data.Size() > size) {
			if (data.Data()[size] == *stringSybol) {
				string_view value{ data.Data(), size };
				data.Erase(size + 1);
				return value;
			}
			size++;
		}

		data.Erase(size);
		return nullopt;
	}



	bool tokenize(string& str, const TokenType token) {
		if (token == TokenType::Number) {

		}
		string_view name = StaticTokenMap.at(token);
		return strncmp(str.data(), name.data(), name.size()) == 0;
	}

	/*
	const unordered_map<TokenType, function<string>> test{

	}
	*/

	//unordered_map<string_view, int> map;
}