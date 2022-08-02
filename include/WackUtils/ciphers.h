#pragma once
#include <string>
#include <functional>

namespace WackUtils::encoding {
	/// Encodes a string using the given algorithm.
	/// @param message The string to encode.
	/// @param algorithm The algorithm to use.
	/// @returns The encoded string.
	std::string encode(const std::string& message, const std::string& type);

	/// Decodes a string using the given algorithm.
	/// @param message The string to decode.
	/// @param algorithm The algorithm to use.
	/// @returns The decoded string.
	std::string decode(const std::string& message, const std::string& type);

	/// Encodes a string using a custom algorithm.
	/// @param message The string to encode.
	/// @param encoder The function to use to encode the string. The function should take a string and return a string.
	/// @note This function is redundant if you are using a custom algorithm.
	/// @returns The encoded string.
	std::string encode(const std::string& message, const std::function<std::string(std::string)> encoder);

	/// Decodes a string using a custom algorithm.
	/// @param message The string to decode.
	/// @param decoder The function to use to decode the string. The function should take a string and return a string.
	/// @note This function is very redundant.
	/// @returns The decoded string.
	std::string decode(const std::string& message, const std::function<std::string(std::string)> decoder);
}