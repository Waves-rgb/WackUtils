#pragma once

#include <functional>
#include <string>

namespace WackUtils::hashing {
	struct Hash {
		std::string ciphertext;
		std::string plaintext;
		std::string algorithm;
		std::string salt;
	};

	typedef std::function<std::string(std::string)> hashAlgorithm_t;

	/// Generates a hash of a string.
	/// @param message The string to hash.
	/// @param algorithm The algorithm to use.
	/// @returns The hash of the string.
	Hash hash(const std::string& message, const std::string& algorithm);

	/// Generates a hash of a string, using a salt.
	/// @param message The string to hash.
	/// @param algorithm The algorithm to use.
	/// @param salt The salt to use. (if salt is empty, a salt of 16 bits will be generated).
	/// @returns The hash of the string.
	Hash saltedHash(const std::string& message, const std::string& algorithm, const std::string& salt);

	/// Hashes a string using a custom algorithm.
	/// @param message The string to hash.
	/// @param encoder The function to use to hash the string. The function should take a string and return a string.
	/// @returns The hash of the string.
	/// @note This function is provided for convenience. It is not recommended to use this function.
	Hash hash(const std::string& message, const hashAlgorithm_t encoder);

	/// Hashes a string using a custom algorithm, using a salt.
	/// @param message The string to hash.
	/// @param encoder The function to use to hash the string. The function should take a string and return a string.
	/// @param salt The salt to use. (if salt is empty, a salt of 16 bits will be generated).
	/// @returns The hash of the string.
	/// @note This mer
	Hash saltedHash(const std::string& message, const hashAlgorithm_t encoder, const std::string& salt);
}